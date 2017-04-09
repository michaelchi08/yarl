#include "yarl/optimization/gp/selection.hpp"

namespace yarl {
namespace gp {

Selection::Selection(void) {
  this->method = UINITI;

  this->tournament_size = UINITI;
}

int Selection::configure(void) {
  return 0;
}

// int Selection::tournamentSelection(Population &population,
//                                    Population &selected) {
//   // setup
//   // selected.clear();
//
//   // select selected
//   // for (int j = 0; j < p->size; j++) {
//   //   index = randi(0, p->size - 1);
//   //   best = p->individuals[index];
//   //
//   //   // select best in tournament
//   //   for (i = 0; i < sc->tournament_size; i++) {
//   //     index = randi(0, p->size - 1);
//   //     contender = p->individuals[index];
//   //
//   //     if (contender->score > best->score) {
//   //       best = contender;
//   //     }
//   //   }
//
//   //     // copy best to selected
//   //     best->hits = 0;
//   //     best->score = 0.0;
//   //     best->error = 0.0;
//   //     tree_destroy(selected->individuals[j]);
//   //     selected->individuals[j] = tree_new();
//   //     tree_copy(best, selected->individuals[j]);
//
//   return 0;
// }

}  // end of gp namespace
}  // end of yarl namespace
