#include "yarl/test.hpp"
#include "yarl/vision/utils.hpp"

namespace yarl {

TEST(VisionUtils, focal_length) {
  double f;

  f = focal_length(60, 640);
  std::cout << f << std::endl;
}

TEST(VisionUtils, projection_matrix) {
  Mat3 K;
  Mat3 R;
  Vec3 t;
  MatX P;

  double fx, fy, cx, cy;
  Vec3 rpy;

  Vec4 f_3d;
  Vec3 f_img;

  // setup
  fx = 554.38;
  fy = 554.38;
  cx = 320.0;
  cy = 320.0;

  // clang-format off
  K << fx, 0.0, cx,
       0.0, fy, cy,
       0.0, 0.0, 1.0;

  rpy << deg2rad(0.0), deg2rad(0.0), deg2rad(0.0);
  euler2rot(rpy, 123, R);

  t << 0.0, 0.0, 0.0;
  // clang-format on

  projection_matrix(K, R, t, P);
  f_3d << 0.0, 0.0, 10.0, 1.0;

  f_img = P * f_3d;
  f_img(0) = f_img(0) / f_img(2);
  f_img(1) = f_img(1) / f_img(2);
  f_img(2) = f_img(2) / f_img(2);

  std::cout << "f_3d: " << f_3d.transpose() << std::endl;
  std::cout << "f_img: " << f_img.transpose() << std::endl;
}

}  // end of yarl namespace
