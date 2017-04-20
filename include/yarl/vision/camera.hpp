#ifndef YARL_VISION_CAMERA_HPP
#define YARL_VISION_CAMERA_HPP

#include <iostream>

#include "yarl/utils/log.hpp"
#include "yarl/vision/utils.hpp"

namespace yarl {

class Camera {
public:
  bool configured;

  cv::VideoCapture capture;
  int capture_index;
  int image_width;
  int image_height;
  cv::Mat camera_mat;
  cv::Mat distortion_coef;

  Camera()
    : configured(false),
      capture(),
      capture_index(-1),
      image_width(0),
      image_height(0),
      camera_mat(),
      distortion_coef() {}

  ~Camera() {
    if (this->capture.isOpened()) {
      this->capture.release();
    }
  }

  int configure(int capture_index, int image_width, int image_height);
  int getFrame(cv::Mat &frame);
  int getUndistortFrame(cv::Mat &frame);
  int saveFrame(const cv::Mat &frame, const std::string &save_path);
  void close();
};

}  // end of yarl namespace
#endif
