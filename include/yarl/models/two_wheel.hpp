#ifndef YARL_MODELS_TWO_WHEEL_HPP
#define YARL_MODELS_TWO_WHEEL_HPP

#include "yarl/utils/utils.hpp"

namespace yarl {

Vec3 two_wheel_model(Vec3 x, Vec2 u, float dt);
Mat3 two_wheel_linearized_model(Vec3 x, Vec2 u, float dt);

}  // end of yarl namespace
#endif
