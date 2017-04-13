#include "yarl/vision/dataset.hpp"

namespace yarl {

TestCamera::TestCamera(void) {
  this->K = Mat3();
  this->image_width = -1;
  this->image_height = -1;
  this->hz = -1;

  this->dt = 0;
  this->frame = -1;
}

bool TestCamera::update(double dt) {
  this->dt += dt;

  if (this->dt > (1.0 / this->hz)) {
    this->dt = 0.0;
    this->frame++;
    return true;
  }

  return false;
}

int TestCamera::checkFeatures(double dt,
                              const MatX &features,
                              const Vec3 &rpy,
                              const Vec3 &t,
                              std::vector<std::pair<Vec2, Vec3>> &observed) {
  Vec3 f_img, rpy_edn, t_edn;
  std::pair<Vec2, Vec3> obs;
  Vec4 f_3d;
  Mat3 R;
  MatX P;

  // pre-check
  if (this->update(dt) == false) {
    return 1;
  }

  // rotation matrix - convert from nwu to edn then to rotation matrix R
  nwu2edn(rpy, rpy_edn);
  euler2rot(rpy_edn, 123, R);

  // translation - convert translation from nwu to edn
  nwu2edn(t, t_edn);

  // projection matrix
  projection_matrix(this->K, R, t_edn, P);

  // check which features in 3d are observable from camera
  for (int i = 0; i < features.cols(); i++) {
    f_3d = features.block(0, i, 4, 1);
    f_img = P * f_3d;

    // check to see if feature is valid and infront of camera
    if (fltcmp(f_img(2), 0.0) == 0) {
      continue;  // go to next loop iteration
    }

    // normalize pixels
    f_img(0) = f_img(0) / f_img(2);
    f_img(1) = f_img(1) / f_img(2);
    f_img(2) = f_img(2) / f_img(2);

    // check to see if feature observed is within image plane
    if ((f_img(0) < this->image_width) && (f_img(0) > 0)) {
      if ((f_img(1) < this->image_height) && (f_img(1) > 0)) {
        obs = std::make_pair(f_img.block(0, 0, 2, 1), f_3d.block(0, 0, 3, 1));
        observed.push_back(obs);
      }
    }
  }

  return 0;
}

TestDataset::TestDataset(void) {
  this->configured = false;

  this->camera = TestCamera();

  this->nb_features = -1;
  this->feature_x_bounds = Vec2();
  this->feature_y_bounds = Vec2();
  this->feature_z_bounds = Vec2();
}

int TestDataset::configure(const std::string config_file) {
  ConfigParser parser;
  double fx, fy, cx, cy;

  // pre-check
  if (file_exists(config_file) == false) {
    log_err("File does not exist [%s]!", config_file.c_str());
    return -1;
  }

  // load config file
  parser.addParam("/config/camera/image_width", &this->camera.image_width);
  parser.addParam("/config/camera/image_height", &this->camera.image_height);
  parser.addParam("/config/camera/fx", &fx);
  parser.addParam("/config/camera/fy", &fy);
  parser.addParam("/config/camera/cx", &cx);
  parser.addParam("/config/camera/cy", &cy);
  parser.addParam("/config/camera/hz", &this->camera.hz);
  parser.addParam("/config/feature_points/nb_features", &this->nb_features);
  parser.addParam("/config/feature_points/x/min", &this->feature_x_bounds(0));
  parser.addParam("/config/feature_points/x/max", &this->feature_x_bounds(1));
  parser.addParam("/config/feature_points/y/min", &this->feature_y_bounds(0));
  parser.addParam("/config/feature_points/y/max", &this->feature_y_bounds(1));
  parser.addParam("/config/feature_points/z/min", &this->feature_z_bounds(0));
  parser.addParam("/config/feature_points/z/max", &this->feature_z_bounds(1));
  if (parser.load(config_file) != 0) {
    log_err("Failed to load [%s]!", config_file.c_str());
    return -2;
  }

  // set camera matrix
  // clang-format off
  this->camera.K << fx, 0.0, cx,
                    0.0, fy, cy,
                    0.0, 0.0, 1.0;
  // clang-format on

  this->configured = true;
  return 0;
}

static void prep_header(std::ofstream &output_file) {
  // clang-format off
  output_file << "time_step" << ",";
  output_file << "x" << ",";
  output_file << "y" << ",";
  output_file << "theta" << ",";
  output_file << std::endl;
  // clang-format on
}

static void record_observation(std::ofstream &output_file, Vec3 &x) {
  output_file << x(0) << ",";
  output_file << x(1) << ",";
  output_file << x(2) << ",";
  output_file << std::endl;
}

void calculate_circle_angular_velocity(double r, double v, double &w) {
  double dist, time;

  dist = 2 * M_PI * r;
  time = dist / v;
  w = (2 * M_PI) / time;
}

int TestDataset::generateRandom3DFeatures(MatX &features) {
  Vec4 point;

  // pre-check
  if (this->configured == false) {
    return -1;
  }

  // generate random 3d features
  features.resize(4, this->nb_features);
  for (int i = 0; i < this->nb_features; i++) {
    point(0) = randf(this->feature_x_bounds(0), this->feature_x_bounds(1));
    point(1) = randf(this->feature_y_bounds(0), this->feature_y_bounds(1));
    point(2) = randf(this->feature_z_bounds(0), this->feature_z_bounds(1));
    point(3) = 1.0;
    features.block(0, i, 4, 1) = point;
  }

  return 0;
}

int TestDataset::record3DFeatures(std::string output_path,
                                  const MatX &features) {
  return mat2csv(output_path, features.transpose());
}

int TestDataset::recordObservedFeatures(
  double time,
  std::string output_path,
  std::vector<std::pair<Vec2, Vec3>> &observed) {
  std::ofstream outfile(output_path);
  Vec2 f_2d;
  Vec3 f_3d;

  // open file
  if (outfile.good() != true) {
    log_err("Failed to open file [%s] to record observed features!",
            output_path.c_str());
    return -1;
  }

  // time and number of observed features
  outfile << time << std::endl;
  outfile << observed.size() << std::endl;

  // features
  for (auto feature : observed) {
    // feature in image frame
    f_2d = feature.first.transpose();
    outfile << f_2d(0) << "," << f_2d(1) << std::endl;

    // feature in world frame
    f_3d = feature.second.transpose();
    outfile << f_3d(0) << "," << f_3d(1) << "," << f_3d(2) << std::endl;
  }

  // clean up
  outfile.close();

  return 0;
}

int TestDataset::generateTestData(std::string output_path) {
  Vec3 x, t, rpy;
  Vec2 u;
  MatX features;
  double w, dt, time;
  std::ofstream output_file;
  std::vector<std::pair<Vec2, Vec3>> observed;
  std::ostringstream oss;

  // pre-check
  if (this->configured == false) {
    return -1;
  }

  // setup
  output_file.open(output_path);
  prep_header(output_file);
  calculate_circle_angular_velocity(0.5, 1.0, w);
  this->generateRandom3DFeatures(features);

  // initialize states
  dt = 0.01;
  time = 0.0;
  x << 0.0, 0.0, 0.0;
  u << 1.0, 0;

  for (int i = 0; i < 2; i++) {
    // update state
    x = two_wheel_model(x, u, dt);
    time += dt;

    // check features
    rpy << 0.0, 0.0, x(2);
    t << x(0), x(1), 0.0;
    if (this->camera.checkFeatures(dt, features, rpy, t, observed) == 0) {
      oss.str("");
      oss << "/tmp/observed_" << this->camera.frame << ".dat";
      std::cout << oss.str() << std::endl;
      this->recordObservedFeatures(time, oss.str(), observed);
    }

    // record state
    record_observation(output_file, x);
  }

  // clean up
  output_file.close();
  return 0;
}

}  // end of yarl namespace
