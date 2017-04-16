#include "yarl/vision/fast.hpp"

namespace yarl {

int FastDetector::configure(int threshold, bool nonmax_suppression) {
  this->configured = true;
  this->threshold = threshold;
  this->nonmax_suppression = nonmax_suppression;

  return 0;
}

int FastDetector::detect(const cv::Mat &image,
                         std::vector<cv::KeyPoint> &keypoints) {
  cv::FAST(image, keypoints, this->threshold, this->nonmax_suppression);

  return 0;
}

int FastDetector::detect(const cv::Mat &image,
                         std::vector<cv::Point2f> &points) {
  std::vector<cv::KeyPoint> keypoints;
  cv::FAST(image, keypoints, this->threshold, this->nonmax_suppression);
  cv::KeyPoint::convert(keypoints, points, std::vector<int>());

  return 0;
}

int FastDetector::detect(const cv::Mat &image, MatX &points) {
  std::vector<cv::KeyPoint> keypoints;

  cv::FAST(image, keypoints, this->threshold, this->nonmax_suppression);
  points.resize(keypoints.size(), 2);
  for (size_t i = 0; i < keypoints.size(); i++) {
    points(i, 0) = keypoints[i].pt.x;
    points(i, 1) = keypoints[i].pt.y;
  }

  return 0;
}

}  // end of yarl namespace
