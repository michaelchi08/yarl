#ifndef __VISION_SFM_HPP__
#define __VISION_SFM_HPP__

#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

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
