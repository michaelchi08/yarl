#ifndef YARL_CONTROL_QUADROTOR_VELOCITY_HPP
#define YARL_CONTROL_QUADROTOR_VELOCITY_HPP

#include <iomanip>

#include "yarl/utils/utils.hpp"
#include "yarl/control/pid.hpp"

namespace yarl {

class VelocityController {
public:
  bool configured;

  double dt;
  PID vx_controller;
  PID vy_controller;
  PID vz_controller;

  double roll_limit[2];
  double pitch_limit[2];
  double throttle_limit[2];

  Vec3 setpoints;
  Vec4 outputs;
  Vec4 att_cmd;

  VelocityController(void);
  int configure(std::string config_file);
  Vec4 calculate(Vec3 setpoints, Vec3 actual, double dt);
  void reset(void);
  void printOutputs(void);
  void printErrors(void);
};

}  // end of fs namespace
#endif
