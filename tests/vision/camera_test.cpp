#include "yarl/test.hpp"
#include "yarl/vision/camera.hpp"

namespace yarl {

TEST(Camera, constructor) {
  Camera camera;

  EXPECT_FALSE(camera.configured);
  EXPECT_EQ(-1, camera.capture_index);
  EXPECT_EQ(0, camera.image_width);
  EXPECT_EQ(0, camera.image_height);
}

TEST(Camera, configure) {
  int retval;
  cv::Mat image;
  Camera camera;

  // configure camera with index, image dimensions
  retval = camera.configure(0, 320, 240);
  EXPECT_EQ(0, retval);
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
