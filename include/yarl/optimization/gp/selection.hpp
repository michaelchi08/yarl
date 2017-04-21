#ifndef YARL_OPTIMIZATION_GP_SELECTION_HPP
#define YARL_OPTIMIZATION_GP_SELECTION_HPP

#include "yarl/optimization/gp/population.hpp"

namespace yarl {
namespace gp {

class Selection {
public:
  int method;

  // tournament specifics
  int tournament_size;

  Selection() : method(UINITI), tournament_size(UINITI) {}

  int configure(int method);
  int tournamentSelection(Population &population, Population &selected);
};

}  // end of gp namespace
}  // end of yarl namespace
#endif
