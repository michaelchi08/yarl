#include "yarl/test.hpp"
#include "yarl/utils/utils.hpp"
#include "yarl/vision/dataset.hpp"
#include "yarl/optimization/ceres/ba.hpp"

namespace yarl {

const std::string TEST_CONFIG = "tests/data/vision/dataset/vo_test.xml";

TEST(BAResidual, constructor) {
  // TEST DEFAULT CONSTRUCTOR
  BAResidual residual1;

  EXPECT_FLOAT_EQ(0.0, residual1.fx);
  EXPECT_FLOAT_EQ(0.0, residual1.fy);
  EXPECT_FLOAT_EQ(0.0, residual1.cx);
  EXPECT_FLOAT_EQ(0.0, residual1.cy);
  EXPECT_FLOAT_EQ(0.0, residual1.x);
  EXPECT_FLOAT_EQ(0.0, residual1.y);

  // TEST CONSTRUCTOR WITH PARAMETERS
  Mat3 K;
  // clang-format off
  K << 1.0, 0.0, 3.0,
       0.0, 2.0, 4.0,
       0.0, 0.0, 1.0;
  // clang-format on
  Vec2 x = Vec2{130, 62};

  BAResidual residual2(K, x);
  EXPECT_FLOAT_EQ(K(0, 0), residual2.fx);
  EXPECT_FLOAT_EQ(K(1, 1), residual2.fy);
  EXPECT_FLOAT_EQ(K(0, 2), residual2.cx);
  EXPECT_FLOAT_EQ(K(1, 2), residual2.cy);
  EXPECT_FLOAT_EQ(x(0), residual2.x);
  EXPECT_FLOAT_EQ(x(1), residual2.y);
}

TEST(BAResidual, test) {
  Mat3 K = Mat3::Identity();
  Vec2 p = Vec2{10, 10};

  double q[4] = {0.0, 0.0, 0.0, 1.0};
  double c[3] = {0.0, 0.0, 0.0};
  double x[3] = {10.0, 10.0, 1.0};
  double e[2] = {0.0, 0.0};

  auto residual = BAResidual(K, p);
  bool retval = residual(q, c, x, e);

  std::cout << e[0] << std::endl;
  std::cout << e[1] << std::endl;

  EXPECT_TRUE(retval);
  EXPECT_FLOAT_EQ(0.0, e[0]);
  EXPECT_FLOAT_EQ(0.0, e[1]);
}

// TEST(BundleAdjustment, addCamera) {
//   // setup
//   Mat3 K = Mat3::Identity();
//   MatX features = MatX::Random(10, 2);
//   VecX landmark_ids = VecX::Random(10);
//   Vec3 cam_t{0.0, 0.0, 0.0};
//   Quaternion cam_q{1.0, 0.0, 0.0, 0.0};
//   double **landmarks = (double **) malloc(sizeof(double **) * 5);
//   landmarks[0] = (double *) malloc(sizeof(double *) * 3);
//   landmarks[1] = (double *) malloc(sizeof(double *) * 3);
//   landmarks[2] = (double *) malloc(sizeof(double *) * 3);
//   landmarks[3] = (double *) malloc(sizeof(double *) * 3);
//   landmarks[4] = (double *) malloc(sizeof(double *) * 3);
//
//   // test and assert
//   BundleAdjustment ba;
//   ba.addCamera(K, features, landmark_ids, cam_t, cam_q, landmarks);
//
//   // clean up
//   free(landmarks[0]);
//   free(landmarks[1]);
//   free(landmarks[2]);
//   free(landmarks[3]);
//   free(landmarks[4]);
//   free(landmarks);
// }

static double **build_landmark_matrix(const VOTestDataset &dataset) {
  size_t nb_landmarks = dataset.landmarks.size();
  double **landmarks = (double **) malloc(sizeof(double *) * nb_landmarks);

  for (auto landmark : dataset.landmarks) {
    int landmark_id = landmark.second;
    Vec3 point = landmark.first;

    landmarks[landmark_id] = (double *) malloc(sizeof(double) * 3);
    landmarks[landmark_id][0] = point(0);
    landmarks[landmark_id][1] = point(1);
    landmarks[landmark_id][2] = point(2);
  }

  return landmarks;
}

static VecX build_landmark_ids(
  const std::vector<std::pair<Vec2, int>> &features_observed) {
  VecX landmark_ids{features_observed.size()};

  for (size_t i = 0; i < features_observed.size(); i++) {
    landmark_ids(i) = features_observed[i].second;
  }

  return landmark_ids;
}

static MatX build_feature_matrix(
  const std::vector<std::pair<Vec2, int>> &features_observed) {
  MatX features(features_observed.size(), 2);

  for (size_t i = 0; i < features_observed.size(); i++) {
    features.block(i, 0, 1, 2) = features_observed[i].first.transpose();
  }

  return features;
}

static void print_vector3(double *vector) {
  std::cout << "(";
  std::cout << vector[0] << ", ";
  std::cout << vector[1] << ", ";
  std::cout << vector[2];
  std::cout << ")" << std::endl;
}

static void print_vector4(double *vector) {
  std::cout << "(";
  std::cout << vector[0] << ", ";
  std::cout << vector[1] << ", ";
  std::cout << vector[2] << ", ";
  std::cout << vector[3];
  std::cout << ")" << std::endl;
}

TEST(BundleAdjustment, solve) {
  // create vo dataset
  VOTestDataset dataset;
  dataset.configure(TEST_CONFIG);
  dataset.simulateVODataset();
  double **landmarks = build_landmark_matrix(dataset);

  // build bundle adjustment problem
  BundleAdjustment ba;
  std::vector<double *> translations;
  std::vector<double *> rotations;

  Vec2 feature = dataset.features_observed[0][0].first;
  int landmark_id = dataset.features_observed[0][0].second;
  BAResidual residual{dataset.camera.K, feature};

  std::cout << dataset.camera.K << std::endl;

  Vec3 t = dataset.robot_state[0].second;
  double *t_vec = (double *) malloc(sizeof(double *) * 3);
  t_vec[0] = -t(1);
  t_vec[1] = 0.0;
  t_vec[2] = t(0);

  Quaternion q = Eigen::AngleAxisd(0.0, Vec3::UnitX()) *
                 Eigen::AngleAxisd(0.0, Vec3::UnitY()) *
                 Eigen::AngleAxisd(0.0, Vec3::UnitZ());
  double *q_vec = (double *) malloc(sizeof(double *) * 4);
  q_vec[0] = q.w();
  q_vec[1] = q.x();
  q_vec[2] = q.y();
  q_vec[3] = q.z();

  print_vector3(t_vec);
  print_vector4(q_vec);

  double e[2] = {0.0, 0.0};
  residual(q_vec, t_vec, landmarks[landmark_id], e);
  std::cout << "landmark_id: " << landmark_id << std::endl;
  std::cout << "landmark: ";
  print_vector3(landmarks[landmark_id]);
  std::cout << std::endl;
  std::cout << e[0] << std::endl;
  std::cout << e[1] << std::endl;

  // // for (size_t i = 0; i < dataset.robot_state.size(); i++) {
  // for (size_t i = 0; i < 2; i++) {
  //   // translation
  //   Vec3 t = dataset.robot_state[i].second;
  //   double *t_vec = (double *) malloc(sizeof(double *) * 3);
  //   // t_vec[0] = t(0);
  //   // t_vec[1] = t(1);
  //   // t_vec[2] = 0.0;
  //   t_vec[0] = -t(1);
  //   t_vec[1] = 0.0;
  //   t_vec[2] = t(0);
  //   translations.push_back(t_vec);
  //
  //   // rotation
  //   // Quaternion q = Eigen::AngleAxisd(0.0, Vec3::UnitX()) *
  //   //                Eigen::AngleAxisd(0.0, Vec3::UnitY()) *
  //   //                Eigen::AngleAxisd(t(2), Vec3::UnitZ());
  //   Quaternion q = Eigen::AngleAxisd(0.0, Vec3::UnitX()) *
  //                  Eigen::AngleAxisd(-t(2), Vec3::UnitY()) *
  //                  Eigen::AngleAxisd(0.0, Vec3::UnitZ());
  //   double *q_vec = (double *) malloc(sizeof(double *) * 4);
  //   q_vec[0] = q.x();
  //   q_vec[1] = q.y();
  //   q_vec[2] = q.z();
  //   q_vec[3] = q.w();
  //   rotations.push_back(q_vec);
  //
  //   // // add camera
  //   VecX landmark_ids = build_landmark_ids(dataset.features_observed[i]);
  //   MatX features = build_feature_matrix(dataset.features_observed[i]);
  //   ba.addCamera(
  //     dataset.camera.K, features, landmark_ids, t_vec, q_vec, landmarks);
  // }
  //
  // // test
  // ba.solve();
  //
  // print_vector3(translations[0]);
  // print_vector3(translations[1]);
}

}  // namespace yarl
