#include "yarl/test.hpp"
#include "yarl/vision/calibration.hpp"

#define TEST_IMAGE "tests/data/vision/chessboard.jpg"

namespace yarl {

TEST(Calibration, constructor) {
  Calibration calibration;

  EXPECT_FALSE(calibration.configured);
  EXPECT_EQ(IDEL, calibration.state);

  EXPECT_EQ(0, calibration.nb_samples);
  EXPECT_EQ(10, calibration.nb_max_samples);
  EXPECT_EQ("./", calibration.save_path);
}

TEST(Calibration, configure) {
  Calibration calib;
  Chessboard chess;

  // setup
  system("rm -rf /tmp/test");
  chess.configure(4, 4);
  calib.configure("/tmp/test", chess, cv::Size(600, 600), 10);

  EXPECT_EQ(0, calib.nb_samples);
  EXPECT_EQ(10, calib.nb_max_samples);
  EXPECT_EQ("/tmp/test", calib.save_path);
}

TEST(Calibration, findChessboardCorners) {
  bool retval;
  cv::Mat image;
  Calibration calib;
  Chessboard chess;
  std::vector<cv::Point2f> corners;

  // setup
  system("rm -rf /tmp/test");

  image = cv::imread(TEST_IMAGE);
  chess.configure(7, 7);
  calib.configure("/tmp/test", chess, cv::Size(600, 600), 10);

  // test
  retval = calib.findChessboardCorners(image, corners);
  EXPECT_TRUE(retval);
  EXPECT_EQ(49, (int) corners.size());

  // cv::imshow("test", image);
  // cv::waitKey(1000);
}

TEST(Calibration, saveImage) {
  std::ifstream image_file;
  cv::Mat image;
  Chessboard chess;
  Calibration calib;
  std::vector<cv::Point2f> corners;

  // setup
  system("rm -rf /tmp/test");

  image = cv::imread(TEST_IMAGE);
  chess.configure(7, 7);
  calib.configure("/tmp/test", chess, cv::Size(600, 600), 10);
  calib.findChessboardCorners(image, corners);
  calib.saveImage(image, corners);

  // test
  image_file.open("/tmp/test/sample_0.jpg", std::ifstream::in);
  EXPECT_TRUE(image_file.good());
}

// TEST(Calibration, saveCalibrationOutputs) {
//   int k;
//   cv::Mat image;
//   std::ifstream yaml_file;
//   std::vector<cv::Point2f> corners;
//   Calibration calib;
//   Chessboard chess;
//
//   // setup
//   system("rm -rf /tmp/test");
//
//   image = cv::imread(TEST_IMAGE);
//   chess.configure(7, 7);
//   calib.configure("/tmp/test", chess, cv::Size(600, 600), 1);
//   calib.findChessboardCorners(image, corners);
//
//   calib.camera_matrix = cv::Mat(3, 3, CV_32F);
//   k = 0;
//   for (int i = 0; i < calib.camera_matrix.rows; i++) {
//     for (int j = 0; j < calib.camera_matrix.cols; j++) {
//       calib.camera_matrix.at<float>(i, j) = k;
//       k++;
//     }
//   }
//
//   calib.distortion_coefficients = cv::Mat(1, 5, CV_32F);
//   k = 0;
//   for (int i = 0; i < calib.distortion_coefficients.rows; i++) {
//     for (int j = 0; j < calib.distortion_coefficients.cols; j++) {
//       calib.distortion_coefficients.at<float>(i, j) = k;
//       k++;
//     }
//   }
//
//   // test
//   calib.saveCalibrationOutputs();
//   yaml_file.open("/tmp/test/calibration.yaml", std::ifstream::in);
//   EXPECT_TRUE(yaml_file.good());
// }

}  // namespace yarl
