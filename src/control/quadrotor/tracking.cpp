#include "yarl/control/quadrotor/tracking.hpp"


namespace yarl {

int TrackingController::configure(const std::string &config_file) {
  ConfigParser parser;

  // load config
  // clang-format off
  parser.addParam<double>("roll_controller.k_p", &this->y_controller.k_p);
  parser.addParam<double>("roll_controller.k_i", &this->y_controller.k_i);
  parser.addParam<double>("roll_controller.k_d", &this->y_controller.k_d);

  parser.addParam<double>("pitch_controller.k_p", &this->x_controller.k_p);
  parser.addParam<double>("pitch_controller.k_i", &this->x_controller.k_i);
  parser.addParam<double>("pitch_controller.k_d", &this->x_controller.k_d);

  parser.addParam<double>("throttle_controller.k_p", &this->z_controller.k_p);
  parser.addParam<double>("throttle_controller.k_i", &this->z_controller.k_i);
  parser.addParam<double>("throttle_controller.k_d", &this->z_controller.k_d);
  parser.addParam<double>("throttle_controller.hover_throttle", &this->hover_throttle);

  parser.addParam<double>("roll_limit.min", &this->roll_limit[0]);
  parser.addParam<double>("roll_limit.max", &this->roll_limit[1]);

  parser.addParam<double>("pitch_limit.min", &this->pitch_limit[0]);
  parser.addParam<double>("pitch_limit.max", &this->pitch_limit[1]);

  parser.addParam<Vec3>("track_offset", &this->track_offset);
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

AttitudeCommand TrackingController::update(const Vec3 &errors,
                                           double yaw,
                                           double dt) {
  double r, p, y, t;
  Vec3 euler;
  Mat3 R;

  // check rate
  this->dt += dt;
  if (this->dt < 0.01) {
    return this->outputs;
  }

  // add offsets
  errors = errors + this->track_offset;

  // roll, pitch, yaw and throttle (assuming NWU frame)
  // clang-format off
  r = -this->y_controller.update(errors(1), 0.0, this->dt);
  p = this->x_controller.update(errors(0), 0.0, this->dt);
  y = yaw;
  t = this->hover_throttle + this->z_controller.update(errors(2), 0.0, this->dt);
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
  this->setpoints = errors;
  this->outputs << r, p, y, t;
  this->dt = 0.0;

  return AttitudeCommand(this->outputs);
}

AttitudeCommand TrackingController::update(const Vec3 &target_pos_bf,
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
  double r, p, t;

  r = rad2deg(this->outputs(0));
  p = rad2deg(this->outputs(1));
  t = this->outputs(3);

  std::cout << "roll: " << std::setprecision(2) << r << "\t";
  std::cout << "pitch: " << std::setprecision(2) << p << "\t";
  std::cout << "throttle: " << std::setprecision(2) << t << std::endl;
}

void TrackingController::printErrors() {
  double p, i, d;

  p = this->x_controller.error_p;
  i = this->x_controller.error_i;
  d = this->x_controller.error_d;

  std::cout << "x_controller: " << std::endl;
  std::cout << "\terror_p: " << std::setprecision(2) << p << "\t";
  std::cout << "\terror_i: " << std::setprecision(2) << i << "\t";
  std::cout << "\terror_d: " << std::setprecision(2) << i << std::endl;

  p = this->y_controller.error_p;
  i = this->y_controller.error_i;
  d = this->y_controller.error_d;

  std::cout << "y_controller: " << std::endl;
  std::cout << "\terror_p: " << std::setprecision(2) << p << "\t";
  std::cout << "\terror_i: " << std::setprecision(2) << i << "\t";
  std::cout << "\terror_d: " << std::setprecision(2) << i << std::endl;

  p = this->z_controller.error_p;
  i = this->z_controller.error_i;
  d = this->z_controller.error_d;

  std::cout << "z_controller: " << std::endl;
  std::cout << "\terror_p: " << std::setprecision(2) << p << "\t";
  std::cout << "\terror_i: " << std::setprecision(2) << i << "\t";
  std::cout << "\terror_d: " << std::setprecision(2) << i << std::endl;
}

}  // end of yarl namespace
