#ifndef YARL_OPTIMIZATION_GPOPT_HPP
#define YARL_OPTIMIZATION_GPOPT_HPP

#include <iostream>

#include "yarl/optimization/gp/tree.hpp"
#include "yarl/optimization/gp/population.hpp"

namespace yarl {
namespace gp {

// ERROR MESSAGES
#define E_SR_INVALID_MODE "invalid symbolic regression mode!"
#define ESEL "selection config is NULL!"
#define ECRO "crossover config is NULL!"
#define EMUT "mutation config is NULL!"
#define ESFUNC "selection function is NULL!"
#define ECFUNC "crossover function is NULL!"
#define EMFUNC "mutation function is NULL!"
#define ESELFAIL "selection failed!"

//  CONSTANTS
#define SR_FILE "/tmp/sr.dat"
#define MODEL_FILE "/tmp/model.dat"
#define MODEL_OUTPUT_FILE "/tmp/model_output.dat"
#define DATA_OUTPUT_FILE "/tmp/data_output.dat"

class GPOpt {
public:
  bool configured;
  Population population;

  // termination criteria
  int max_generations;
  double target_score;

  // stats
  int generation;
  Tree best;

  GPOpt()
    : configured{false},
      population{},
      max_generations{100},
      target_score{0.0},
      generation{0},
      best{} {}

  int configure(const std::string &config_file);
  int iterate();
  int solve();
};

}  // end of gp namespace
}  // end of yarl namespace
#endif
