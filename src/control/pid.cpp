#include "yarl/control/pid.hpp"

namespace yarl {
namespace control {

double PID::update(double setpoint, double actual, double dt) {
  // update errors
  double error = setpoint - actual;
  this->error_sum += error * dt;

  // update output
  this->error_p = this->k_p * error;
  this->error_i = this->k_i * this->error_sum;
  this->error_d = this->k_d * (error - this->error_prev) / dt;
  double output = this->error_p + this->error_i + this->error_d;

  // update error
  this->error_prev = error;

  return output;
}

}  // end of control namespace
}  // end of yarl namespace
