#include "yarl/models/two_wheel.hpp"

namespace yarl {

Vec3 TwoWheelRobot2DModel::update(const Vec2 &inputs, double dt) {
  this->pose(0) += inputs(0) * cos(this->pose(2)) * dt;
  this->pose(1) += inputs(0) * sin(this->pose(2)) * dt;
  this->pose(2) += inputs(1) * dt;

  return this->pose;
}

Vec4 two_wheel_3d_model(const Vec4 &x, const Vec3 &u, float dt) {
  Vec4 g;

  g(0) = x(0) + u(0) * cos(x(3)) * dt;
  g(1) = x(1) + u(0) * sin(x(3)) * dt;
  g(2) = x(2) + u(1) * dt;
  g(3) = x(3) + u(2) * dt;

  return g;
}


}  // namespace yarl
