#include "yarl/vision/good.hpp"

namespace yarl {

GoodDetector::GoodDetector(void) {
  this->configured = false;
  this->max_corners = 1000;
  this->quality_level = 0.1;
  this->min_dist = 10;
  this->block_size = 3;
  this->use_harris = false;
  this->k = 0.04;
}

int GoodDetector::configure(void) {
  this->configured = true;
  return 0;
}

int GoodDetector::detect(const cv::Mat &image,
                         std::vector<cv::Point2f> &points) {
  cv::goodFeaturesToTrack(image,
                          points,
                          this->max_corners,
                          this->quality_level,
                          this->min_dist,
                          this->mask,
                          this->block_size);

  return 0;
}

}  // end of yarl namespace
