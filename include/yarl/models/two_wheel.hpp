#ifndef YARL_MODELS_TWO_WHEEL_HPP
#define YARL_MODELS_TWO_WHEEL_HPP

#include "yarl/utils/utils.hpp"

namespace yarl {

Vec3 two_wheel_model(const Vec3 &x, const Vec2 &u, float dt);
Mat3 two_wheel_linearized_model(const Vec3 x, const Vec2 &u, float dt);
Vec4 two_wheel_3d_model(const Vec4 &x, Vec3 &u, float dt);

}  // end of yarl namespace
#endif
