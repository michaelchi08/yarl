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

  FastDetector(void);
  int configure(int threshold, bool nonmax_suppression);
  int detect(cv::Mat &image, std::vector<cv::KeyPoint> &keypoints);
  int detect(cv::Mat &image, std::vector<cv::Point2f> &points);
  int detect(cv::Mat &image, MatX &points);
};

}  // end of yarl namespace
#endif
