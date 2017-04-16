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

  GoodDetector() :
    configured(false),
    max_corners(1000),
    quality_level(0.1),
    min_dist(10),
    block_size(3),
    use_harris(false),
    k(0.04) {}

  int configure();
  int detect(const cv::Mat &image, std::vector<cv::Point2f> &points);
};

}  // end of yarl namespace
#endif
