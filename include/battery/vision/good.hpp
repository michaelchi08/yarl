#ifndef VISION_GOOD_HPP
#define VISION_GOOD_HPP

#include "battery/vision/utils.hpp"

namespace battery {

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

} // end of battery namespace
#endif
