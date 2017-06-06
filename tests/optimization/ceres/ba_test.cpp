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
  K << 1.0, 0.0, 3.0, 0.0, 2.0, 4.0, 0.0, 0.0, 1.0;
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

  BAResidual residual;
  residual = BAResidual(K, p);
  bool retval = residual(q, c, x, e);

  std::cout << e[0] << std::endl;
  std::cout << e[1] << std::endl;

  EXPECT_TRUE(retval);
  // EXPECT_FLOAT_EQ(0.0, e[0]);
  // EXPECT_FLOAT_EQ(0.0, e[1]);
}

TEST(BundleAdjustment, addCamera) {
  Mat3 K = Mat3::Identity();
  MatX features = MatX::Random(10, 2);
  Vec3 cam_t{0.0, 0.0, 0.0};
  Quaternion cam_q{1.0, 0.0, 0.0, 0.0};
  MatX landmarks = MatX::Random(10, 3);

  BundleAdjustment ba;
  ba.addCamera(K, features, cam_t, cam_q, landmarks);
}

TEST(BundleAdjustment, solve) {
  // int retval;

  // // create vo dataset
  // VOTestDataset dataset;
  // dataset.configure(TEST_CONFIG);
  // dataset.simulateVODataset();
  //
  // // build bundle adjustment problem
  // BundleAdjustment ba;
  // std::vector<Vec3> translations;
  // std::vector<Quaternion> rotations;

  // for (auto features : dataset.features_observed) {
  //   // translation
  //   Vec3 t{0.0, 0.0, 0.0};
  //   translations.push_back(t);
  //
  //   // rotation
  //   Quaternion q{1.0, 0.0, 0.0, 0.0};
  //   rotations.push_back(q);
  //
  //   // add camera
  //   // ba.addCamera(dataset.camera.K, t, q, landmarks, features.first);
  // }

  // test
  // struct timespec t;

  // tic(&t);
  // ba.solve();

  // std::cout << mtoc(&t) << " ms" << std::endl << std::endl;
  //
  // std::cout << "q: (";
  // std::cout << ba.q[1][0] << ", ";
  // std::cout << ba.q[1][1] << ", ";
  // std::cout << ba.q[1][2] << ", ";
  // std::cout << ba.q[1][3] << ")";
  // std::cout << std::endl;
  //
  // std::cout << "c: (";
  // std::cout << ba.c[1][0] << ", ";
  // std::cout << ba.c[1][1] << ", ";
  // std::cout << ba.c[1][2] << ")";
  // std::cout << std::endl;
  //
  // std::cout << "x: (";
  // std::cout << ba.x[1][0] << ", ";
  // std::cout << ba.x[1][1] << ", ";
  // std::cout << ba.x[1][2] << ")";
  // std::cout << std::endl;
}

}  // namespace yarl
