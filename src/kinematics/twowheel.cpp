#include "battery/kinematics/twowheel.hpp"

namespace battery {

TwoWheelRobotModel::TwoWheelRobotModel(void) {
  this->initialized = false;
}

VecX TwoWheelRobotModel::gFunc(VecX x, VecX u, float dt) {
  VecX g;

  // clang-format off
  g << x(1) + u(1) * cos(x(3)) * dt,
       x(2) + u(1) * sin(x(3)) * dt,
       x(3) + u(2) * dt;
  // clang-format on

  return g;
}

MatX TwoWheelRobotModel::GFunc(VecX x, VecX u, float dt) {
  MatX G;

  // clang-format off
  G << 1.0, 0.0, (-u(1) * sin(x(3)) * dt),
       0.0, 1.0, (u(1) * cos(x(3)) * dt),
       0.0, 0.0, 1.0;
  // clang-format on

  return G;
}

VecX TwoWheelRobotModel::hFunc(VecX x) {
  VecX h;
  MatX H;

  H = MatX::Identity(3, 3);
  h = H * x;

  return h;
}

MatX TwoWheelRobotModel::HFunc(VecX y) {
  MatX H;
  // UNUSED(y);

  H = MatX::Identity(3, 3);

  return H;
}

}  // end of battery namespace
