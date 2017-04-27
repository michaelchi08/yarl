#include "yarl/optimization/gp/population.hpp"

namespace yarl {
namespace gp {

int Population::configure(int nb_individuals, TreeConfig *tree_config) {
  Tree *tree;

  // setup
  this->tree_config = tree_config;

  // generate population
  for (int i = 0; i < nb_individuals; i++) {
    tree = new Tree();
    tree->configure(this->tree_config);
    tree->generate();
    this->individuals.push_back(tree);
  }

  return 0;
}

int Population::evaluate(const Data &data, const std::string &predict) {
  for (auto t : this->individuals) {
    t->evaluate(data, predict);
  }

  return 0;
}

int Population::best(Tree &best) {
  // setup
  int best_index = 0;
  double best_score = this->individuals[0]->score;

  // find best
  for (size_t i = 1; i < this->individuals.size(); i++) {
    if (best_score < this->individuals[i]->score) {
      best_index = i;
      best_score = this->individuals[i]->score;
    }
  }

  // return best
  best.copyFrom(*this->individuals[best_index]);

  return 0;
}

int Population::copyFrom(const Population &population) {
  Tree *tree;

  // generate population
  for (size_t i = 0; i < population.individuals.size(); i++) {
    tree = new Tree();
    tree->copyFrom(*population.individuals[i]);
    this->individuals.push_back(tree);
  }

  return 0;
}

void Population::clear() {
  for (auto t : this->individuals) {
    delete t;
  }
  this->individuals.clear();
}

void Population::print() {
  for (size_t i = 0; i < this->individuals.size(); i++) {
    this->individuals[i]->printEquation();
  }
}

}  // end of gp namespace
}  // end of yarl namespace
