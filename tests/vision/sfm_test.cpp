#include "yarl/yarl_test.hpp"
#include "yarl/utils/utils.hpp"
#include "yarl/vision/sfm.hpp"
#include "yarl/vision/utils.hpp"

#define TEST_DATA_1 "tests/data/vision/sfm/pts1.dat"
#define TEST_DATA_2 "tests/data/vision/sfm/pts2.dat"

namespace yarl {

TEST(SFM, constructor) {
  yarl::SFM sfm;
}

TEST(SFM, configure) {
  yarl::SFM sfm;
  yarl::Mat3 K;

  K << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0;

  sfm.configure(K);
  ASSERT_EQ(true, sfm.configured);
}

TEST(SFM, recoverPose) {
  yarl::SFM sfm;
  yarl::SFMPose pose;
  yarl::Mat3 K;
  yarl::MatX pts1, pts2;

  // setup
  K << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0;

  yarl::csv2mat(TEST_DATA_1, false, pts1);
  yarl::csv2mat(TEST_DATA_2, false, pts2);

  // yarl::normalize_2dpts(960, 720, pts1);
  // yarl::normalize_2dpts(960, 720, pts2);

  sfm.configure(K);
  std::cout << pts1 << std::endl << std::endl;
  std::cout << pts2 << std::endl << std::endl;

  // test
  // sfm.recoverPose(pts1, pts2, pose);
  // std::cout << pose.R.eulerAngles(0, 1, 2) << std::endl << std::endl;
  // std::cout << pose.t << std::endl;
}

}  // end of yarl namespace
