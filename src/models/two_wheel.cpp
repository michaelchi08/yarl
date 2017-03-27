#include "yarl/models/two_wheel.hpp"

namespace yarl {

Vec3 two_wheel_model(Vec3 x, Vec2 u, float dt) {
  Vec3 g;

  // clang-format off
  g << x(0) + u(0) * cos(x(2)) * dt,
       x(1) + u(0) * sin(x(2)) * dt,
       x(2) + u(1) * dt;
  // clang-format on

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

}  // end of yarl namespace