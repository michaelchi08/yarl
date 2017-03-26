#ifndef YARL_VISION_GOOD_HPP
#define YARL_VISION_GOOD_HPP

#include "yarl/vision/utils.hpp"

namespace yarl {

class GoodDetector {
public:
  bool configured;

  int max_corners;
  double quality_level;
  double min_dist;
  int block_size;
  bool use_harris;
  double k;

  cv::Mat mask;

  GoodDetector(void);
  int configure(void);
  int detect(cv::Mat &image, std::vector<cv::Point2f> &points);
};

}  // end of yarl namespace
#endif
