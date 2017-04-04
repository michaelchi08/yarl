#include "yarl/optimization/gp/mutation.hpp"

// // MUTATION FUNCTIONS
// void mutation_config_defaults(struct mutation_config *mc) {
//   mc->mutation_function = subtree_mutation;
//   mc->probability = 0.02;
//
//   mc->subtree_build_method = FULL_METHOD;
//   mc->subtree_max_depth = 2;
// }
//
// static void mutate_node(struct tree *t, struct node *n) {
//   struct node *new_node;
//
//   // generate new node
//   if (n->type == CONST) {
//     new_node = node_random_const(t->ts);
//     n->nval = new_node->nval;
//
//   } else if (n->type == INPUT) {
//     new_node = node_random_input(t->ts);
//     free(n->input);
//     n->input = new_node->input;
//
//   } else if (n->type == UFUNC) {
//     new_node = node_random_ufunc(t->fs);
//     n->fval = new_node->fval;
//     free(new_node->children);
//
//   } else if (n->type == BFUNC) {
//     new_node = node_random_bfunc(t->fs);
//     n->fval = new_node->fval;
//     free(new_node->children);
//   }
//
//   free(new_node);
// }
//
// int point_mutation(struct tree *t, struct mutation_config *config) {
//   int i;
//
//   // mutate
//   for (i = 0; i < t->size; i++) {
//     if (config->probability > randf(0, 1.0)) {
//       mutate_node(t, t->chromosome[i]);
//     }
//   }
//
//   return 0;
// }
//
// int subtree_mutation(struct tree *t, struct mutation_config *config) {
//   int i;
//   struct node *n;
//   struct tree *tmp;
//   struct tree_config tc;
//
//   // pre-check
//   if (randf(0.0, 1.0) > config->probability) {
//     return 0;
//   }
//
//   // setup
//   tc.build_method = config->subtree_build_method;
//   tc.max_depth = config->subtree_max_depth;
//   tc.fs = t->fs;
//   tc.ts = t->ts;
//   tmp = tree_new();
//   tree_generate(tmp, &tc);
//
//   // mutate
//   i = randi(0, t->size - 1);
//   n = t->chromosome[i];
//   if (n == t->root) {
//     t->root = tmp->root;
//   } else {
//     n->parent->children[n->nth_child] = tmp->root;
//   }
//   tree_update(t);
//
//   // clean up
//   node_clear_destroy(n);
//   free(tmp->chromosome);
//   free(tmp);
//
//   return 0;
// }
//
//
