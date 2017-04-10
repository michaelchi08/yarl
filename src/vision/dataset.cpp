#include "yarl/vision/dataset.hpp"

namespace yarl {

TestDataset::TestDataset(void) {
  this->configured = false;

  this->K = Mat3();
  this->image_width = -1;
  this->image_height = -1;
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
  parser.addParam("/config/camera/image_width", &this->image_width);
  parser.addParam("/config/camera/image_height", &this->image_height);
  parser.addParam("/config/camera/fx", &fx);
  parser.addParam("/config/camera/fy", &fy);
  parser.addParam("/config/camera/cx", &cx);
  parser.addParam("/config/camera/cy", &cy);
  if (parser.load(config_file) != 0) {
    log_err("Failed to load [%s]!", config_file.c_str());
    return -2;
  }

  // set camera matrix
  // clang-format off
  this->K << fx, 0.0, cx,
             0.0, fy, cy,
             0.0, 0.0, 0.0;
  // clang-format on

  this->configured = true;
  return 0;
}

static void prep_header(std::ofstream &output_file) {
  output_file << "time_step" << ",";
  output_file << "x" << ",";
  output_file << "y" << ",";
  output_file << "theta" << ",";
  output_file << std::endl;
}

static void record_observation(std::ofstream &output_file, Vec3 &x) {
  output_file << x(0) << ",";
  output_file << x(1) << ",";
  output_file << x(2) << ",";
  output_file << std::endl;
}

int TestDataset::generateTestData(const std::string output_path) {
  Vec3 x, u;
  double dt, t;
  std::ofstream output_file;

  // pre-check
  if (this->configured == false) {
    return -1;
  }

  // setup
  output_file.open(output_path);
  prep_header(output_file);

  // initialize states
  dt = 0.01;
  t = 0.0;
  x << 0.0, 0.0, 0.0;
  u << -15.5, -10.5, 1.5;

  for (int i = 0; i < 100; i++) {
    // update state
    x(0) = x(0) + u(0) * cos(x(2)) * dt,
    x(1) = x(1) + u(0) * sin(x(2)) * dt,
    x(2) = x(2) + u(1) * dt;
    t += dt;

    // record state
    record_observation(output_file, x);
  }

  output_file.close();
  return 0;
}

}  // end of yarl namespace
