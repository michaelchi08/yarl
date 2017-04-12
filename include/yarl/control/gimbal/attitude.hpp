#ifndef YARL_CONTROL_GIMBAL_ATTITUDE_CONTROLLER_HPP
#define YARL_CONTROL_GIMBAL_ATTITUDE_CONTROLLER_HPP

#include <float.h>
#include <iostream>

#include "yarl/utils/utils.hpp"
#include "yarl/control/pid.hpp"

namespace yarl {

class AttitudeController {
public:
  PID roll_controller;
  PID pitch_controller;
  double dt;
  Vec3 outputs;

  AttitudeController(void);
  VecX calculate(Vec3 setpoints, Vec3 actual, double dt);
};

}  // end of yarl namespace
#endif
