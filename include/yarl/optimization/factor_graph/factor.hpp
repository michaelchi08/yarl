#ifndef YARL_OPTIMIZATION_FACTOR_GRAPH_FACTOR_HPP
#define YARL_OPTIMIZATION_FACTOR_GRAPH_FACTOR_HPP

#include <memory>

#include "yarl/utils/utils.hpp"
#include "yarl/optimization/factor_graph/variable.hpp"

namespace yarl {

struct Factor {
  int arity;
  std::vector<std::shared_ptr<FactorVariable>> variables;

  Factor() : arity{0}, variables{} {}

  Factor(const std::shared_ptr<FactorVariable> &at)
    : arity{1}, variables{at} {}

  Factor(const std::shared_ptr<FactorVariable> &from,
         const std::shared_ptr<FactorVariable> &to)
    : arity{2}, variables{from, to} {}
};

}  // namespace yarl
#endif
