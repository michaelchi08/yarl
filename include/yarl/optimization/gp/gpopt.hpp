#ifndef YARL_OPTIMIZATION_GPOPT_HPP
#define YARL_OPTIMIZATION_GPOPT_HPP

#include <iostream>

#include "yarl/utils/utils.hpp"
#include "yarl/optimization/gp/tree.hpp"
#include "yarl/optimization/gp/population.hpp"
#include "yarl/optimization/gp/selection.hpp"
#include "yarl/optimization/gp/crossover.hpp"
#include "yarl/optimization/gp/mutation.hpp"

namespace yarl {
namespace gp {

class GPOpt {
public:
  bool configured;

  // general
  Population population;
  TreeConfig tree_config;
  Dataset dataset;

  // genetic operators
  SelectionConfig selection_config;
  CrossoverConfig crossover_config;
  MutationConfig mutation_config;

  // termination criteria
  int max_generations;
  double target_score;

  // stats
  int generation;
  Tree best;

  GPOpt()
    : configured{false},
      population{},
      tree_config{},
      dataset{},
      max_generations{100},
      target_score{0.0},
      generation{0},
      best{} {}

  int configure(const std::string &config_file);
  int iterate();
  int solve();
  void printBest();
};

}  // end of gp namespace
}  // end of yarl namespace
#endif
