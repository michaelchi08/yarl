#ifndef YARL_OPTIMIZATION_GP_POPULATION_HPP
#define YARL_OPTIMIZATION_GP_POPULATION_HPP

#include "yarl/optimization/gp/tree.hpp"

namespace yarl {
namespace gp {

class Population {
public:
  std::vector<Tree *> individuals;
  TreeConfig *tree_config;
  Data *data;

  Population() : individuals(), tree_config(NULL), data(NULL) {}

  ~Population() {
    for (auto t : this->individuals) {
      delete t;
    }
    this->individuals.clear();
    this->tree_config = NULL;
    this->data = NULL;
  }

  int configure(int nb_individuals, TreeConfig *tree_config, Data *data);
  void clear();
  int best(Tree &tree);
  int evaluate();
  int copyFrom(const Population &p);
  void print();
};

}  // end of gp namespace
}  // end of yarl namespace
#endif
