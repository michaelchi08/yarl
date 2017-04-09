#include "yarl/control/quadrotor/position_controller.hpp"

namespace yarl {

PositionController::PositionController(void) {
  this->dt = 0.0;
  this->outputs << 0.0, 0.0, 0.0, 0.0;

  this->x_controller = PID(0.5, 0.0, 0.035);
  this->y_controller = PID(0.5, 0.0, 0.035);
  this->z_controller = PID(0.3, 0.0, 0.018);
}

Vec4 PositionController::calculate(Vec3 setpoints,
                                   Vec4 actual,
                                   double yaw,
                                   double dt) {
  double r, p, y, t;
  Vec3 errors, euler;
  Vec4 outputs;
  Mat3 R;

  // check rate
  this->dt += dt;
  if (this->dt < 0.01) {
    return this->outputs;
  }

  // calculate RPY errors relative to quadrotor by incorporating yaw
  errors(0) = setpoints(0) - actual(0);
  errors(1) = setpoints(1) - actual(1);
  errors(2) = setpoints(2) - actual(2);
  euler << 0.0, 0.0, actual(3);
  euler2rot(euler, 123, R);
  errors = R * errors;

  // roll, pitch, yaw and thrust
  r = -this->y_controller.calculate(errors(1), 0.0, dt);
  p = this->x_controller.calculate(errors(0), 0.0, dt);
  y = yaw;
  t = 0.5 + this->z_controller.calculate(errors(2), 0.0, dt);
  outputs << r, p, y, t;

  // limit roll, pitch
  for (int i = 0; i < 2; i++) {
    if (outputs(i) > deg2rad(30.0)) {
      outputs(i) = deg2rad(30.0);
    } else if (outputs(i) < deg2rad(-30.0)) {
      outputs(i) = deg2rad(-30.0);
    }
  }

  // limit yaw
  while (outputs(2) > deg2rad(360.0)) {
    outputs(2) -= deg2rad(360.0);
  }
  while (outputs(2) < deg2rad(0.0)) {
    outputs(2) += deg2rad(360.0);
  }

  // limit thrust
  if (outputs(3) > 1.0) {
    outputs(3) = 1.0;
  } else if (outputs(3) < 0.0) {
    outputs(3) = 0.0;
  }

  // yaw first if threshold reached
  if (fabs(yaw - actual(3)) > deg2rad(2)) {
    outputs(0) = 0.0;
    outputs(1) = 0.0;
  }

  // keep track of outputs
  this->outputs = outputs;
  this->dt = 0.0;

  return outputs;
}


}  // end of yarl namespace
