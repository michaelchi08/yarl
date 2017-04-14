#ifndef YARL_CONTROL_QUADROTOR_LANDING_HPP
#define YARL_CONTROL_QUADROTOR_LANDING_HPP

#include <iomanip>
#include <libgen.h>
#include <string>
#include <deque>

#include "yarl/utils/utils.hpp"
#include "yarl/control/pid.hpp"


namespace yarl {

#define ETROWS "Trajectory [%s] has 0 rows!"
#define ETCOLS "Trajectory [%s] invalid number of cols!"
#define ETLOAD "Failed to load trajectory!"
#define ETIROWS "Trajectory index [%s] has 0 rows!"
#define ETICOLS "Trajectory index [%s] invalid number of cols!"
#define ETIFAIL "Found no trajectory for z = %f, v = %f"
#define TLOAD "Loaded trajectory @ z = %f, v = %f"

class Trajectory {
public:
  bool loaded;
  int index;

  std::deque<Vec2> pos;
  std::deque<Vec2> vel;
  std::deque<Vec2> inputs;
  std::deque<Vec2> rel_pos;
  std::deque<Vec2> rel_vel;
  Vec3 p0;

  Trajectory(void);
  int load(int index, const std::string &filepath, const Vec3 &pos);
  int update(const Vec3 pos, Vec2 &wp_pos, Vec2 &wp_vel, Vec2 &wp_inputs);
  void reset(void);
};

class TrajectoryIndex {
public:
  bool loaded;

  std::string traj_dir;
  MatX index_data;
  double pos_thres;
  double vel_thres;

  TrajectoryIndex(void);
  int load(const std::string &index_file,
           double pos_thres = 0.2,
           double vel_thres = 0.2);
  int find(const Vec3 &pos, double v, const Trajectory &traj);
};

class LandingController {
public:
  bool configured;
  std::string mode;

  double dt;
  double blackbox_dt;

  double vx_error_prev;
  double vy_error_prev;
  double vz_error_prev;

  double vx_error_sum;

  double vx_k_p;
  double vx_k_i;
  double vx_k_d;

  double vy_k_p;
  double vy_k_i;
  double vy_k_d;

  double vz_k_p;
  double vz_k_i;
  double vz_k_d;

  double roll_limit[2];
  double pitch_limit[2];
  double throttle_limit[2];

  Vec3 setpoints;
  Vec4 outputs;
  AttitudeCommand att_cmd;

  TrajectoryIndex traj_index;
  Vec3 trajectory_threshold;
  Trajectory trajectory;

  bool blackbox_enable;
  double blackbox_rate;
  std::ofstream blackbox;

  LandingController(void);
  ~LandingController(void);
  int configure(const std::string &config_file);
  int loadTrajectory(const Vec3 &pos, const Vec3 &target_pos_bf, double v);
  int prepBlackbox(const std::string &blackbox_file);
  int recordTrajectoryIndex(void);
  int record(const Vec3 &pos,
             const Vec3 &vel,
             const Vec2 &wp_pos,
             const Vec2 &wp_vel,
             const Vec2 &wp_inputs,
             const Vec3 &target_pos_bf,
             const Vec3 &target_vel_bf,
             const Vec3 &rpy,
             double thrust,
             double dt);
  Vec4 calculateVelocityErrors(const Vec3 &v_errors,
                               const Vec3 &p_errors,
                               double yaw,
                               double dt);
  int calculate(const Vec3 &target_pos_bf,
                const Vec3 &target_vel_bf,
                const Vec3 &pos,
                const Vec3 &vel,
                const Quaternion &orientation,
                double yaw,
                double dt);
  void reset(void);
  void printOutputs(void);
  void printErrors(void);
};

}  // end of yarl namespace
#endif
