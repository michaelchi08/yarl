#ifndef YARL_VISION_FAST_HPP
#define YARL_VISION_FAST_HPP

#include "yarl/utils/utils.hpp"
#include "yarl/vision/utils.hpp"

namespace yarl {

class FastDetector {
public:
  bool configured;

  int threshold;
  bool nonmax_suppression;

  FastDetector() :
    configured(false),
    threshold(20),
    nonmax_suppression(true) {}

  int configure(int threshold, bool nonmax_suppression);
  int detect(const cv::Mat &image, std::vector<cv::KeyPoint> &keypoints);
  int detect(const cv::Mat &image, std::vector<cv::Point2f> &points);
  int detect(const cv::Mat &image, MatX &points);
};

}  // end of yarl namespace
#endif
