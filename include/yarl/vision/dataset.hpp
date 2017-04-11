#ifndef YARL_VISION_DATASET_HPP
#define YARL_VISION_DATASET_HPP

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

  TestCamera(void);
  bool update(double dt);
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
  int configure(std::string config_file);
  int generateRandom3DFeatures(MatX &features);
  int generateTestData(std::string output_path);
};

}  // end of yarl namespace
#endif
