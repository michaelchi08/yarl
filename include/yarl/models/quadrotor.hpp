#ifndef YARL_MODELS_QUADROTOR_HPP
#define YARL_MODELS_QUADROTOR_HPP

#include <float.h>
#include <iostream>

#include "yarl/utils/utils.hpp"
#include "yarl/control/quadrotor/attitude.hpp"
#include "yarl/control/quadrotor/position.hpp"

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
  Vec3 position_setpoints;

  control::AttitudeController attitude_controller;
  control::PositionController position_controller;

  QuadrotorModel()
    : states(),

      Ix(0.0963),
      Iy(0.0963),
      Iz(0.1927),

      kr(0.1),
      kt(0.2),

      l(0.9),
      d(1.0),

      m(1.0),
      g(10.0),

      attitude_setpoints(0.0, 0.0, 0.0, 0.5),
      position_setpoints(0.0, 0.0, 0.0),

      attitude_controller(),
      position_controller() {}

  QuadrotorModel(const VecX &pose)
    : states(),

      Ix(0.0963),
      Iy(0.0963),
      Iz(0.1927),

      kr(0.1),
      kt(0.2),

      l(0.9),
      d(1.0),

      m(1.0),
      g(10.0),

      attitude_setpoints(0.0, 0.0, 0.0, 0.5),
      position_setpoints(0.0, 0.0, 0.0),

      attitude_controller(),
      position_controller() {
    this->states.resize(12);
    this->states(0) = pose(3);  // roll
    this->states(1) = pose(4);  // pitch
    this->states(2) = pose(5);  // yaw

    this->states(6) = pose(0);  // x
    this->states(7) = pose(1);  // y
    this->states(8) = pose(2);  // z
  }

  int update(const VecX &motor_inputs, double dt);
  Vec4 attitudeControllerControl(double dt);
  Vec4 positionControllerControl(double dt);
  void setAttitude(double roll, double pitch, double yaw, double z);
  void setPosition(double x, double y, double z);
  void setVelocity(double vx, double vy, double vz);
  VecX getPose();
  VecX getVelocity();
  void printState();
};

}  // namespace yarl
#endif
