#include "yarl/control/quadrotor/landing.hpp"

namespace yarl {
namespace control {

// TRAJECTORY
Trajectory::Trajectory() {
  this->loaded = false;
  this->index = -1;
  this->pos.clear();
  this->vel.clear();
  this->inputs.clear();
  this->rel_pos.clear();
  this->rel_vel.clear();
  this->p0 << 0.0, 0.0, 0.0;
}

int Trajectory::load(int index,
                     const std::string &filepath,
                     const Vec3 &pos) {
  // pre-check
  if (file_exists(filepath) == false) {
    log_error("File not found: %s", filepath.c_str());
    return -1;
  }

  // load trajectory file
  // assumes each column is:
  // - x
  // - vx
  // - z
  // - vz
  // - az
  // - theta
  // - rel_x
  // - rel_z
  // - rel_vx
  // - rel_vz
  MatX traj_data;

  this->reset();
  this->index = index;
  csv2mat(filepath, true, traj_data);
  if (traj_data.rows() == 0) {
    log_error(ETROWS, filepath.c_str());
    return -2;
  } else if (traj_data.cols() != 10) {
    log_error(ETCOLS, filepath.c_str());
    return -2;
  }

  // set trajectory class
  Vec2 p, v, u, rel_p, rel_v;
  for (int i = 0; i < traj_data.rows(); i++) {
    p << traj_data(i, 0), traj_data(i, 2);      // x, z
    v << traj_data(i, 1), traj_data(i, 3);      // vx, vz
    u << traj_data(i, 4), traj_data(i, 5);      // az, theta
    rel_p << traj_data(i, 6), traj_data(i, 7);  // rel_x, rel_z
    rel_v << traj_data(i, 8), traj_data(i, 9);  // rel_vx, rel_vz

    this->pos.push_back(p);
    this->vel.push_back(v);
    this->inputs.push_back(u);
    this->rel_pos.push_back(rel_p);
    this->rel_vel.push_back(rel_v);
  }

  this->p0 = pos;
  this->loaded = true;
  return 0;
}

int Trajectory::update(const Vec3 pos,
                       Vec2 &wp_pos,
                       Vec2 &wp_vel,
                       Vec2 &wp_inputs) {
  // pre-check
  if (this->loaded == false) {
    return -1;
  } else if (this->pos.size() < 2) {
    wp_pos = this->pos.at(0);
    wp_vel = this->vel.at(0);
    wp_inputs = this->inputs.at(0);
    return 0;
  }

  // setup
  Vec2 wp_pos_start = this->pos.at(0);
  Vec2 wp_pos_end = this->pos.at(1);

  Vec2 wp_vel_start = this->vel.at(0);
  Vec2 wp_vel_end = this->vel.at(1);

  Vec2 wp_inputs_start = this->inputs.at(0);
  Vec2 wp_inputs_end = this->inputs.at(1);

  Vec2 q_pos(0) = (this->p0.block(0, 0, 2, 1) - pos.block(0, 0, 2, 1)).norm();
  Vec2 q_pos(1) = pos(2);

  // find next waypoint position, velocity and inputs
  double wp_percent = closest_point(wp_pos_start, wp_pos_end, q_pos, wp_pos);
  wp_vel = linear_interpolation(wp_vel_start, wp_vel_end, wp_percent);
  wp_inputs =
    linear_interpolation(wp_inputs_start, wp_inputs_end, wp_percent);

  // update trajectory waypoints
  if (wp_percent > 1.0) {
    this->pos.pop_front();
    this->vel.pop_front();
    this->inputs.pop_front();
    this->rel_pos.pop_front();
    this->rel_vel.pop_front();
  }

  // debug
  // std::cout << "pos: " << pos.transpose() << std::endl;
  // std::cout << "wp_start: " << wp_pos_start.transpose() << std::endl;
  // std::cout << "wp_end: " << wp_pos_end.transpose() << std::endl;
  // std::cout << "wp_vel: " << wp_vel.transpose() << std::endl;
  // std::cout << "wp: " << wp_pos.transpose() << std::endl;
  // std::cout << "rel_pos: " << this->rel_pos.at(0).transpose() << std::endl;
  // std::cout << "rel_vel: " << this->rel_vel.at(0).transpose() << std::endl;
  // std::cout << "inputs: " << this->inputs.at(0).transpose() << std::endl;
  // std::cout << "nb waypoints left: " << this->pos.size() << std::endl;
  // std::cout << std::endl;

  return 0;
}

void Trajectory::reset() {
  this->loaded = false;
  this->pos.clear();
  this->vel.clear();
  this->inputs.clear();
  this->rel_pos.clear();
  this->rel_vel.clear();
  this->p0 << 0.0, 0.0, 0.0;
}


// TRAJECTORY INDEX
TrajectoryIndex::TrajectoryIndex() {
  this->loaded = false;

  this->traj_dir = "";
  this->index_data = MatX();
  this->pos_thres = 0.0;
  this->vel_thres = 0.0;
}

int TrajectoryIndex::load(const std::string &index_file,
                          double pos_thres,
                          double vel_thres) {
  // pre-check
  if (file_exists(index_file) == false) {
    log_error("File not found: %s", index_file.c_str());
    return -1;
  }

  // load trajectory index
  // assumes each column is: (index, p0_x, p0_z, pf_x, pf_z, z)
  csv2mat(index_file, true, this->index_data);
  this->traj_dir = std::string(dirname((char *) index_file.c_str()));
  this->pos_thres = pos_thres;
  this->vel_thres = vel_thres;

  if (this->index_data.rows() == 0) {
    log_error(ETIROWS, index_file.c_str());
    return -2;
  } else if (this->index_data.cols() != 3) {
    log_error(ETICOLS, index_file.c_str());
    return -2;
  }

  this->loaded = true;
  return 0;
}

int TrajectoryIndex::find(const Vec3 &pos, double v, const Trajectory &traj) {
  // pre-check
  if (this->loaded == false) {
    return -1;
  }

  // NOTE: the following is not the most efficient way of implementing a
  // lookup
  // table, a better way could involve a search tree and traverse it or even a
  // bucket based approach. The following implements a list traversal type
  // search which is approx O(n), ok for small lookups.

  // find rows in the index that have same approx
  // start height (z) and velocity (v)
  bool p_ok, v_ok;
  std::vector<int> matches;
  for (int i = 0; i < this->index_data.rows(); i++) {
    p_ok = fabs(pos(2) - this->index_data(i, 1)) < this->pos_thres;
    v_ok = fabs(v - this->index_data(i, 2)) < this->vel_thres;

    if (p_ok && v_ok) {
      matches.push_back(i);
    }
  }

  // check number of matches
  if (matches.size() == 0) {
    return -2;  // found no trajectory
  }

  // load trajectory
  std::string traj_file;
  traj_file = this->traj_dir + "/";
  traj_file += std::to_string((int) matches[0]) + ".csv";
  if (traj.load(matches[0], traj_file, pos) != 0) {
    return -3;
  }

  return 0;
}


// LANDING CONTROLLER
LandingController::LandingController() {
  this->configured = false;

  this->dt = 0.0;
  this->blackbox_dt = 0.0;

  this->vx_error_prev = 0.0;
  this->vy_error_prev = 0.0;
  this->vz_error_prev = 0.0;

  this->vx_error_sum = 0.0;

  this->vx_k_p = 0.0;
  this->vx_k_i = 0.0;
  this->vx_k_d = 0.0;

  this->vy_k_p = 0.0;
  this->vy_k_i = 0.0;
  this->vy_k_d = 0.0;

  this->vz_k_p = 0.0;
  this->vz_k_i = 0.0;
  this->vz_k_d = 0.0;

  this->roll_limit[0] = 0.0;
  this->roll_limit[1] = 0.0;
  this->pitch_limit[0] = 0.0;
  this->pitch_limit[1] = 0.0;
  this->throttle_limit[0] = 0.0;
  this->throttle_limit[1] = 0.0;

  this->setpoints << 0.0, 0.0, 0.0;
  this->outputs << 0.0, 0.0, 0.0, 0.0;
  this->att_cmd = AttitudeCommand();

  this->traj_index;
  this->trajectory_threshold << 1.0, 1.0, 1.0;
  this->trajectory;

  this->blackbox_enable = false;
  this->blackbox_rate = FLT_MAX;
  this->blackbox;
}

LandingController::~LandingController() {
  if (this->blackbox_enable && this->blackbox) {
    this->blackbox.close();
  }
}

int LandingController::configure(const std::string &config_file) {
  ConfigParser parser;
  std::string traj_index_file;
  std::string blackbox_file;

  // load config
  parser.addParam("vx_controller.k_p", &this->vx_k_p);
  parser.addParam("vx_controller.k_i", &this->vx_k_i);
  parser.addParam("vx_controller.k_d", &this->vx_k_d);

  parser.addParam("vy_controller.k_p", &this->vy_k_p);
  parser.addParam("vy_controller.k_i", &this->vy_k_i);
  parser.addParam("vy_controller.k_d", &this->vy_k_d);

  parser.addParam("vz_controller.k_p", &this->vz_k_p);
  parser.addParam("vz_controller.k_i", &this->vz_k_i);
  parser.addParam("vz_controller.k_d", &this->vz_k_d);

  parser.addParam("roll_limit.min", &this->roll_limit[0]);
  parser.addParam("roll_limit.max", &this->roll_limit[1]);

  parser.addParam("pitch_limit.min", &this->pitch_limit[0]);
  parser.addParam("pitch_limit.max", &this->pitch_limit[1]);

  parser.addParam("throttle_limit.min", &this->throttle_limit[0]);
  parser.addParam("throttle_limit.max", &this->throttle_limit[1]);

  parser.addParam<std::string>("trajectory_index", &traj_index_file);
  parser.addParam<Vec3>("trajectory_threshold", &this->trajectory_threshold);

  parser.addParam("blackbox_enable", &this->blackbox_enable);
  parser.addParam("blackbox_rate", &this->blackbox_rate, true);
  parser.addParam<std::string>("blackbox_file", &blackbox_file, true);

  if (parser.load(config_file) != 0) {
    return -1;
  }

  // load trajectory index
  std::string config_dir = std::string(dirname((char *) config_file.c_str()));
  paths_combine(config_dir, traj_index_file, traj_index_file);
  if (this->traj_index.load(traj_index_file) != 0) {
    return -2;
  }

  // prepare blackbox file
  if (this->blackbox_enable) {
    if (blackbox_file == "") {
      log_error("blackbox file is not set!");
      return -3;
    } else if (this->prepBlackbox(blackbox_file) != 0) {
      log_error("Failed to open blackbox file at [%s]",
                blackbox_file.c_str());
      return -3;
    }

    if (this->blackbox_rate == FLT_MAX) {
      log_error("blackbox rate is not set!");
      return -3;
    }
  }

  // convert roll and pitch limits from degrees to radians
  this->roll_limit[0] = deg2rad(this->roll_limit[0]);
  this->roll_limit[1] = deg2rad(this->roll_limit[1]);
  this->pitch_limit[0] = deg2rad(this->pitch_limit[0]);
  this->pitch_limit[1] = deg2rad(this->pitch_limit[1]);

  // initialize setpoints to zero
  this->setpoints << 0.0, 0.0, 0.0;
  this->outputs << 0.0, 0.0, 0.0, 0.0;

  this->configured = true;
  return 0;
}

int LandingController::loadTrajectory(const Vec3 &pos,
                                      const Vec3 &target_pos_bf,
                                      double v) {
  // find trajectory
  int retval = this->traj_index.find(pos, v, this->trajectory);

  // check retval
  if (retval == -2) {
    log_error(ETIFAIL, pos(2), v);
    return -1;
  } else if (retval == -3) {
    log_error(ETLOAD);
    return -1;
  } else {
    log_info(TLOAD, pos(2), v);
  }

  return 0;
}

int LandingController::prepBlackbox(const std::string &blackbox_file) {
  // setup
  this->blackbox.open(blackbox_file);
  if (!this->blackbox) {
    return -1;
  }

  // write header
  // clang-format off
  this->blackbox << "dt" << ",";
  this->blackbox << "x" << ",";
  this->blackbox << "y" << ",";
  this->blackbox << "z" << ",";
  this->blackbox << "vx" << ",";
  this->blackbox << "vy" << ",";
  this->blackbox << "vz" << ",";
  this->blackbox << "wp_pos_x" << ",";
  this->blackbox << "wp_pos_z" << ",";
  this->blackbox << "wp_vel_x" << ",";
  this->blackbox << "wp_vel_z" << ",";
  this->blackbox << "target_x_bf" << ",";
  this->blackbox << "target_y_bf" << ",";
  this->blackbox << "target_z_bf" << ",";
  this->blackbox << "target_vx_bf" << ",";
  this->blackbox << "target_vy_bf" << ",";
  this->blackbox << "target_vz_bf" << ",";
  this->blackbox << "roll" << ",";
  this->blackbox << "pitch" << ",";
  this->blackbox << "yaw";
  this->blackbox << std::endl;
  // clang-format on

  return 0;
}

int LandingController::recordTrajectoryIndex() {
  this->blackbox << "trajectory index: " << this->trajectory.index
                 << std::endl;
}

int LandingController::record(const Vec3 &pos,
                              const Vec3 &vel,
                              const Vec2 &wp_pos,
                              const Vec2 &wp_vel,
                              const Vec2 &wp_inputs,
                              const Vec3 &target_pos_bf,
                              const Vec3 &target_vel_bf,
                              const Vec3 &rpy,
                              double thrust,
                              double dt) {
  // pre-check
  this->blackbox_dt += dt;
  if (this->blackbox_enable && this->blackbox_dt > this->blackbox_rate) {
    return 0;
  }

  // record
  this->blackbox << dt << ",";
  this->blackbox << pos(0) << ",";
  this->blackbox << pos(1) << ",";
  this->blackbox << pos(2) << ",";
  this->blackbox << vel(0) << ",";
  this->blackbox << vel(1) << ",";
  this->blackbox << vel(2) << ",";
  this->blackbox << wp_pos(0) << ",";
  this->blackbox << wp_pos(1) << ",";
  this->blackbox << wp_vel(0) << ",";
  this->blackbox << wp_vel(1) << ",";
  this->blackbox << wp_inputs(0) << ",";
  this->blackbox << wp_inputs(1) << ",";
  this->blackbox << target_pos_bf(0) << ",";
  this->blackbox << target_pos_bf(1) << ",";
  this->blackbox << target_pos_bf(2) << ",";
  this->blackbox << target_vel_bf(0) << ",";
  this->blackbox << target_vel_bf(1) << ",";
  this->blackbox << target_vel_bf(2) << ",";
  this->blackbox << rpy(0) << ",";
  this->blackbox << rpy(1) << ",";
  this->blackbox << rpy(2) << ",";
  this->blackbox << thrust;
  this->blackbox << std::endl;
  this->blackbox_dt = 0.0;

  return 0;
}

Vec4 LandingController::updateVelocityErrors(const Vec3 &v_errors,
                                             const Vec3 &p_errors,
                                             double yaw,
                                             double dt) {
  // check rate
  this->dt += dt;
  if (this->dt < 0.01) {
    return this->outputs;
  }

  // roll
  double r, p, y, t;
  r = this->vy_k_p * v_errors(1);
  r += this->vy_k_i * p_errors(1);
  r += this->vy_k_d * (v_errors(1) - this->vy_error_prev) / this->dt;
  r = -1 * r;

  // pitch
  this->vx_error_sum += v_errors(0);
  p = this->vx_k_p * v_errors(0);
  p += this->vx_k_i * this->vx_error_sum;
  p += this->vx_k_d * (v_errors(0) - this->vx_error_prev) / this->dt;

  // yaw
  y = 0.0;

  // throttle
  t = this->vz_k_p * v_errors(2);
  t += this->vz_k_i * p_errors(2);
  t += this->vz_k_d * (v_errors(2) - this->vz_error_prev) / this->dt;
  t /= fabs(cos(r) * cos(p));  // adjust throttle for roll and pitch

  // keep track of previous errors
  this->vx_error_prev = v_errors(0);
  this->vy_error_prev = v_errors(1);
  this->vz_error_prev = v_errors(2);

  // limit roll, pitch, throttle
  r = (r < this->roll_limit[0]) ? this->roll_limit[0] : r;
  r = (r > this->roll_limit[1]) ? this->roll_limit[1] : r;
  p = (p < this->pitch_limit[0]) ? this->pitch_limit[0] : p;
  p = (p > this->pitch_limit[1]) ? this->pitch_limit[1] : p;
  t = (t < this->throttle_limit[0]) ? this->throttle_limit[0] : t;
  t = (t > this->throttle_limit[1]) ? this->throttle_limit[1] : t;

  // keep track of setpoints and outputs
  this->setpoints = v_errors;
  this->outputs << r, p, y, t;
  this->dt = 0.0;

  return this->outputs;
}

int LandingController::update(const Vec3 &target_pos_bf,
                              const Vec3 &target_vel_bf,
                              const Vec3 &pos,
                              const Vec3 &vel,
                              const Quaternion &orientation,
                              double yaw,
                              double dt) {
  int retval;

  // obtain position and velocity waypoints
  Vec2 wp_pos, wp_vel, wp_inputs, wp_rel_pos, wp_rel_vel;
  retval = this->trajectory.update(pos, wp_pos, wp_vel, wp_inputs);
  wp_rel_pos = this->trajectory.rel_pos.at(0);
  wp_rel_vel = this->trajectory.rel_vel.at(0);

  // update velocity in body frame
  Vec3 euler, vel_bf;
  Quaternion q;
  euler << 0, 0, yaw;
  euler2quat(euler, 321, q);
  inertial2body(vel, q, vel_bf);

  // update velocity errors (inertial version)
  Vec3 v_errors;
  v_errors(0) = wp_vel(0) - vel_bf(0);
  v_errors(1) = target_vel_bf(1);
  v_errors(2) = wp_vel(1) - vel(2);

  // update position errors
  Vec3 p_errors;
  p_errors(0) = wp_rel_pos(0) + target_pos_bf(0);
  p_errors(1) = target_pos_bf(1);
  p_errors(2) = wp_rel_pos(1) - pos(2);

  // update feed-back controls
  this->outputs = this->updateVelocityErrors(v_errors, p_errors, yaw, dt);

  // add in feed-forward controls
  this->outputs(0) += 0.0;           // roll
  this->outputs(1) += wp_inputs(1);  // pitch
  this->outputs(2) += yaw;           // yaw
  this->outputs(3) += wp_inputs(0);  // thrust
  this->att_cmd = AttitudeCommand(this->outputs);

  // record
  quat2euler(orientation, 321, euler);
  this->record(pos,
               vel,
               wp_pos,
               wp_vel,
               wp_inputs,
               target_pos_bf,
               target_vel_bf,
               euler,
               this->outputs(3),
               dt);

  // check if we are too far off track with trajectory
  if (p_errors(0) > this->trajectory_threshold(0)) {
    log_error("Trajectory error in the x-axis is too large!");
    log_error("error: %f > %f", p_errors(0), this->trajectory_threshold(0));
    return -1;
  } else if (p_errors(1) > this->trajectory_threshold(1)) {
    log_error("Trajectory error in the y-axis is too large!");
    log_error("error: %f > %f", p_errors(1), this->trajectory_threshold(1));
    return -1;
  } else if (p_errors(2) > this->trajectory_threshold(2)) {
    log_error("Trajectory error in the z-axis is too large!");
    log_error("error: %f > %f", p_errors(2), this->trajectory_threshold(2));
    return -1;
  }

  return 0;
}

void LandingController::reset() {
  // this->vx_controller.reset();
  // this->vy_controller.reset();
  // this->vz_controller.reset();
}

void LandingController::printOutputs() {
  double r = rad2deg(this->outputs(0));
  double p = rad2deg(this->outputs(1));
  double t = this->outputs(3);

  std::cout << "roll: " << std::setprecision(2) << r << "\t";
  std::cout << "pitch: " << std::setprecision(2) << p << "\t";
  std::cout << "throttle: " << std::setprecision(2) << t << std::endl;
}

// void LandingController::printErrors() {
//   double p, i, d;
//
//   p = this->vx_controller.error_p;
//   i = this->vx_controller.error_i;
//   d = this->vx_controller.error_d;
//
//   std::cout << "vx_controller: " << std::endl;
//   std::cout << "\terror_p: " << std::setprecision(2) << p << "\t";
//   std::cout << "\terror_i: " << std::setprecision(2) << i << "\t";
//   std::cout << "\terror_d: " << std::setprecision(2) << i << std::endl;
//
//   p = this->vy_controller.error_p;
//   i = this->vy_controller.error_i;
//   d = this->vy_controller.error_d;
//
//   std::cout << "vy_controller: " << std::endl;
//   std::cout << "\terror_p: " << std::setprecision(2) << p << "\t";
//   std::cout << "\terror_i: " << std::setprecision(2) << i << "\t";
//   std::cout << "\terror_d: " << std::setprecision(2) << i << std::endl;
//
//   p = this->vz_controller.error_p;
//   i = this->vz_controller.error_i;
//   d = this->vz_controller.error_d;
//
//   std::cout << "vz_controller: " << std::endl;
//   std::cout << "\terror_p: " << std::setprecision(2) << p << "\t";
//   std::cout << "\terror_i: " << std::setprecision(2) << i << "\t";
//   std::cout << "\terror_d: " << std::setprecision(2) << i << std::endl;
// }

}  // end of control namespace
}  // namespace yarl
