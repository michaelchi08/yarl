#ifndef YARL_OPTIMIZATION_FACTOR_GRAPH_FACTOR_GRAPH_HPP
#define YARL_OPTIMIZATION_FACTOR_GRAPH_FACTOR_GRAPH_HPP

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
  std::multimap<std::shared_ptr<Variable>, std::shared_ptr<Factor>> graph;
  std::set<std::shared_ptr<Variable>> variables;
  std::vector<std::shared_ptr<Factor>> factors;

  FactorGraph() : graph{}, variables{}, factors{} {}

  template <typename T>
  int addUnaryFactor(VariableType type, size_t at, const T &measurement) {
    // store variable and factor
    auto variable = std::make_shared<Variable>(type, at);
    this->variables.insert(variable);

    auto factor = std::make_shared<Factor>(variable, measurement);
    this->factors.push_back(factor);

    // store key-factor pair
    auto value = std::make_pair(variable, factor);
    this->graph.insert(value);

    return 0;
  }

  template <typename T>
  int addBinaryFactor(VariableType from_type,
                      size_t from,
                      VariableType to_type,
                      size_t to,
                      const T &measurement) {
    // store variables and factor
    auto from_var = std::make_shared<Variable>(from_type, from);
    this->variables.insert(from_var);

    auto to_var = std::make_shared<Variable>(to_type, to);
    this->variables.insert(to_var);

    auto factor = std::make_shared<Factor>(from_var, to_var, measurement);
    this->factors.push_back(factor);

    // store key-factor pairs
    auto val1 = std::make_pair(from_var, factor);
    this->graph.insert(val1);

    auto val2 = std::make_pair(to_var, factor);
    this->graph.insert(val2);

    return 0;
  }

  std::string toString() {
    std::ostringstream oss;
    int index = 0;

    for (auto f : this->factors) {
      oss << "f" << index << " -- ";
      oss << f->toString() << std::endl;
      index++;
    }

    return oss.str();
  }

  void print() {
    std::cout << this->toString() << std::endl;
  }
};

}  // end of yarl namespace
#endif
