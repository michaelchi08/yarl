#ifndef VISION_CALIBRATION_HPP
#define VISION_CALIBRATION_HPP

#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <fstream>
#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include <yaml-cpp/yaml.h>

#include "battery/utils/logging.hpp"
#include "battery/utils/utils.hpp"
#include "battery/vision/chessboard.hpp"

namespace battery {

// ERROR MESSAGES
#define ECALIBDIRPERM "permission denied! while creating [%s]!"
#define ECALIBNOTDIR "[%s] is not a dir!"
#define ECALIBDIREXIST "[%s] already exists!"
#define ECALIBDIR "failed to create [%s]!"

// CALIBRATION STATES
#define IDEL 0
#define CAPTURING 1
#define READY_TO_CALIBRATE 2

// MACROS
#define CALIBRATION_FILENAME "calibration.yaml"

class Calibration {
public:
  bool configured;
  int state;

  Chessboard chessboard;
  int nb_samples;
  int nb_max_samples;
  std::string save_path;
  YAML::Emitter yaml_config;

  cv::Size image_size;
  cv::Mat camera_matrix;
  cv::Mat distortion_coefficients;
  std::vector<cv::Mat> rotation_vectors;
  std::vector<cv::Mat> translation_vectors;
  double reprojection_error;

  Calibration(void);
  int configure(std::string calibration_path, Chessboard &chessboard,
                cv::Size image_size, int nb_max_samples);
  bool findChessboardCorners(cv::Mat &image, std::vector<cv::Point2f> &corners);
  int saveImage(cv::Mat &image, std::vector<cv::Point2f> corners);
  int calibrate(std::vector<std::vector<cv::Point2f>> image_points,
                cv::Size image_size);
  int saveCalibrationOutputs(void);
};

} // end of battery namespace
#endif
