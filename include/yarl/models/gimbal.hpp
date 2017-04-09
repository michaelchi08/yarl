#ifndef YARL_MODELS_GIMBAL_HPP
#define YARL_MODELS_GIMBAL_HPP

#include <float.h>
#include <iostream>
#include <iomanip>

#include "yarl/utils/utils.hpp"
#include "yarl/control/gimbal/attitude_controller.hpp"

namespace yarl {

class GimbalModel {
public:
  VecX states;

  double Ix;
  double Iy;
  Pose camera_offset;

  Vec3 joint_setpoints;
  AttitudeController joint_controller;

  Quaternion frame_orientation;
  Quaternion joint_orientation;
  Vec3 target_attitude_if;

  GimbalModel(void);
  GimbalModel(VecX pose);
  int update(Vec3 motor_inputs, double dt);
  Vec3 attitudeControllerControl(double dt);
  void setFrameOrientation(Quaternion frame_if);
  void setAttitude(Vec3 euler_if);
  Vec3 getTargetInBF(Vec3 target_cf);
  Vec3 getTargetInBPF(Vec3 target_cf,
                      Quaternion body_if,
                      Quaternion joint_bf);
  void trackTarget(Vec3 target_cf);
  Vec4 getState(void);
  void printState(void);
};

}  // end of yarl namespace
#endif
