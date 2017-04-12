#include "yarl/control/gimbal/attitude.hpp"

namespace yarl {

AttitudeController::AttitudeController(void) {
  this->roll_controller = PID(0.3, 0.0, 0.2);
  this->pitch_controller = PID(0.3, 0.0, 0.2);
}

VecX AttitudeController::calculate(Vec3 setpoints, Vec3 actual, double dt) {
  Vec3 outputs;

  // check rate
  this->dt += dt;
  if (this->dt < 0.001) {
    return this->outputs;
  }

  // roll pitch yaw
  outputs(0) = this->roll_controller.calculate(setpoints(0), actual(0), dt);
  outputs(1) = this->pitch_controller.calculate(setpoints(1), actual(1), dt);
  outputs(2) = 0.0;

  // keep track of outputs
  this->outputs = outputs;
  this->dt = 0.0;

  return outputs;
}

}  // end of yarl namespace
