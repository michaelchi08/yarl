#ifndef YARL_OPTIMIZATION_MUTATION_HPP
#define YARL_OPTIMIZATION_MUTATION_HPP

#include "yarl/optimization/mutation.hpp"

namespace yarl {
namespace gp {

class Mutation {
public:
  float probability;
  int pointMutation(const Tree &t);
  int subtreeMutation(const Tree &t);
};

}  // end of gp namespace
}  // end of yarl namespace
#endif
