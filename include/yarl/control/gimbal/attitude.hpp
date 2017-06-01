#ifndef YARL_CONTROL_GIMBAL_ATTITUDE_CONTROLLER_HPP
#define YARL_CONTROL_GIMBAL_ATTITUDE_CONTROLLER_HPP

#include <float.h>
#include <iostream>

#include "yarl/utils/utils.hpp"
#include "yarl/control/pid.hpp"

namespace yarl {
namespace control {

/**
 * Attitude controller for a 2-axis Gimbal
 */
class AttitudeController {
public:
  PID roll_controller;
  PID pitch_controller;

  double dt;
  Vec3 outputs;

  AttitudeController()
    : roll_controller(0.3, 0.0, 0.2),
      pitch_controller(0.3, 0.0, 0.2),
      dt(0.0),
      outputs(0.0, 0.0, 0.0) {}

  VecX update(const Vec3 &setpoints, const Vec3 &actual, double dt);
};

}  // end of control namespace
}  // namespace yarl
#endif
