#include "yarl/vision/good.hpp"

namespace yarl {

int GoodDetector::configure() {
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

}  // namespace yarl
