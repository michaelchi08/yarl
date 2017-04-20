#ifndef YARL_CONTROL_QUADROTOR_VELOCITY_HPP
#define YARL_CONTROL_QUADROTOR_VELOCITY_HPP

#include <iomanip>

#include "yarl/utils/utils.hpp"
#include "yarl/control/pid.hpp"

namespace yarl {
namespace control {

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


  VelocityController()
    : configured(false),

      dt(0.0),
      vx_controller(0.0, 0.0, 0.0),
      vy_controller(0.0, 0.0, 0.0),
      vz_controller(0.0, 0.0, 0.0),

      roll_limit{0.0, 0.0},
      pitch_limit{0.0, 0.0},
      throttle_limit{0.0, 0.0},

      setpoints(0.0, 0.0, 0.0),
      outputs(0.0, 0.0, 0.0, 0.0),
      att_cmd() {}

  int configure(const std::string &config_file);
  Vec4 update(const Vec3 &setpoints, const Vec3 &actual, double dt);
  void reset();
  void printOutputs();
  void printErrors();
};

}  // end of control namespace
}  // end of fs namespace
#endif
