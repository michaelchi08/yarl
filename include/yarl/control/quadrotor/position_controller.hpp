#ifndef YARL_CONTROL_QUADROTOR_POSITION_CONTROLLER_HPP
#define YARL_CONTROL_QUADROTOR_POSITION_CONTROLLER_HPP

#include <float.h>
#include <iostream>

#include "yarl/utils/utils.hpp"
#include "yarl/control/pid.hpp"

namespace yarl {

class PositionController {
public:
  double dt;
  Vec4 outputs;

  PID x_controller;
  PID y_controller;
  PID z_controller;

  PositionController(void);
  Vec4 calculate(Vec3 setpoints, Vec4 actual, double yaw, double dt);
};

}  // end of yarl namespace
#endif
