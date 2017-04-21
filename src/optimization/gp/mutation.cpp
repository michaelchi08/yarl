#include "yarl/optimization/gp/mutation.hpp"


namespace yarl {
namespace gp {

static void mutate_node(Tree &tree, Node *node) {
  Node new_node;

  if (node->type == CONST) {
    tree.tc->randomConstant(new_node);
    node->nval = new_node.nval;

  } else if (node->type == INPUT) {
    tree.tc->randomInput(new_node);
    node->input = new_node.input;

  } else if (node->type == UFUNC) {
    tree.tc->randomUnaryFunction(new_node);
    node->fval = new_node.fval;

  } else if (node->type == BFUNC) {
    tree.tc->randomBinaryFunction(new_node);
    node->fval = new_node.fval;
  }
}

int point_mutation(double probability, Tree &tree) {
  for (int i = 0; i < tree.size; i++) {
    if (probability > randf(0, 1.0)) {
      mutate_node(tree, tree.chromosome[i]);
    }
  }

  return 0;
}

int subtree_mutation(double probability,
                     int build_method,
                     int max_depth,
                     Tree &tree) {
  int index;
  Node *node;
  Tree subtree;
  TreeConfig config;

  // pre-check
  if (randf(0.0, 1.0) > probability) {
    return 0;
  }

  // setup
  config.configure(build_method, max_depth);
  subtree.tc = &config;
  subtree.generate();

  // mutate
  index = randi(0, tree.chromosome.size());
  node = tree.chromosome[index];
  if (node == tree.root) {
    delete tree.root;
    tree.root = subtree.root;
    subtree.root = NULL;

  } else {
    node->parent->children[node->nth_child] = subtree.root;
    subtree.root = NULL;
    delete node;
  }
  tree.update();

  return 0;
}

}  // end of gp namespace
}  // end of yarl namespace
