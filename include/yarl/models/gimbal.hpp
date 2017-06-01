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
  Vec4 states;

  Pose camera_offset;
  double Ix;
  double Iy;

  Vec3 joint_setpoints;
  control::AttitudeController joint_controller;

  Quaternion frame_orientation;
  Quaternion joint_orientation;
  Vec3 target_attitude_if;

  GimbalModel()
    : states(0.0, 0.0, 0.0, 0.0),

      // downward facing camera (gimbal is NWU frame)
      // NWU frame: (x - forward, y - left, z - up)
      camera_offset(0.0, deg2rad(90.0), 0.0, 0.0, 0.0, 0.0),
      Ix(0.01),
      Iy(0.01),

      joint_setpoints(0.0, 0.0, 0.0),
      joint_controller(),

      frame_orientation(0.0, 0.0, 0.0, 0.0),
      joint_orientation(0.0, 0.0, 0.0, 0.0),
      target_attitude_if(0.0, 0.0, 0.0) {}

  GimbalModel(const VecX &pose)
    : states(pose(0), pose(1), pose(2), pose(3)),

      // downward facing camera (gimbal is NWU frame)
      // NWU frame: (x - forward, y - left, z - up)
      camera_offset(0.0, deg2rad(90.0), 0.0, 0.0, 0.0, 0.0),
      Ix(0.01),
      Iy(0.01),

      joint_setpoints(0.0, 0.0, 0.0),
      joint_controller(),

      frame_orientation(0.0, 0.0, 0.0, 0.0),
      joint_orientation(0.0, 0.0, 0.0, 0.0),
      target_attitude_if(0.0, 0.0, 0.0) {}

  int update(const Vec3 &motor_inputs, double dt);
  Vec3 attitudeControllerControl(double dt);
  void setFrameOrientation(const Quaternion &frame_if);
  void setAttitude(const Vec3 &euler_if);
  Vec3 getTargetInBF(const Vec3 &target_cf);
  Vec3 getTargetInBPF(const Vec3 &target_cf,
                      const Quaternion &body_if,
                      const Quaternion &joint_bf);
  void trackTarget(const Vec3 &target_cf);
  Vec4 getState();
  void printState();
};

}  // namespace yarl
#endif
