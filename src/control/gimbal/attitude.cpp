#include "yarl/control/gimbal/attitude.hpp"

namespace yarl {
namespace control {

VecX AttitudeController::update(const Vec3 &setpoints,
                                const Vec3 &actual,
                                double dt) {
  // check rate
  this->dt += dt;
  if (this->dt < 0.001) {
    return this->outputs;
  }

  // roll pitch yaw
  Vec3 outputs;
  outputs(0) = this->roll_controller.update(setpoints(0), actual(0), dt);
  outputs(1) = this->pitch_controller.update(setpoints(1), actual(1), dt);
  outputs(2) = 0.0;

  // keep track of outputs
  this->outputs = outputs;
  this->dt = 0.0;

  return outputs;
}

}  // namespace control
}  // namespace yarl
