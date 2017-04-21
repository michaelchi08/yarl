#ifndef YARL_OPTIMIZATION_GP_POPULATION_HPP
#define YARL_OPTIMIZATION_GP_POPULATION_HPP

#include "yarl/optimization/gp/tree.hpp"

namespace yarl {
namespace gp {

class Population {
public:
  std::vector<Tree *> individuals;
  TreeConfig *tree_config;

  Population() : individuals(), tree_config(NULL) {}

  ~Population() {
    for (auto t : this->individuals) {
      delete t;
    }
    this->individuals.clear();
    this->tree_config = NULL;
  }

  int configure(int nb_individuals, TreeConfig *tree_config);
  int evaluate(const Data &data, const std::string &predict);
  int best(Tree &tree);
  int copyFrom(const Population &p);
  void clear();
  void print();
};

}  // end of gp namespace
}  // end of yarl namespace
#endif
