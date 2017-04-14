#ifndef YARL_CONTROL_QUADROTOR_ATTITUDE_HPP
#define YARL_CONTROL_QUADROTOR_ATTITUDE_HPP

#include <float.h>
#include <iostream>

#include "yarl/utils/utils.hpp"
#include "yarl/control/pid.hpp"

namespace yarl {

class AttitudeController {
public:
  double dt;
  Vec4 outputs;

  PID roll_controller;
  PID pitch_controller;
  PID yaw_controller;

  AttitudeController(void);
  Vec4 calculate(const Vec4 &setpoints, const Vec4 &actual, double dt);
  Vec4 calculate(const Vec4 &psetpoints,
                 const Vec4 &vsetpoints,
                 const Vec4 &actual,
                 double dt);
};

}  // end of yarl namespace
#endif
