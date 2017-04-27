#include "yarl/vision/camera.hpp"

namespace yarl {

int Camera::configure(int capture_index, int image_width, int image_height) {
  // setup
  this->configured = true;
  this->capture = cv::VideoCapture(capture_index);
  this->capture_index = capture_index;
  this->image_width = image_width;
  this->image_height = image_height;

  // open camera
  if (this->capture.isOpened() == false) {
    log_error("failed to open webcam!");
    return -1;
  }

  // configure image resolution
  this->capture.set(cv::CAP_PROP_FRAME_WIDTH, image_width);
  this->capture.set(cv::CAP_PROP_FRAME_HEIGHT, image_height);

  return 0;
}

int Camera::configure(const std::string &config_path) {


  return 0;
}

int Camera::getFrame(cv::Mat &frame) {
  // pre-check
  if (this->configured == false) {
    return -1;
  }

  // get frame
  bool retval = this->capture.read(frame);
  if (retval == false) {
    return -2;
  }

  return 0;
}

int Camera::getUndistortFrame(cv::Mat &frame) {
  // pre-check
  if (this->configured == false) {
    return -1;
  }

  // get undistorted frame
  bool retval = this->capture.read(frame);
  if (retval == false) {
    return -2;
  }
  cv::undistort(frame, frame, this->camera_mat, this->distortion_coef);

  return 0;
}

int Camera::saveFrame(const cv::Mat &frame, const std::string &save_path) {
  // pre-check
  if (this->configured == false) {
    return -1;
  }

  // save frame
  bool retval = cv::imwrite(save_path, frame);
  if (retval == false) {
    return -2;
  }

  return 0;
}

int Camera::showFPS(double &last_tic, int &frame_count) {
  // pre-check
  if (this->configured == false) {
    return -1;
  }

  // show fps
  double t;
  double fps;

  frame_count++;
  if (frame_count % 30 == 0 && this->config.showfps) {
    t = time_now();
    fps = 30.0 / (t - last_tic);
    printf("fps: %.2f\n", fps);
    last_tic = t;
    frame_count = 0;
  }

  return 0;
}

int Camera::showImage(cv::Mat &image) {
  // pre-check
  if (this->configured == false) {
    return -1;
  }

  // show image
  if (this->config.imshow && image.rows && image.cols) {
    cv::imshow("Camera", image);
    cv::waitKey(1);
  }

  return 0;
}

int Camera::run(void) {
  int frame_count;
  double t;
  double last_tic;

  // pre-check
  if (this->configured == false) {
    return -1;
  }

  // setup
  frame_count = 0;
  last_tic = time_now();

  // run
  while (true) {
    this->getFrame(this->image);

    // show stats
    this->showFPS(last_tic, frame_count);
    this->showImage(this->image);
  }

  return 0;
}

void Camera::close() {
  if (this->capture.isOpened()) {
    this->capture.release();
  }
}

}  // end of yarl namespace
