#ifndef VISION_SFM_HPP
#define VISION_SFM_HPP

#include <iostream>

#include "battery/utils/utils.hpp"
#include "battery/vision/utils.hpp"

namespace battery {

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

} // end of battery namespace
#endif
