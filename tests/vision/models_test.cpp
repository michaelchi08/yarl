#include "yarl/test.hpp"
#include "yarl/vision/models.hpp"

namespace yarl {

TEST(CameraModel, constructor) {
  // TEST DEFAULT CONSTRUCTOR
  CameraModel cam;

  EXPECT_TRUE(cam.t.isApprox(Vec3::Zero()));
  EXPECT_TRUE(cam.R.isApprox(Mat3::Identity()));

  // TEST TRANSLATION AND ROTATION MATRIX CONSTRUCTOR
  Vec3 t = Vec3{1.0, 2.0, 3.0};
  Mat3 R = Mat3::Random(3, 3);
  CameraModel cam1{t, R};

  EXPECT_TRUE(cam1.t.isApprox(t));
  EXPECT_TRUE(cam1.R.isApprox(R));

  std::cout << cam1.t << std::endl;
  std::cout << cam1.R << std::endl;
}

TEST(PinholeModel, constructor) {
  PinholeModel cam;

  EXPECT_TRUE(cam.t.isApprox(Vec3::Zero()));
  EXPECT_TRUE(cam.R.isApprox(Mat3::Identity()));
}


}  // namespace yarl
