#include "yarl/control/quadrotor/tracking.hpp"

namespace yarl {
namespace control {

int TrackingController::configure(const std::string &config_file) {
  ConfigParser parser;

  // load config
  // clang-format off
  parser.addParam("roll_controller.k_p", &this->y_controller.k_p);
  parser.addParam("roll_controller.k_i", &this->y_controller.k_i);
  parser.addParam("roll_controller.k_d", &this->y_controller.k_d);

  parser.addParam("pitch_controller.k_p", &this->x_controller.k_p);
  parser.addParam("pitch_controller.k_i", &this->x_controller.k_i);
  parser.addParam("pitch_controller.k_d", &this->x_controller.k_d);

  parser.addParam("throttle_controller.k_p", &this->z_controller.k_p);
  parser.addParam("throttle_controller.k_i", &this->z_controller.k_i);
  parser.addParam("throttle_controller.k_d", &this->z_controller.k_d);
  parser.addParam("throttle_controller.hover_throttle", &this->hover_throttle);

  parser.addParam("roll_limit.min", &this->roll_limit[0]);
  parser.addParam("roll_limit.max", &this->roll_limit[1]);

  parser.addParam("pitch_limit.min", &this->pitch_limit[0]);
  parser.addParam("pitch_limit.max", &this->pitch_limit[1]);

  parser.addParam("track_offset", &this->track_offset);
  // clang-format on
  if (parser.load(config_file) != 0) {
    return -1;
  }

  // convert roll and pitch limits from degrees to radians
  this->roll_limit[0] = deg2rad(this->roll_limit[0]);
  this->roll_limit[1] = deg2rad(this->roll_limit[1]);
  this->pitch_limit[0] = deg2rad(this->pitch_limit[0]);
  this->pitch_limit[1] = deg2rad(this->pitch_limit[1]);

  // initialize setpoints to zero
  this->setpoints << 0.0, 0.0, 0.0;
  this->outputs << 0.0, 0.0, 0.0, 0.0;

  this->configured = true;
  return 0;
}

Vec4 TrackingController::update(const Vec3 &errors, double yaw, double dt) {
  double r, p, y, t;
  Vec3 err, euler;
  Mat3 R;

  // check rate
  this->dt += dt;
  if (this->dt < 0.01) {
    return this->outputs;
  }

  // add offsets
  err = errors + this->track_offset;

  // roll, pitch, yaw and throttle (assuming NWU frame)
  // clang-format off
  r = -this->y_controller.update(err(1), 0.0, this->dt);
  p = this->x_controller.update(err(0), 0.0, this->dt);
  y = yaw;
  t = this->hover_throttle + this->z_controller.update(err(2), 0.0, this->dt);
  t /= fabs(cos(r) * cos(p));  // adjust throttle for roll and pitch
  // clang-format o

  // limit roll, pitch
  r = (r < this->roll_limit[0]) ? this->roll_limit[0] : r;
  r = (r > this->roll_limit[1]) ? this->roll_limit[1] : r;
  p = (p < this->pitch_limit[0]) ? this->pitch_limit[0] : p;
  p = (p > this->pitch_limit[1]) ? this->pitch_limit[1] : p;

  // limit throttle
  t = (t < 0) ? 0.0 : t;
  t = (t > 1.0) ? 1.0 : t;

  // keep track of setpoints and outputs
  this->setpoints = err;
  this->outputs << r, p, y, t;
  this->dt = 0.0;

  return this->outputs;
}

Vec4 TrackingController::update(const Vec3 &target_pos_bf,
                                              const Vec3 &pos,
                                              const Vec3 &pos_prev,
                                              double yaw,
                                              double dt) {
  Vec3 errors;
  errors(0) = target_pos_bf(0);
  errors(1) = target_pos_bf(1);
  errors(2) = pos_prev(2) - pos(2);

  return this->update(errors, yaw, dt);
}

void TrackingController::reset() {
  this->x_controller.reset();
  this->y_controller.reset();
  this->z_controller.reset();
}

void TrackingController::printOutputs() {
  double r = rad2deg(this->outputs(0));
  double p = rad2deg(this->outputs(1));
  double t = this->outputs(3);

  std::cout << "roll: " << std::setprecision(2) << r << "\t";
  std::cout << "pitch: " << std::setprecision(2) << p << "\t";
  std::cout << "throttle: " << std::setprecision(2) << t << std::endl;
}

void TrackingController::printErrors() {
  double p = this->x_controller.error_p;
  double i = this->x_controller.error_i;
  double d = this->x_controller.error_d;

  std::cout << "x_controller: " << std::endl;
  std::cout << "\terror_p: " << std::setprecision(2) << p << "\t";
  std::cout << "\terror_i: " << std::setprecision(2) << i << "\t";
  std::cout << "\terror_d: " << std::setprecision(2) << d << std::endl;

  p = this->y_controller.error_p;
  i = this->y_controller.error_i;
  d = this->y_controller.error_d;

  std::cout << "y_controller: " << std::endl;
  std::cout << "\terror_p: " << std::setprecision(2) << p << "\t";
  std::cout << "\terror_i: " << std::setprecision(2) << i << "\t";
  std::cout << "\terror_d: " << std::setprecision(2) << d << std::endl;

  p = this->z_controller.error_p;
  i = this->z_controller.error_i;
  d = this->z_controller.error_d;

  std::cout << "z_controller: " << std::endl;
  std::cout << "\terror_p: " << std::setprecision(2) << p << "\t";
  std::cout << "\terror_i: " << std::setprecision(2) << i << "\t";
  std::cout << "\terror_d: " << std::setprecision(2) << d << std::endl;
}

}  // end of control namespace
}  // end of yarl namespace
