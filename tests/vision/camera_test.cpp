#include "yarl/test.hpp"
#include "yarl/vision/camera.hpp"

#define CALIB_FILE "tests/data/vision/camera/config.yaml"

namespace yarl {

// TEST(Camera, constructor) {
//   Camera camera;
//
//   EXPECT_EQ(false, camera.configured);
//   EXPECT_EQ(NULL, camera.capture);
//   EXPECT_EQ(0, camera.capture_index);
//   EXPECT_EQ(0, camera.image_width);
//   EXPECT_EQ(0, camera.image_height);
// }
//
// TEST(Camera, configure) {
//   int retval;
//   cv::Mat image;
//   Camera camera;
//
//   // configure camera with index, image dimensions
//   retval = camera.configure(0, 320, 240);
//   EXPECT_EQ(0, retval);
//   camera.close();
//
//   // configure camera with index, calibration file
//   camera.configure(0, CALIB_FILE);
//   EXPECT_EQ(0, retval);
//   camera.close();
// }
//
// TEST(Camera, getFrame) {
//   Camera camera;
//   cv::Mat image;
//
//   // configure camera with index, image dimensions
//   camera.configure(0, 320, 240);
//   for (int i = 0; i < 10; i++) {
//     camera.getFrame(image);
//     // cv::imshow("test", image);
//     // cv::waitKey(1);
//   }
//   camera.close();
// }

}  // end of yarl namespace
