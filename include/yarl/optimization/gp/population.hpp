#ifndef YARL_OPTIMIZATION_GP_POPULATION_HPP
#define YARL_OPTIMIZATION_GP_POPULATION_HPP

#include "yarl/optimization/gp/tree.hpp"

namespace yarl {
namespace gp {

class Population {
public:
  std::vector<std::shared_ptr<Tree>> individuals;
  std::shared_ptr<TreeConfig> tree_config;
  std::shared_ptr<Data> data;

  Population(void);
  ~Population(void);
  int configure(int nb_individuals);
  // void clear(void);
  // int best(Tree &tree);
  // int evaluate(void);
  // int copyFrom(Population &p);
  // void print(void);
};

}  // end of gp namespace
}  // end of yarl namespace
#endif
