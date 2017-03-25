#include "battery/battery_test.hpp"
#include "battery/utils/utils.hpp"
#include "battery/vision/sfm.hpp"
#include "battery/vision/utils.hpp"

#define TEST_DATA_1 "tests/data/pts1.dat"
#define TEST_DATA_2 "tests/data/pts2.dat"

namespace battery {

TEST(SFM, constructor) {
  battery::SFM sfm;
}

TEST(SFM, configure) {
  battery::SFM sfm;
  battery::Mat3 K;

  K << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0;

  sfm.configure(K);
  ASSERT_EQ(true, sfm.configured);
}

TEST(SFM, recoverPose) {
  battery::SFM sfm;
  battery::SFMPose pose;
  battery::Mat3 K;
  battery::MatX pts1, pts2;

  // setup
  K << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0;

  battery::csv2mat(TEST_DATA_1, false, pts1);
  battery::csv2mat(TEST_DATA_2, false, pts2);

  // battery::normalize_2dpts(960, 720, pts1);
  // battery::normalize_2dpts(960, 720, pts2);

  sfm.configure(K);
  std::cout << pts1 << std::endl << std::endl;
  std::cout << pts2 << std::endl << std::endl;

  // test
  sfm.recoverPose(pts1, pts2, pose);
  std::cout << pose.R.eulerAngles(0, 1, 2) << std::endl << std::endl;
  std::cout << pose.t << std::endl;
}

}  // end of battery namespace
