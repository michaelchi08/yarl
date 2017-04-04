#include "yarl/optimization/gp/crossover.hpp"

// // CROSSOVER FUNCTIONS
// void crossover_config_defaults(struct crossover_config *cc) {
//   cc->crossover_function = point_crossover;
//   cc->probability = 0.6;
// }
//
// int point_crossover(struct tree *t1,
//                     struct tree *t2,
//                     struct crossover_config *config) {
//   int i1;
//   int i2;
//   struct node *n1;
//   struct node *n2;
//
//   // pre-check
//   if (randf(0.0, 1.0) > config->probability) {
//     return 0;
//   }
//
//   // setup
//   i1 = randi(0, t1->size - 1);
//   i2 = randi(0, t2->size - 1);
//   n1 = t1->chromosome[i1];
//   n2 = t2->chromosome[i2];
//
//   // crossover
//   if (n1 == t1->root) {
//     t1->root = n2;
//   } else {
//     n1->parent->children[n1->nth_child] = n2;
//   }
//
//   if (n2 == t2->root) {
//     t2->root = n1;
//   } else {
//     n2->parent->children[n2->nth_child] = n1;
//   }
//
//   // update
//   t1->root->parent = NULL;
//   t2->root->parent = NULL;
//   tree_update(t1);
//   tree_update(t2);
//
//   return 0;
// }
//
//
