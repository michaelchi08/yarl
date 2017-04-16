#include "yarl/vision/camera.hpp"

namespace yarl {

Camera::Camera() {
  this->configured = false;

  this->capture_index = 0;
  this->image_width = 0;
  this->image_height = 0;
}

Camera::~Camera() {
  if (this->capture.isOpened()) {
    this->capture.release();
  }
}

int Camera::configure(int capture_index, int image_width, int image_height) {
  // setup
  this->configured = true;
  this->capture = cv::VideoCapture(capture_index);
  this->capture_index = capture_index;
  this->image_width = image_width;
  this->image_height = image_height;

  // open camera
  if (this->capture.isOpened() == 0) {
    log_err("failed to open webcam!");
    return -1;
  }

  // configure image resolution
  this->capture.set(cv::CAP_PROP_FRAME_WIDTH, image_width);
  this->capture.set(cv::CAP_PROP_FRAME_HEIGHT, image_height);

  return 0;
}

int Camera::getFrame(cv::Mat &frame) {
  bool retval = this->capture.read(frame);
  if (retval == false) {
    return -1;
  }

  return 0;
}

int Camera::getUndistortFrame(cv::Mat &frame) {
  bool retval = this->capture.read(frame);
  if (retval == false) {
    return -1;
  }
  cv::undistort(frame, frame, this->camera_mat, this->distortion_coef);

  return 0;
}

int Camera::saveFrame(const cv::Mat &frame, const std::string &save_path) {
  bool retval = cv::imwrite(save_path, frame);
  if (retval == false) {
    return -1;
  }

  return 0;
}

void Camera::close() {
  if (this->capture.isOpened()) {
    this->capture.release();
  }
}

}  // end of yarl namespace
