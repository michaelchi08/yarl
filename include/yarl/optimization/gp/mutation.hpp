#ifndef YARL_OPTIMIZATION_MUTATION_HPP
#define YARL_OPTIMIZATION_MUTATION_HPP

#include "yarl/optimization/gp/tree.hpp"

namespace yarl {
namespace gp {

int point_mutation(double probability, Tree &tree);
int subtree_mutation(double probability,
                     int build_method,
                     int max_depth,
                     Tree &tree);

}  // end of gp namespace
}  // end of yarl namespace
#endif
