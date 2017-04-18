#ifndef YARL_VISION_CALIBRATION_HPP
#define YARL_VISION_CALIBRATION_HPP

#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <fstream>
#include <iostream>

#include "yarl/utils/utils.hpp"
#include "yarl/vision/chessboard.hpp"
#include "yarl/vision/utils.hpp"

namespace yarl {

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

  cv::Size image_size;
  cv::Mat camera_matrix;
  cv::Mat distortion_coefficients;
  std::vector<cv::Mat> rotation_vectors;
  std::vector<cv::Mat> translation_vectors;
  double reprojection_error;

  Calibration()
    : configured(false),
      state(IDEL),
      nb_samples(0),
      nb_max_samples(10),
      save_path("./") {}

  int configure(const std::string &save_path,
                const Chessboard &chessboard,
                const cv::Size &image_size,
                int nb_max_samples);
  bool findChessboardCorners(const cv::Mat &image,
                             std::vector<cv::Point2f> &corners);
  int saveImage(const cv::Mat &image,
                const std::vector<cv::Point2f> &corners);
  int calibrate(const std::vector<std::vector<cv::Point2f>> &image_points,
                const cv::Size &image_size);
  int saveCalibrationOutputs();
};

}  // end of yarl namespace
#endif
