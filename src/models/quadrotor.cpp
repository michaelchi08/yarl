#include "yarl/models/quadrotor.hpp"

namespace yarl {

int QuadrotorModel::update(const VecX &motor_inputs, double dt) {
  double ph = this->states(0);
  double th = this->states(1);
  double ps = this->states(2);

  double p = this->states(3);
  double q = this->states(4);
  double r = this->states(5);

  double x = this->states(6);
  double y = this->states(7);
  double z = this->states(8);

  double vx = this->states(9);
  double vy = this->states(10);
  double vz = this->states(11);

  double Ix = this->Ix;
  double Iy = this->Iy;
  double Iz = this->Iz;

  double kr = this->kr;
  double kt = this->kt;

  double m = this->m;
  double g = this->g;

  // convert motor inputs to angular p, q, r and total thrust
  // clang-format off
  Mat4 A;
  A << 1.0, 1.0, 1.0, 1.0,
       0.0, -this->l, 0.0, this->l,
       -this->l, 0.0, this->l, 0.0,
       -this->d, this->d, -this->d, this->d;
  // clang-format on

  Vec4 tau;
  tau = A * motor_inputs;
  double tauf = tau(0);
  double taup = tau(1);
  double tauq = tau(2);
  double taur = tau(3);

  // update
  // clang-format off
  this->states(0) = ph + (p + q * sin(ph) * tan(th) + r * cos(ph) * tan(th)) * dt;
  this->states(1) = th + (q * cos(ph) - r * sin(ph)) * dt;
  this->states(2) = ps + ((1 / cos(th)) * (q * sin(ph) + r * cos(ph))) * dt;
  this->states(3) = p + (-((Iz - Iy) / Ix) * q * r - (kr * p / Ix) + (1 / Ix) * taup) * dt;
  this->states(4) = q + (-((Ix - Iz) / Iy) * p * r - (kr * q / Iy) + (1 / Iy) * tauq) * dt;
  this->states(5) = r + (-((Iy - Ix) / Iz) * p * q - (kr * r / Iz) + (1 / Iz) * taur) * dt;
  this->states(6) = x + vx * dt;
  this->states(7) = y + vy * dt;
  this->states(8) = z + vz * dt;
  this->states(9) = vx + ((-kt * vx / m) + (1 / m) * (cos(ph) * sin(th) * cos(ps) + sin(ph) * sin(ps)) * tauf) * dt;
  this->states(10) = vy + ((-kt * vy / m) + (1 / m) * (cos(ph) * sin(th) * sin(ps) - sin(ph) * cos(ps)) * tauf) * dt;
  this->states(11) = vz + (-(kt * vz / m) + (1 / m) * (cos(ph) * cos(th)) * tauf - g) * dt;
  // clang-format on

  // constrain yaw to be [-180, 180]
  this->states(2) = rad2deg(this->states(2));
  this->states(2) = wrapTo180(this->states(2));
  this->states(2) = deg2rad(this->states(2));

  return 0;
}

Vec4 QuadrotorModel::attitudeControllerControl(double dt) {
  Vec4 actual_attitude;
  Vec4 motor_inputs;

  // attitude controller
  // clang-format off
  actual_attitude << this->states(0),  // roll
                     this->states(1),  // pitch
                     this->states(2),  // yaw
                     this->states(8);  // z
  motor_inputs = this->attitude_controller.update(this->attitude_setpoints,
                                                     actual_attitude,
                                                     dt);
  // clang-format on

  return motor_inputs;
}

Vec4 QuadrotorModel::positionControllerControl(double dt) {
  Vec4 motor_inputs;
  Vec4 actual_position;
  Vec4 actual_attitude;

  // position controller
  // clang-format off
  actual_position(0) = this->states(6);  // x
  actual_position(1) = this->states(7);  // y
  actual_position(2) = this->states(8);  // z
  actual_position(3) = this->states(2);  // yaw
  this->attitude_setpoints = this->position_controller.update(
    this->position_setpoints,
    actual_position,
    0.0,
    dt
  );

  // attitude controller
  actual_attitude(0) = this->states(0);  // roll
  actual_attitude(1) = this->states(1);  // pitch
  actual_attitude(2) = this->states(2);  // yaw
  actual_attitude(3) = this->states(8);  // z
  motor_inputs = this->attitude_controller.update(
    this->attitude_setpoints,
    actual_attitude,
    dt
  );
  // clang-format on

  return motor_inputs;
}

void QuadrotorModel::setAttitude(double roll,
                                 double pitch,
                                 double yaw,
                                 double z) {
  this->attitude_setpoints(0) = roll;
  this->attitude_setpoints(1) = pitch;
  this->attitude_setpoints(2) = yaw;
  this->attitude_setpoints(3) = z;
}

void QuadrotorModel::setPosition(double x, double y, double z) {
  this->position_setpoints(0) = x;
  this->position_setpoints(1) = y;
  this->position_setpoints(2) = z;
}

VecX QuadrotorModel::getPose() {
  VecX pose(6);

  // x, y, z
  pose(0) = this->states(6);
  pose(1) = this->states(7);
  pose(2) = this->states(8);

  // phi, theta, psi
  pose(3) = this->states(0);
  pose(4) = this->states(1);
  pose(5) = this->states(2);

  return pose;
}

VecX QuadrotorModel::getVelocity() {
  VecX velocities(6);

  // vx, vy, vz
  velocities(0) = this->states(9);
  velocities(1) = this->states(10);
  velocities(2) = this->states(11);

  // phi_dot, theta_dot, psi_dot
  velocities(3) = this->states(3);
  velocities(4) = this->states(4);
  velocities(5) = this->states(5);

  return velocities;
}

void QuadrotorModel::printState() {
  // phi, theta, psi
  float phi = this->states(0);
  float theta = this->states(1);
  float psi = this->states(2);

  // x, y, z
  float x = this->states(6);
  float y = this->states(7);
  float z = this->states(8);

  // print states
  printf("x: %f\t", x);
  printf("y: %f\t", y);
  printf("z: %f\t\t", z);

  printf("phi: %f\t", phi);
  printf("theta: %f\t", theta);
  printf("psi: %f\n", psi);
}

}  // namespace yarl
