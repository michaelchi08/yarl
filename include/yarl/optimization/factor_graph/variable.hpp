#ifndef YARL_OPTIMIZATION_FACTOR_GRAPH_VARIABLE_HPP
#define YARL_OPTIMIZATION_FACTOR_GRAPH_VARIABLE_HPP

#include "yarl/utils/utils.hpp"

namespace yarl {

using VarId = size_t;

#define NOTSET -1
#define POSE3D 1
#define POINT3D 2

/** Base variable POD **/
struct Variable {
  int type = 0;
  VarId id = -1;
  VecX value = VecX::Zero(1, 1);

  Variable() {}

  Variable(int type, VarId id) : type{type}, id{id} {
    switch (type) {
      case NOTSET: this->value = VecX::Zero(1); break;
      case POSE3D: this->value = VecX::Zero(6); break;
      case POINT3D: this->value = VecX::Zero(3); break;
      default: this->value = VecX::Zero(1); break;
    }
  }

  friend std::ostream &operator<<(std::ostream &os, const Variable &v) {
    // type
    os << "[";
    switch (v.type) {
      case POSE3D: os << "type: POSE3D, "; break;
      case POINT3D: os << "type: POINT3D, "; break;
      default: os << "type: NOTSET, "; break;
    }

    // id
    os << "id: " << v.id << ", ";

    // variable dimensions
    os << "variable dim: ";
    os << "(" << v.value.rows() << ", " << v.value.cols() << ")";
    os << "]";
    return os;
  }
};

/** Pose 3D variable **/
struct Pose3dVar : Variable {
  Pose3dVar() : Variable(POSE3D, -1) {}
  Pose3dVar(VarId id) : Variable{POSE3D, id} {}
  Pose3dVar(VarId id, const Vec3 &p) : Variable{POSE3D, id} {
    this->value = p;
  }
};

/** Point 3D variable **/
struct Point3dVar : Variable {
  Point3dVar() : Variable(POINT3D, -1) {}
  Point3dVar(VarId id) : Variable{POINT3D, id} {}
  Point3dVar(VarId id, const Vec3 &p) : Variable{POINT3D, id} {
    this->value = p;
  }
};

}  // namespace yarl
#endif
