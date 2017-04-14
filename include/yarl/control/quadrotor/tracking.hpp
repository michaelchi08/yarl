#ifndef YARL_CONTROL_QUADROTOR_TRACKING_HPP
#define YARL_CONTROL_QUADROTOR_TRACKING_HPP

#include <iomanip>

#include "yarl/utils/utils.hpp"
#include "yarl/control/pid_controller.hpp"

namespace yarl {

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
  AttitudeCommand att_cmd;

  TrackingController(void);
  int configure(const std::string &config_file);
  AttitudeCommand calculate(const Vec3 &errors, double yaw, double dt);
  AttitudeCommand calculate(const Vec3 &target_pos_bf,
                            const Vec3 &pos,
                            const Vec3 &pos_prev,
                            double yaw,
                            double dt);
  void reset(void);
  void printOutputs(void);
  void printErrors(void);
};

}  // end of yarl namespace
#endif
