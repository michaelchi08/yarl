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

void cvpts2mat(const std::vector<cv::Point2f> &points, MatX &mat) {
  cv::Point2f p;

  mat.resize(points.size(), 3);
  for (size_t i = 0; i < points.size(); i++) {
    p = points[i];
    mat(i, 0) = p.x;
    mat(i, 1) = p.y;
    mat(i, 2) = 1.0;
  }
}

void projection_matrix(const Mat3 &K, const Mat3 &R, const Vec3 &t, MatX &P) {
  MatX extrinsics;

  extrinsics.resize(3, 4);
  extrinsics.block(0, 0, 3, 3) = R;
  extrinsics.block(0, 3, 3, 1) = t;

  P.resize(3, 4);
  P = K * extrinsics;
}

}  // namespace yarl
