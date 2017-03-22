#ifndef VISION_FAST_HPP
#define VISION_FAST_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include "battery/utils/utils.hpp"

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
