#ifndef YARL_CONTROL_QUADROTOR_TRACKING_HPP
#define YARL_CONTROL_QUADROTOR_TRACKING_HPP

#include <iomanip>

#include "yarl/utils/utils.hpp"
#include "yarl/control/pid.hpp"

namespace yarl {
namespace control {

class TrackingController {
public:
  bool configured;

  double dt;
  PID x_controller;
  PID y_controller;
  PID z_controller;

  double hover_throttle;
  double roll_limit[2];
  double pitch_limit[2];
  Vec3 track_offset;

  Vec3 setpoints;
  Vec4 outputs;

  TrackingController()
    : configured(false),

      dt(0.0),
      x_controller(0.0, 0.0, 0.0),
      y_controller(0.0, 0.0, 0.0),
      z_controller(0.0, 0.0, 0.0),

      hover_throttle(0.0),
      roll_limit{0.0, 0.0},
      pitch_limit{0.0, 0.0},
      track_offset(0.0, 0.0, 0.0),

      setpoints(0.0, 0.0, 0.0),
      outputs(0.0, 0.0, 0.0, 0.0) {}

  int configure(const std::string &config_file);
  Vec4 update(const Vec3 &errors, double yaw, double dt);
  Vec4 update(const Vec3 &target_pos_bf,
              const Vec3 &pos,
              const Vec3 &pos_prev,
              double yaw,
              double dt);
  void reset();
  void printOutputs();
  void printErrors();
};

}  // end of control namespace
}  // namespace yarl
#endif
