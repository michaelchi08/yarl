#ifndef YARL_VISION_CAMERA_HPP
#define YARL_VISION_CAMERA_HPP

#include <iostream>

// #include <yaml-cpp/yaml.h>

#include "yarl/utils/log.hpp"
#include "yarl/vision/utils.hpp"

namespace yarl {

struct CameraConfig {
public:
  int camera_index;
  int image_width;
  int image_height;

  float exposure;
  float gain;

  cv::Mat camera_mat;
  cv::Mat rectification_mat;
  cv::Mat distortion_coef;
  cv::Mat projection_mat;
};

class Camera {
public:
  bool configured;

  cv::VideoCapture capture;

  int capture_index;
  int image_width;
  int image_height;
  cv::Mat camera_mat;
  cv::Mat distortion_coef;

  Camera(void);
  ~Camera(void);
  int configure(int capture_index, int image_width, int image_height);
  int getFrame(cv::Mat &frame);
  int getUndistortFrame(cv::Mat &frame);
  int saveFrame(const cv::Mat &frame, const std::string &save_path);
  void close(void);
};

}  // end of yarl namespace
#endif
