#include "yarl/control/quadrotor/attitude.hpp"

namespace yarl {

Vec4 AttitudeController::calculate(const Vec4 &setpoints,
                                   const Vec4 &actual,
                                   double dt) {
  // check rate
  this->dt += dt;
  if (this->dt < 0.001) {
    return this->outputs;
  }

  // calculate yaw error
  double actual_yaw = rad2deg(actual(2));
  double setpoint_yaw = rad2deg(setpoints(2));
  double error_yaw = setpoint_yaw - actual_yaw;
  if (error_yaw > 180.0) {
    error_yaw -= 360.0;
  } else if (error_yaw < -180.0) {
    error_yaw += 360.0;
  }
  error_yaw = deg2rad(error_yaw);

  // roll pitch yaw
  double r, p, y;
  r = this->roll_controller.calculate(setpoints(0), actual(0), this->dt);
  p = this->pitch_controller.calculate(setpoints(1), actual(1), this->dt);
  y = this->yaw_controller.calculate(error_yaw, 0.0, this->dt);

  // thrust
  double max_thrust = 5.0;
  double t = max_thrust * setpoints(3);   // convert relative to true thrust
  t = (t > max_thrust) ? max_thrust : t;  // limit thrust
  t = (t < 0) ? 0.0 : t;                  // limit thrust

  // map roll, pitch, yaw and thrust to motor outputs
  Vec4 outputs;
  outputs(0) = -p - y + t;
  outputs(1) = -r + y + t;
  outputs(2) = p - y + t;
  outputs(3) = r + y + t;

  // limit outputs
  for (int i = 0; i < 4; i++) {
    if (outputs(i) > max_thrust) {
      outputs(i) = max_thrust;
    } else if (outputs(i) < 0.0) {
      outputs(i) = 0.0;
    }
  }

  // keep track of outputs
  this->outputs = outputs;
  this->dt = 0.0;

  return outputs;
}

Vec4 AttitudeController::calculate(const Vec4 &psetpoints,
                                   const Vec4 &vsetpoints,
                                   const Vec4 &actual,
                                   double dt) {
  Vec4 setpoints;
  setpoints = psetpoints + vsetpoints;
  return this->calculate(setpoints, actual, dt);
}

}  // end of yarl namespace
