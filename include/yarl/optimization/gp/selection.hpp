#ifndef YARL_OPTIMIZATION_GP_SELECTION_HPP
#define YARL_OPTIMIZATION_GP_SELECTION_HPP

#include "yarl/optimization/gp/population.hpp"

namespace yarl {
namespace gp {

struct SelectionConfig {
  int tournament_size;

  SelectionConfig() : tournament_size{2} {}
};

int tournament_selection(int tournament_size,
                         const Population &population,
                         Population &selected);

}  // end of gp namespace
}  // end of yarl namespace
#endif
