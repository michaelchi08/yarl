#ifndef YARL_OPTIMIZATION_FACTOR_GRAPH_FACTOR_HPP
#define YARL_OPTIMIZATION_FACTOR_GRAPH_FACTOR_HPP

#include <memory>

#include "yarl/utils/utils.hpp"
#include "yarl/optimization/factor_graph/variable.hpp"

namespace yarl {

struct Factor {
  int arity;
  std::vector<std::shared_ptr<Variable>> variables;

  Factor() : arity{0}, variables{} {}
  Factor(const std::shared_ptr<Variable> &at) : arity{1}, variables{at} {}
  Factor(const std::shared_ptr<Variable> &from,
         const std::shared_ptr<Variable> &to)
    : arity{2}, variables{from, to} {}

  virtual std::string toString() {
    std::ostringstream oss;

    switch (this->arity) {
      case 1:
        oss << "[factor_arity: unary, ";
        oss << "at: " << this->variables[0]->toString();
        oss << "]";
        break;
      case 2:
        oss << "[factor_arity: binary, ";
        oss << "from: " << this->variables[0]->toString();
        oss << ", ";
        oss << "to: " << this->variables[1]->toString();
        oss << "]";
        break;
      default: break;
    }

    return oss.str();
  }

  virtual void print() {
    std::cout << this->toString() << std::endl;
  }
};

template <typename T>
struct UnaryFactor : Factor {
  T measurement;

  UnaryFactor(const std::shared_ptr<Variable> &at, const T &measurement)
    : Factor{at}, measurement{measurement} {}
};

template <typename T>
struct BinaryFactor : Factor {
  T measurement;

  BinaryFactor(const std::shared_ptr<Variable> &from,
               const std::shared_ptr<Variable> &to,
               const T &measurement)
    : Factor{from, to}, measurement{measurement} {}
};

}  // end of yarl namespace
#endif
