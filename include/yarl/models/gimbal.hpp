#ifndef YARL_MODELS_GIMBAL_HPP
#define YARL_MODELS_GIMBAL_HPP

#include <float.h>
#include <iostream>
#include <iomanip>

#include "yarl/utils/utils.hpp"
#include "yarl/control/gimbal/attitude.hpp"

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
  GimbalModel(const VecX &pose);
  int update(const Vec3 &motor_inputs, double dt);
  Vec3 attitudeControllerControl(double dt);
  void setFrameOrientation(const Quaternion &frame_if);
  void setAttitude(const Vec3 &euler_if);
  Vec3 getTargetInBF(const Vec3 &target_cf);
  Vec3 getTargetInBPF(const Vec3 &target_cf,
                      const Quaternion &body_if,
                      const Quaternion &joint_bf);
  void trackTarget(const Vec3 &target_cf);
  Vec4 getState(void);
  void printState(void);
};

}  // end of yarl namespace
#endif
