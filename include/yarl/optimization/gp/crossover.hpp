#ifndef YARL_OPTIMIZATION_CROSSOVER_HPP
#define YARL_OPTIMIZATION_CROSSOVER_HPP

#include "yarl/optimization/gp/tree.hpp"

namespace yarl {
namespace gp {

struct CrossoverConfig {
  double probability;

  CrossoverConfig() : probability{0.02} {}
};

int point_crossover(double probability, Tree &t1, Tree &t2);

}  // end of gp namespace
}  // end of yarl namespace
#endif
