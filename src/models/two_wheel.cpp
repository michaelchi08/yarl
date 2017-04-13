#include "yarl/models/two_wheel.hpp"

namespace yarl {

Vec3 two_wheel_model(Vec3 x, Vec2 u, float dt) {
  Vec3 g;

  g(0) = x(0) + u(0) * cos(x(2)) * dt;
  g(1) = x(1) + u(0) * sin(x(2)) * dt;
  g(2) = x(2) + u(1) * dt;

  return g;
}

Mat3 two_wheel_linearized_model(Vec3 x, Vec2 u, float dt) {
  Mat3 G;

  // clang-format off
  G << 1.0, 0.0, (-u(0) * sin(x(2)) * dt),
       0.0, 1.0, (u(0) * cos(x(2)) * dt),
       0.0, 0.0, 1.0;
  // clang-format on

  return G;
}

Vec4 two_wheel_3d_model(Vec4 x, Vec3 u, float dt) {
  Vec4 g;

  g(0) = x(0) + u(0) * cos(x(3)) * dt;
  g(1) = x(1) + u(0) * sin(x(3)) * dt;
  g(2) = x(2) + u(1) * dt;
  g(3) = x(3) + u(2) * dt;

  return g;
}


}  // end of yarl namespace
