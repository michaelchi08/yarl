#include "yarl/control/quadrotor/position.hpp"

namespace yarl {

Vec4 PositionController::update(Vec3 setpoints,
                                Vec4 actual,
                                double yaw,
                                double dt) {
  // check rate
  this->dt += dt;
  if (this->dt < 0.01) {
    return this->outputs;
  }

  // update RPY errors relative to quadrotor by incorporating yaw
  Vec3 errors, euler;
  Mat3 R;
  errors(0) = setpoints(0) - actual(0);
  errors(1) = setpoints(1) - actual(1);
  errors(2) = setpoints(2) - actual(2);
  euler << 0.0, 0.0, actual(3);
  euler2rot(euler, 123, R);
  errors = R * errors;

  // roll, pitch, yaw and thrust
  double r = -this->y_controller.update(errors(1), 0.0, dt);
  double p = this->x_controller.update(errors(0), 0.0, dt);
  double y = yaw;
  double t = 0.5 + this->z_controller.update(errors(2), 0.0, dt);
  Vec4 outputs;
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
