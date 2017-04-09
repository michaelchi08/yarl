#include "yarl/optimization/gp/population.hpp"

namespace yarl {
namespace gp {

Population::Population(void) {
  // this->clear();
}

Population::~Population(void) {
  // this->clear();
}

int Population::configure(int nb_individuals) {
  std::shared_ptr<Tree> tree;

  // setup
  this->tree_config->configure(GROW_METHOD, 2);

  // generate population
  for (int i = 0; i < nb_individuals; i++) {
    tree = std::make_shared<Tree>();
    // tree->configure(this->tree_config, this->data);
    tree->generate();
    this->individuals.push_back(tree);
  }

  return 0;
}

// void Population::clear(void) {
//   for (size_t i = 0; i < this->individuals.size(); i++) {
//     delete this->individuals.back();
//     this->individuals.pop_back();
//   }
// }
//
// int Population::best(Tree &best) {
//   best = *this->individuals[0];
//   for (size_t i = 1; i < this->individuals.size(); i++) {
//     if (best.score > this->individuals[i]->score) {
//       best = *this->individuals[i];
//     }
//   }
//
//   return 0;
// }
//
// int Population::copyFrom(Population &population) {
//   Tree *tree;
//
//   // generate population
//   for (size_t i = 0; i < population.individuals.size(); i++) {
//     tree = new Tree();
//     tree->copyFrom(*population.individuals[i]);
//     this->individuals.push_back(tree);
//   }
//
//   return 0;
// }
//
// void Population::print(void) {
//   for (size_t i = 0; i < this->individuals.size(); i++) {
//     this->individuals[i]->printEquation();
//   }
// }

}  // end of gp namespace
}  // end of yarl namespace
