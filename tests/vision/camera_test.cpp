#include "yarl/vision/camera.hpp"
#include "yarl/yarl_test.hpp"

#define CALIB_FILE "tests/data/vision/camera/config.yaml"

namespace yarl {

TEST(Camera, constructor) {
  Camera camera;

  ASSERT_EQ(false, camera.configured);
  ASSERT_EQ(NULL, camera.capture);
  ASSERT_EQ(0, camera.capture_index);
  ASSERT_EQ(0, camera.image_width);
  ASSERT_EQ(0, camera.image_height);
}

TEST(Camera, configure) {
  int retval;
  cv::Mat image;
  Camera camera;

  // configure camera with index, image dimensions
  retval = camera.configure(0, 320, 240);
  ASSERT_EQ(0, retval);
  camera.close();

  // configure camera with index, calibration file
  camera.configure(0, CALIB_FILE);
  ASSERT_EQ(0, retval);
  camera.close();
}

TEST(Camera, getFrame) {
  Camera camera;
  cv::Mat image;

  // configure camera with index, image dimensions
  camera.configure(0, 320, 240);
  for (int i = 0; i < 10; i++) {
    camera.getFrame(image);
    // cv::imshow("test", image);
    // cv::waitKey(1);
  }
  camera.close();
}

}  // end of yarl namespace
