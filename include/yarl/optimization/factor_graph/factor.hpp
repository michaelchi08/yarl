#ifndef YARL_OPTIMIZATION_FACTOR_GRAPH_FACTOR_HPP
#define YARL_OPTIMIZATION_FACTOR_GRAPH_FACTOR_HPP

#include <memory>

#include "yarl/utils/utils.hpp"
#include "yarl/optimization/factor_graph/variable.hpp"

namespace yarl {

/** Factor Types **/
#define NOTSET -1
#define ODOM 1
#define MONOVO 2

/** Factor Error Messages **/
#define INV_ODOM_FACTOR \
  "Invalid OdomFactor! Expecting [POSE3D, POSE3D] variables!"
#define INV_MONOVO_FACTOR \
  "Invalid MonoVOFactor! Expecting [POSE3D, POINT3D] variables!"

/** Base Factor POD **/
struct Factor {
  bool valid = false;
  int type = 0;
  int arity = 0;
  std::vector<Variable *> variables;
  MatX measurement = MatX::Zero(1, 1);

  Factor() {}

  Factor(int type, Variable *var1, MatX measurement)
    : type{type}, arity{1}, variables{var1}, measurement{measurement} {}

  Factor(int type, Variable *var1, Variable *var2, MatX measurement)
    : type{type}, arity{2}, variables{var1, var2}, measurement{measurement} {}

  friend std::ostream &operator<<(std::ostream &os, const Factor &f) {
    // type
    os << "[";
    switch (f.type) {
      case NOTSET: os << "type: NOTSET, "; break;
      case ODOM: os << "type: ODOM, "; break;
      case MONOVO: os << "type: MONOVO, "; break;
      default: os << "type: UNDEFINED, "; break;
    }

    // arity
    os << "arity: " << f.arity << ", ";

    // measurement dimensions
    os << "measurement dim: ";
    os << "(" << f.measurement.rows() << ", " << f.measurement.cols() << ")";
    os << "]";
    return os;
  }
};

/** Convenient Odometry Factor **/
struct OdomFactor : Factor {
  OdomFactor() : Factor{} {}
  OdomFactor(Variable *pose1, Variable *pose2, const MatX &measurement)
    : Factor{ODOM, pose1, pose2, measurement} {
    if (pose1->type == POSE3D && pose2->type == POSE3D) {
      this->valid = true;
    } else {
      log_error(INV_ODOM_FACTOR);
    }
  }
};

/** Convenient MonoVO Factor **/
struct MonoVOFactor : Factor {
  MonoVOFactor() : Factor{} {}
  MonoVOFactor(Variable *pose, Variable *point, const MatX &measurement)
    : Factor{MONOVO, pose, point, measurement} {
    if (pose->type == POSE3D && point->type == POINT3D) {
      this->valid = true;
    } else {
      log_error(INV_MONOVO_FACTOR);
    }
  }
};

}  // namespace yarl
#endif
