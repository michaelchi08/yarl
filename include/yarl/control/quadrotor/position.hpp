#ifndef YARL_CONTROL_QUADROTOR_POSITION_HPP
#define YARL_CONTROL_QUADROTOR_POSITION_HPP

#include <float.h>
#include <iostream>

#include "yarl/utils/utils.hpp"
#include "yarl/control/pid.hpp"

namespace yarl {
namespace control {

class PositionController {
public:
  PID x_controller;
  PID y_controller;
  PID z_controller;

  double dt;
  Vec4 outputs;

  PositionController()
    : x_controller(0.5, 0.0, 0.035),
      y_controller(0.5, 0.0, 0.035),
      z_controller(0.3, 0.0, 0.018),

      dt(0.0),
      outputs(0.0, 0.0, 0.0, 0.0) {}

  Vec4 update(Vec3 setpoints, Vec4 actual, double yaw, double dt);
};

}  // end of control namespace
}  // namespace yarl
#endif
