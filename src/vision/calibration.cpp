#include "yarl/vision/calibration.hpp"

namespace yarl {

int Calibration::configure(const std::string &save_path,
                           const Chessboard &chessboard,
                           const cv::Size &image_size,
                           int nb_max_samples) {
  // setup
  std::string calib_dir = rmtrailslash(save_path);

  // mkdir calibration directory
  int retval = mkdir(calib_dir.c_str(), ACCESSPERMS);
  if (retval != 0) {
    switch (errno) {
      case EACCES: log_error(MKDIR_PERMISSION, save_path.c_str()); break;
      case ENOTDIR: log_error(MKDIR_INVALID, save_path.c_str()); break;
      case EEXIST: log_error(MKDIR_EXISTS, save_path.c_str()); break;
      default: log_error(MKDIR_FAILED, save_path.c_str()); break;
    }
    return -1;
  }

  // initialize variables
  this->image_size = image_size;
  this->chessboard = chessboard;
  this->nb_samples = 0;
  this->nb_max_samples = nb_max_samples;
  this->save_path = save_path;

  return 0;
}

bool Calibration::findChessboardCorners(const cv::Mat &image,
                                        std::vector<cv::Point2f> &corners) {
  // setup
  this->state = CAPTURING;
  if (corners.size()) {
    corners.clear();
  }

  // detect chessboard corners
  int flags = cv::CALIB_CB_ADAPTIVE_THRESH;
  flags += cv::CALIB_CB_NORMALIZE_IMAGE;
  flags += cv::CALIB_CB_FAST_CHECK;
  bool corners_found = cv::findChessboardCorners(
    image, this->chessboard.board_size, corners, flags);

  // draw detected chessboard corners
  cv::drawChessboardCorners(
    image, this->chessboard.board_size, corners, corners_found);

  return corners_found;
}

int Calibration::saveImage(const cv::Mat &image,
                           const std::vector<cv::Point2f> &img_points) {
  // pre-check
  if ((int) img_points.size() != this->chessboard.nb_corners_total) {
    log_info("failed to detect complete chessboard!");
    return -1;
  } else if (nb_samples >= nb_max_samples) {
    this->state = READY_TO_CALIBRATE;
    log_info("max calibration samples captured!");
    return -2;
  }

  // save image
  log_info("captured image [%d]", this->nb_samples);
  std::string image_path = this->save_path + "/";
  image_path += "sample_" + std::to_string(this->nb_samples) + ".jpg";
  cv::imwrite(image_path, image);

  // record image points
  this->nb_samples++;

  return 0;
}

int Calibration::calibrate(
  const std::vector<std::vector<cv::Point2f>> &img_points,
  const cv::Size &image_size) {
  // pre-check
  if (this->state != READY_TO_CALIBRATE) {
    log_info("calibrator is not ready to calibrate!");
    return -2;
  }

  // hard-coding the object points - assuming chessboard is origin by
  // setting chessboard in the x-y plane (where z = 0).
  std::vector<std::vector<cv::Point3f>> object_points;
  for (int i = 0; i < chessboard.nb_corners_rows; i++) {
    for (int j = 0; j < chessboard.nb_corners_columns; j++) {
      object_points[0].push_back(cv::Point3f(j, i, 0.0f));
    }
  }
  object_points.resize(img_points.size(), object_points[0]);

  // calibrate camera
  this->reprojection_error =
    cv::calibrateCamera(object_points,
                        img_points,
                        image_size,
                        this->camera_matrix,
                        this->distortion_coefficients,
                        this->rotation_vectors,
                        this->translation_vectors);

  // check results
  bool camera_matrix_ok = cv::checkRange(this->camera_matrix);
  bool distortion_ok = cv::checkRange(this->distortion_coefficients);
  if (camera_matrix_ok && distortion_ok) {
    return 0;
  } else {
    return -1;
  }
}

int Calibration::saveCalibrationOutputs() {
  // setup
  std::ofstream outfile;
  outfile.open(this->save_path + "/" + CALIBRATION_FILENAME);
  if (outfile.bad()) {
    return -1;
  }

  // image width and height
  int img_width = this->image_size.width;
  int img_height = this->image_size.height;
  outfile << "<image_width>" << img_width << "</image_width>" << std::endl;
  outfile << "<image_height>" << img_height << "</image_height>" << std::endl;

  // camera matrix
  double fx = this->camera_matrix.at<double>(0, 0);
  double fy = this->camera_matrix.at<double>(1, 1);
  double cx = this->camera_matrix.at<double>(0, 2);
  double cy = this->camera_matrix.at<double>(1, 2);
  outfile << "<fx>" << fx << "</fx>" << std::endl;
  outfile << "<fy>" << fy << "</fy>" << std::endl;
  outfile << "<cx>" << cx << "</cx>" << std::endl;
  outfile << "<cy>" << cy << "</cy>" << std::endl;

  // distortion coefficent
  outfile << "<distortion_coefficients>";
  // outfile << this->reprojection_error;
  outfile << "</distortion_coefficients>" << std::endl;

  // distortion coefficent
  outfile << "<reprojection_error>";
  outfile << this->reprojection_error;
  outfile << "</reprojection_error>" << std::endl;

  // close
  outfile.close();

  return 0;
}

}  // end of yarl namespace
