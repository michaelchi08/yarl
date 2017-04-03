#ifndef YARL_OPTIMIZATION_CROSSOVER_HPP
#define YARL_OPTIMIZATION_CROSSOVER_HPP

#include "yarl/optimization/crossover.hpp"

namespace yarl {
namespace gp {

class Crossover {
public:
  float probability;
  int pointCrossover(const Tree &t1, const Tree &t2);
};

}  // end of gp namespace
}  // end of yarl namespace
#endif
