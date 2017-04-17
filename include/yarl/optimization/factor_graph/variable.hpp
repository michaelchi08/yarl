#ifndef YARL_OPTIMIZATION_FACTOR_GRAPH_VARIABLE_HPP
#define YARL_OPTIMIZATION_FACTOR_GRAPH_VARIABLE_HPP

namespace yarl {

enum class VariableType { NOT_SET = 0, POSE = 1, LANDMARK = 2 };

struct Variable {
  VariableType type;
  size_t id;

  Variable() : type(VariableType::NOT_SET), id{0} {}
  Variable(VariableType type, size_t id) : type{type}, id{id} {}

  bool operator<(const Variable &other) const {
    if (this->id < other.id) {
      return true;
    }
    return false;
  }
};

}  // end of yarl namespace
#endif
