#ifndef YARL_OPTIMIZATION_CROSSOVER_HPP
#define YARL_OPTIMIZATION_CROSSOVER_HPP

#include "yarl/optimization/gp/tree.hpp"

namespace yarl {
namespace gp {

class Crossover {
public:
  float probability;

  Crossover(void);
  int pointCrossover(Tree *t1, Tree *t2);
};

}  // end of gp namespace
}  // end of yarl namespace
#endif
