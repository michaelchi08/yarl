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

  VOTestDataset() {}

  int configure(const std::string &config_file);
  void prepHeader(std::ofstream &output_file);
  int generateRandom3DFeatures(MatX &features);
  int record3DFeatures(const std::string &output_path, const MatX &features);
  int recordObservedFeatures(double time,
                             const Vec3 &x,
                             const std::string &output_path,
                             std::vector<std::pair<Vec2, Vec3>> &observed);
  int recordRobotState(std::ofstream &output_file, const Vec3 &x);
  int generateTestData(const std::string &output_path);
};

}  // namespace yarl
#endif
