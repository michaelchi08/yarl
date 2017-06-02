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

  int addVariable(Variable *var) {
    auto retval = this->variables.insert({var->id, var});
    if (retval.second == false) {
      return -1;
    }
    return 0;
  }

  void addFactor(Factor *fac) {
    this->factors.push_back(fac);
    for (auto var : fac->variables) {
      this->addVariable(var);
    }
  }
};

}  // namespace yarl
#endif
