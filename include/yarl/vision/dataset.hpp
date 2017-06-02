#ifndef YARL_VISION_DATASET_HPP
#define YARL_VISION_DATASET_HPP

#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "yarl/utils/utils.hpp"
#include "yarl/vision/utils.hpp"
#include "yarl/models/two_wheel.hpp"

namespace yarl {

class VOTestCamera {
public:
  int image_width = 0;
  int image_height = 0;
  Mat3 K = Mat3::Zero();
  double hz = 0;

  double dt = 0;
  int frame = 0;

  VOTestCamera() {}

  VOTestCamera(int image_width, int image_height, Mat3 K, double hz)
    : image_width{image_width}, image_height{image_height}, K{K}, hz{hz} {}

  bool update(double dt);
  int checkFeatures(double dt,
                    const MatX &features,
                    const Vec3 &rpy,
                    const Vec3 &t,
                    std::vector<std::pair<Vec2, Vec3>> &observed);
};

class VOTestDataset {
public:
  bool configured = false;

  VOTestCamera camera;
  int nb_features = 0;
  Vec2 feature_x_bounds = Vec2::Zero();
  Vec2 feature_y_bounds = Vec2::Zero();
  Vec2 feature_z_bounds = Vec2::Zero();

  MatX features_world = MatX::Zero(1, 1);
  std::vector<std::pair<double, Vec3>> robot_state;
  std::vector<std::vector<std::pair<Vec2, Vec3>>> features_observed;

  VOTestDataset() {}

  int configure(const std::string &config_file);
  int generateRandom3DFeatures(MatX &features);
  int output3DFeatures(const std::string &output_path);
  int outputObservedFeatures(const std::string &output_path);
  int outputRobotState(const std::string &output_dir);
  int simulateVODataset();
  int generateTestData(const std::string &output_path);
};

}  // namespace yarl
#endif
