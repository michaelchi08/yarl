#ifndef YARL_OPTIMIZATION_FACTOR_GRAPH_GRAPH_HPP
#define YARL_OPTIMIZATION_FACTOR_GRAPH_GRAPH_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <memory>

#include "yarl/utils/utils.hpp"
#include "yarl/optimization/factor_graph/factor.hpp"
#include "yarl/optimization/factor_graph/variable.hpp"

namespace yarl {

/** Factor Graph **/
class FactorGraph {
public:
  std::map<VarId, Variable *> variables;
  std::vector<Factor *> factors;

  FactorGraph() {}

  ~FactorGraph() {
    // free variables
    for (auto var : this->variables) {
      delete var.second;
    }

    // free factors
    for (auto fac : this->factors) {
      delete fac;
    }
  }

  /** Add variable **/
  int addVariable(Variable *var) {
    auto retval = this->variables.insert({var->id, var});
    if (retval.second == false) {
      return -1;
    }
    return 0;
  }

  /** Add factor **/
  int addFactor(Factor *fac) {
    // pre-check
    if (fac->valid == false) {
      return -1;
    }

    // add factor
    this->factors.push_back(fac);
    for (auto var : fac->variables) {
      this->addVariable(var);
    }

    return 0;
  }
};

}  // namespace yarl
#endif
