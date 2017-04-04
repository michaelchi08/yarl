#include "yarl/optimization/gp/population.hpp"

// // POPULATION FUNCTIONS
// struct population *population_new(int size) {
//   int i;
//   struct population *p;
//
//   // pre-check
//   check(size > 0, E_NUM_OF_INDIVIDUALS);
//
//   // setup
//   p = (struct population *) malloc(sizeof(struct population));
//   p->individuals = (struct tree **) malloc(sizeof(struct tree *) * size);
//   for (i = 0; i < size; i++) {
//     p->individuals[i] = NULL;
//   }
//   p->size = size;
//
//   return p;
// error:
//   return NULL;
// }
//
// void population_destroy(void *target) {
//   int i;
//   struct population *p;
//   void *t;
//
//   p = (struct population *) target;
//   for (i = 0; i < p->size; i++) {
//     t = p->individuals[i];
//     if (t != NULL) {
//       tree_destroy(t);
//     }
//   }
//   free(p->individuals);
//   free(p);
//   p = NULL;
// }
//
// struct population *population_generate(struct tree_config *tc, int size) {
//   int i;
//   struct population *p;
//   struct tree *t;
//
//   // setup
//   p = population_new(size);
//
//   // generate population
//   for (i = 0; i < size; i++) {
//     t = tree_new();
//     tree_generate(t, tc);
//     p->individuals[i] = t;
//   }
//
//   return p;
// }
//
// struct tree *population_best(struct population *p) {
//   int i;
//   int best_index;
//   struct tree *best;
//   struct tree *contender;
//   struct tree *result;
//
//   // pre-check
//   check(p->individuals != NULL, E_POPULATION);
//   check(p->size > 0, E_POPULATION_EMPTY);
//
//   // find best
//   best_index = randi(0, p->size - 1);
//   best = p->individuals[best_index];
//
//   for (i = 0; i < p->size; i++) {
//     contender = p->individuals[i];
//
//     if (fltcmp(contender->score, best->score) == 1) {
//       best = contender;
//     }
//   }
//
//   // set population best
//   result = tree_new();
//   tree_copy(best, result);
//
//   return result;
// error:
//   return NULL;
// }
//
// void population_clear(struct population *p) {
//   int i;
//   struct tree *t;
//
//   for (i = 0; i < p->size; i++) {
//     t = p->individuals[i];
//     if (t) {
//       node_clear_destroy(t->root);
//       t->root = NULL;
//     }
//   }
// }
//
// void population_copy(struct population *src, struct population *dest) {
//   int i;
//
//   for (i = 0; i < src->size; i++) {
//     tree_copy(src->individuals[i], dest->individuals[i]);
//   }
// }
//
// void population_print(struct population *p) {
//   int i;
//
//   for (i = 0; i < p->size; i++) {
//     tree_print(p->individuals[i]);
//   }
// }
//
//
