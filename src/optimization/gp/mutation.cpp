#include "yarl/optimization/gp/mutation.hpp"


namespace yarl {
namespace gp {

Mutation::Mutation(void) {
}

int Mutation::configure(float probability) {
  this->probability = probability;
  return 0;
}

// static void mutate_node(Tree *t, Node *n) {
//   Node *new_node;
//
//   generate new node
//   if (n->type == CONST) {
//     new_node = t->ts->randomConstant();
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
// }

int Mutation::pointMutation(Tree *t) {
  int i;

  // mutate
  for (i = 0; i < t->size; i++) {
    if (this->probability > randf(0, 1.0)) {
      // mutate_node(t, t->chromosome[i]);
    }
  }

  return 0;
}

// int Mutation::subtreeMutation(Tree *t) {
//     int i;
//     struct node *n;
//     struct tree *tmp;
//     struct tree_config tc;
//
//     // pre-check
//     if (randf(0.0, 1.0) > config->probability) {
//       return 0;
//     }
//
//     // setup
//     tc.build_method = config->subtree_build_method;
//     tc.max_depth = config->subtree_max_depth;
//     tc.fs = t->fs;
//     tc.ts = t->ts;
//     tmp = tree_new();
//     tree_generate(tmp, &tc);
//
//     // mutate
//     i = randi(0, t->size - 1);
//     n = t->chromosome[i];
//     if (n == t->root) {
//       t->root = tmp->root;
//     } else {
//       n->parent->children[n->nth_child] = tmp->root;
//     }
//     tree_update(t);
//
//     // clean up
//     node_clear_destroy(n);
//     free(tmp->chromosome);
//     free(tmp);
//
//     return 0;
// }

}  // end of gp namespace
}  // end of yarl namespace
