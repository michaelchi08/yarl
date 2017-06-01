#ifndef YARL_MODELS_TWO_WHEEL_HPP
#define YARL_MODELS_TWO_WHEEL_HPP

#include "yarl/utils/utils.hpp"

namespace yarl {

/** Generic two wheel robot motion model */
class TwoWheelRobot2DModel {
public:
  /** Robot pose consisting of position in x and y (meters) and heading
   * (radians) */
  Vec3 pose;

  TwoWheelRobot2DModel() : pose{0.0, 0.0, 0.0} {}
  explicit TwoWheelRobot2DModel(const Vec3 &pose) : pose{pose} {}

  /** Update two wheel model
   *
   * @param inputs Model input vector where first input is wheel velocity in
   * m/s and the second input is heading angular velocity rad/s
   *
   * @param dt Update time step in seconds
   *
   * @returns Updated pose of two wheel robot
   */
  Vec3 update(const Vec2 &inputs, double dt);
};

Mat3 two_wheel_linearized_model(const Vec3 x, const Vec2 &u, float dt);
Vec4 two_wheel_3d_model(const Vec4 &x, Vec3 &u, float dt);

}  // namespace yarl
#endif
