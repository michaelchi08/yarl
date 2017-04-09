#include "yarl/optimization/gp/mutation.hpp"


namespace yarl {
namespace gp {

Mutation::Mutation(void) {
  this->probability = 0.0;

  this->subtree_build_method = UINITI;
  this->subtree_max_depth = UINITI;
}

int Mutation::configure(float probability) {
  this->probability = probability;

  this->subtree_build_method = GROW_METHOD;
  this->subtree_max_depth = 2;

  return 0;
}

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

int Mutation::pointMutation(Tree &tree) {
  for (int i = 0; i < tree.size; i++) {
    if (this->probability > randf(0, 1.0)) {
      mutate_node(tree, tree.chromosome[i]);
    }
  }

  return 0;
}

int Mutation::subtreeMutation(Tree &tree) {
  int index;
  Node *node;
  Tree subtree;
  TreeConfig config;

  // pre-check
  if (randf(0.0, 1.0) > this->probability) {
    return 0;
  }

  // setup
  config.configure(this->subtree_build_method, this->subtree_max_depth);
  subtree.tc = &config;
  subtree.generate();

  // mutate
  index = randi(0, tree.chromosome.size() - 1);
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
