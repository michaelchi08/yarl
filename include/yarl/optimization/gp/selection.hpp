#ifndef YARL_OPTIMIZATION_GP_SELECTION_HPP
#define YARL_OPTIMIZATION_GP_SELECTION_HPP

#include "yarl/optimization/gp/population.hpp"

namespace yarl {
namespace gp {

class Selection {
public:
  int method;

  // tournament specifics
  int tournament_size;

  Selection();
  int configure();
  int tournamentSelection(Population &population, Population &selected);
};

// int tournament_selection(struct population *p,
//                          struct population *selected,
//                          struct selection_config *sc) {
//   int i;
//   int j;
//   int index;
//   struct tree *best;
//   struct tree *contender;
//
//   // pre-check
//   check(p != NULL, E_POPULATION);
//   check(selected != NULL, E_SELECTED);
//   check(sc != NULL, E_SELECTION_CONFIG);
//   check(sc->tournament_size > 0, E_TOURNAMENT_SIZE);
//
//   // setup
//   population_clear(selected);
//
//   // select selected
//   for (j = 0; j < p->size; j++) {
//     index = randi(0, p->size - 1);
//     best = p->individuals[index];
//
//     // select best in tournament
//     for (i = 0; i < sc->tournament_size; i++) {
//       index = randi(0, p->size - 1);
//       contender = p->individuals[index];
//
//       if (contender->score > best->score) {
//         best = contender;
//       }
//     }
//
//     // copy best to selected
//     best->hits = 0;
//     best->score = 0.0;
//     best->error = 0.0;
//     tree_destroy(selected->individuals[j]);
//     selected->individuals[j] = tree_new();
//     tree_copy(best, selected->individuals[j]);
//   }
//   selected->size = p->size;
//
//   return 0;
// error:
//   return -1;
// }

}  // end of gp namespace
}  // end of yarl namespace
#endif
