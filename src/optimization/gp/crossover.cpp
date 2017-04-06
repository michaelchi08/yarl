#include "yarl/optimization/gp/crossover.hpp"


namespace yarl {
namespace gp {

Crossover::Crossover(void) {
  this->probability = 0.0;
}

int Crossover::pointCrossover(Tree *tree1, Tree *tree2) {
  int index1, index2;
  Node *node1, *node2;

  // pre-check
  if (randf(0.0, 1.0) > this->probability) {
    return 0;
  }

  // setup
  index1 = randi(0, tree1->size - 1);
  index2 = randi(0, tree2->size - 1);
  node1 = tree1->chromosome[index1];
  node2 = tree2->chromosome[index2];

  // crossover
  if (node1 == tree1->root) {
    tree1->root = node2;
  } else {
    node1->parent->children[node1->nth_child] = node2;
  }

  if (node2 == tree2->root) {
    tree2->root = node1;
  } else {
    node2->parent->children[node2->nth_child] = node1;
  }

  // update
  tree1->root->parent = NULL;
  tree2->root->parent = NULL;
  tree1->update();
  tree2->update();

  return 0;
}

}  // end of gp namespace
}  // end of yarl namespace
