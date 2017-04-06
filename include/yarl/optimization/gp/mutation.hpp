#ifndef YARL_OPTIMIZATION_MUTATION_HPP
#define YARL_OPTIMIZATION_MUTATION_HPP

#include "yarl/optimization/gp/tree.hpp"

namespace yarl {
namespace gp {

class Mutation {
public:
  float probability;

  // subtree mutation specific
  int subtree_build_method;
  int subtree_max_depth;

  Mutation(void);
  int configure(float probability);
  int pointMutation(Tree *t);
  int subtreeMutation(Tree *t);
};

}  // end of gp namespace
}  // end of yarl namespace
#endif
