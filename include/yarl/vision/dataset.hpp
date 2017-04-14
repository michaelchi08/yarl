#ifndef YARL_VISION_DATASET_HPP
#define YARL_VISION_DATASET_HPP

#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "yarl/utils/utils.hpp"
#include "yarl/vision/utils.hpp"
#include "yarl/models/two_wheel.hpp"

namespace yarl {

class TestCamera {
public:
  int image_width;
  int image_height;
  Mat3 K;
  double hz;

  double dt;
  int frame;

  TestCamera(void);
  bool update(double dt);
  int checkFeatures(double dt,
                    const MatX &features,
                    const Vec3 &rpy,
                    const Vec3 &t,
                    std::vector<std::pair<Vec2, Vec3>> &observed);
};

class TestDataset {
public:
  bool configured;

  TestCamera camera;
  int nb_features;
  Vec2 feature_x_bounds;
  Vec2 feature_y_bounds;
  Vec2 feature_z_bounds;


  TestDataset(void);
  int configure(const std::string &config_file);
  int generateRandom3DFeatures(MatX &features);
  int record3DFeatures(const std::string &output_path, const MatX &features);
  int recordObservedFeatures(double time,
                             const Vec3 &x,
                             const std::string &output_path,
                             std::vector<std::pair<Vec2, Vec3>> &observed);
  int generateTestData(const std::string &output_path);
};

}  // end of yarl namespace
#endif
