#ifndef VISION_FAST_HPP
#define VISION_FAST_HPP

#include "battery/utils/utils.hpp"
#include "battery/vision/utils.hpp"

namespace battery {

class FastDetector {
public:
  bool configured;

  int threshold;
  bool nonmax_suppression;

  FastDetector(void);
  int configure(int threshold, bool nonmax_suppression);
  int detect(cv::Mat &image, std::vector<cv::KeyPoint> &keypoints);
  int detect(cv::Mat &image, std::vector<cv::Point2f> &points);
  int detect(cv::Mat &image, MatX &points);
};

} // end of battery namespace
#endif
