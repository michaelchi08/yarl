#include "yarl/vision/utils.hpp"

namespace yarl {

double focal_length(double hfov, double image_width) {
  return (image_width / 2.0) / tan(deg2rad(hfov) / 2.0);
}

Vec2 focal_length(double hfov,
                  double vfov,
                  double image_width,
                  double image_height) {
  Vec2 focal;

  focal(0) = (image_width / 2.0) / tan(deg2rad(hfov) / 2.0);
  focal(1) = (image_height / 2.0) / tan(deg2rad(vfov) / 2.0);

  return focal;
}

double diag_focal_length(double hfov,
                         double vfov,
                         double image_width,
                         double image_height) {
  double fx, fy;
  fx = (image_width / 2.0) / tan(deg2rad(hfov) / 2.0);
  fy = (image_height / 2.0) / tan(deg2rad(vfov) / 2.0);
  return 2 * atan(sqrt(pow(fx, 2)) + sqrt(pow(fy, 2)));
}

void cvpts2mat(std::vector<cv::Point2f> points, MatX &mat) {
  cv::Point2f p;

  mat.resize(points.size(), 3);
  for (size_t i = 0; i < points.size(); i++) {
    p = points[i];
    mat(i, 0) = p.x;
    mat(i, 1) = p.y;
    mat(i, 2) = 1.0;
  }
}

void cvmatconcat(cv::Mat img1, cv::Mat img2, cv::Mat &out) {
  cv::Size size1;
  cv::Size size2;

  // setup
  size1 = img1.size();
  size2 = img2.size();
  out = cv::Mat(size1.height, size1.width + size2.width, img1.type());

  // copy image 1 to the left
  out.adjustROI(0, 0, 0, -size2.width);
  img1.copyTo(out);

  // copy image 2 to the right
  out.adjustROI(0, 0, -size1.width, size2.width);
  img2.copyTo(out);

  // restore original roi
  out.adjustROI(0, 0, size1.width, 0);
}

void projection_matrix(Mat3 K, Mat3 R, Vec3 t, MatX &P) {
  MatX extrinsics;

  extrinsics.resize(3, 4);
  extrinsics.block(0, 0, 3, 3) = R;
  extrinsics.block(0, 3, 3, 1) = t;

  P.resize(3, 4);
  P = K * extrinsics;
}

void normalize_2dpts(double image_width, double image_height, MatX &pts) {
  Mat3 N;
  MatX pts_h;

  // convert points to homogeneous coordinates
  pts_h.resize(pts.rows(), 3);
  for (int i = 0; i < pts.rows(); i++) {
    pts_h(i, 0) = pts(i, 0);
    pts_h(i, 1) = pts(i, 1);
    pts_h(i, 2) = 1.0;
  }

  // create normalization matrix N
  // clang-format off
  N << 2.0 / image_width, 0.0, -1.0,
       0.0, 2.0 / image_height, -1.0,
       0.0, 0.0, 1.0;
  // clang-format on

  // normalize image points to camera center
  pts_h = (N * pts_h.transpose()).transpose();

  // convert back to 2d coordinates
  for (int i = 0; i < pts.rows(); i++) {
    pts(i, 0) = pts_h(i, 0);
    pts(i, 1) = pts_h(i, 1);
  }
}

}  // end of yarl namespace
