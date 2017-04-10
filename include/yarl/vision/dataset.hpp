#ifndef YARL_VISION_DATASET_HPP
#define YARL_VISION_DATASET_HPP

#include "yarl/utils/utils.hpp"

namespace yarl {

class TestDataset {
public:
  bool configured;

  Mat3 K;
  int image_width;
  int image_height;

  TestDataset(void);
  int configure(const std::string config_file);
  int generateTestData(const std::string output_path);
};

}  // end of yarl namespace
#endif
