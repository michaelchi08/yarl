#ifndef YARL_OPTIMIZATION_FACTOR_GRAPH_VARIABLE_HPP
#define YARL_OPTIMIZATION_FACTOR_GRAPH_VARIABLE_HPP

#include "yarl/utils/utils.hpp"

namespace yarl {

using VariableId = size_t;

struct FactorVariable {
  VariableId id;
  VecX data;

  FactorVariable() : id{0}, data{VecX::Zero(1)} {}
  FactorVariable(VariableId id, size_t size)
    : id{id}, data{VecX::Zero(size)} {}

  friend std::ostream &operator<<(std::ostream &os,
                                  const FactorVariable &var) {
    os << "[";
    os << "id: " << var.id << ", ";
    os << "size: " << var.data.size();
    os << "]";
    return os;
  }

  bool operator<(const FactorVariable &other) const {
    if (this->id < other.id) {
      return true;
    }
    return false;
  }
};

struct PoseVar : FactorVariable {
  PoseVar(size_t id) : FactorVariable{id, 6} {}
};

struct LandmarkVar : FactorVariable {
  LandmarkVar(size_t id) : FactorVariable{id, 3} {}
};

}  // end of yarl namespace
#endif
