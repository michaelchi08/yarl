#ifndef YARL_VISION_SFM_HPP
#define YARL_VISION_SFM_HPP

#include <iostream>

#include "yarl/utils/utils.hpp"
#include "yarl/vision/utils.hpp"

namespace yarl {

class SFMPose {
public:
  Mat3 R;
  Vec3 t;

  SFMPose(void);
};

class SFM {
public:
  bool configured;
  Mat3 K;

  SFM(void);
  int configure(Mat3 K);
  int recoverPose(MatX pts1, MatX pts2, SFMPose &pose);
};

}  // end of yarl namespace
#endif
