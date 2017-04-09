#ifndef YARL_MODELS_QUADROTOR_HPP
#define YARL_MODELS_QUADROTOR_HPP

#include <float.h>
#include <iostream>

#include "yarl/utils/utils.hpp"
#include "yarl/control/quadrotor/attitude_controller.hpp"
#include "yarl/control/quadrotor/position_controller.hpp"

namespace yarl {

class QuadrotorModel {
public:
  VecX states;
  double Ix;
  double Iy;
  double Iz;

  double kr;
  double kt;

  double l;
  double d;

  double m;
  double g;

  Vec4 attitude_setpoints;
  VecX position_setpoints;

  AttitudeController attitude_controller;
  PositionController position_controller;

  QuadrotorModel(void);
  QuadrotorModel(VecX pose);
  int update(VecX motor_inputs, double dt);
  VecX attitudeControllerControl(double dt);
  VecX positionControllerControl(double dt);
  VecX velocityControllerControl(double dt);
  void setAttitude(double roll, double pitch, double yaw, double z);
  void setPosition(double x, double y, double z);
  void setVelocity(double vx, double vy, double vz);
  VecX getPose(void);
  VecX getVelocity(void);
  void printState(void);
};

}  // end of yarl namespace
#endif
