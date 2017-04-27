#include "yarl/optimization/gp/selection.hpp"

namespace yarl {
namespace gp {

int tournament_selection(int tournament_size,
                         const Population &population,
                         Population &selected) {
  // pre-check
  if (tournament_size <= 0) {
    return -1;
  }

  // setup
  selected.clear();

  // select selected
  int index;
  Tree *best, *contender, *t;

  for (size_t j = 0; j < population.individuals.size(); j++) {
    index = randi(0, population.individuals.size());
    best = population.individuals[index];

    // select best in tournament
    for (int i = 0; i < tournament_size; i++) {
      index = randi(0, population.individuals.size());
      contender = population.individuals[index];

      if (contender->score > best->score) {
        best = contender;
      }
    }

    // push best to selected
    t = new Tree();
    t->copyFrom(*best);
    selected.individuals.push_back(t);
  }

  return 0;
}

}  // end of gp namespace
}  // end of yarl namespace
