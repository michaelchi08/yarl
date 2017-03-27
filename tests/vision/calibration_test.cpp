#include "yarl/vision/calibration.hpp"
#include "yarl/yarl_test.hpp"

#define TEST_IMAGE "tests/data/vision/chessboard.jpg"

namespace yarl {

// TEST(Calibration, constructor) {
//   Calibration calibration;
//
//   ASSERT_EQ(false, calibration.configured);
//   ASSERT_EQ(IDEL, calibration.state);
//
//   ASSERT_EQ(0, calibration.nb_samples);
//   ASSERT_EQ(10, calibration.nb_max_samples);
//   ASSERT_EQ("./", calibration.save_path);
// }
//
// TEST(Calibration, configure) {
//   Calibration calib;
//   Chessboard chess;
//
//   // setup
//   system("rm -rf /tmp/test");
//   chess.configure(4, 4);
//   calib.configure("/tmp/test", chess, cv::Size(600, 600), 10);
//
//   ASSERT_EQ(0, calib.nb_samples);
//   ASSERT_EQ(10, calib.nb_max_samples);
//   ASSERT_EQ("/tmp/test", calib.save_path);
// }
//
// TEST(Calibration, findChessboardCorners) {
//   bool retval;
//   cv::Mat image;
//   Calibration calib;
//   Chessboard chess;
//   std::vector<cv::Point2f> corners;
//
//   // setup
//   system("rm -rf /tmp/test");
//
//   image = cv::imread(TEST_IMAGE);
//   chess.configure(7, 7);
//   calib.configure("/tmp/test", chess, cv::Size(600, 600), 10);
//
//   // test and assert
//   retval = calib.findChessboardCorners(image, corners);
//   ASSERT_EQ(true, retval);
//   ASSERT_EQ(49, corners.size());
//
//   // cv::imshow("test", image);
//   // cv::waitKey(1000);
// }
//
// TEST(Calibration, saveImage) {
//   std::ifstream image_file;
//   cv::Mat image;
//   Chessboard chess;
//   Calibration calib;
//   std::vector<cv::Point2f> corners;
//
//   // setup
//   system("rm -rf /tmp/test");
//
//   image = cv::imread(TEST_IMAGE);
//   chess.configure(7, 7);
//   calib.configure("/tmp/test", chess, cv::Size(600, 600), 10);
//   calib.findChessboardCorners(image, corners);
//   calib.saveImage(image, corners);
//
//   // // test and assert
//   // image_file.open("/tmp/test/sample_0.jpg", std::ifstream::in);
//   // ASSERT_TRUE(image_file.good());
// }
//
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
//   // test and assert
//   calib.saveCalibrationOutputs();
//   yaml_file.open("/tmp/test/calibration.yaml", std::ifstream::in);
//   ASSERT_TRUE(yaml_file.good());
// }

}  // end of yarl namespace
