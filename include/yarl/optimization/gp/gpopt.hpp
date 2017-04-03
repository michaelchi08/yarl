#ifndef YARL_OPTIMIZATION_GPOPT_HPP
#define YARL_OPTIMIZATION_GPOPT_HPP

#include <stdio.h>
#include <stdlib.h>

#include "yarl/optimization/gp/tree.hpp"

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

// STRUCTURES
struct config {
  // details
  int nb_populations;
  int nb_individuals;

  // populations
  struct population **p;
  struct population **selected;

  // genetic operators
  struct selection_config selection;
  struct crossover_config crossover;
  struct mutation_config mutation;

  // termination criteria
  int max_generations;
  double target_score;
};

// FUNCTIONS
struct config *sr_setup(int nb_populations,
                        int nb_individuals,
                        struct tree_config *tc);
void sr_destroy(void *target);
int sr_reproduce(struct config *c);
void sr_evaluate(struct config *c, struct data *d, char *predict);
void sr_exchange_best(struct config *c);
struct tree *sr_best(struct config *c);
void sr_print_best(struct config *c, struct dataset *d, int generation);
int sr_record_best(struct config *c, struct dataset *d);
int sr_record_generation(struct config *c, int generation);
int sr_evolve_terminate(struct config *c);
void sr_print(struct config *c, int generation);
int sr_evolve(struct config *c, struct dataset *d);

namespace yarl {

class GPConfig {
public:
  // details
  int nb_populations;
  int nb_individuals;

  // populations
  struct population **p;
  struct population **selected;

  // genetic operators
  struct selection_config selection;
  struct crossover_config crossover;
  struct mutation_config mutation;

  // termination criteria
  int max_generations;
  double target_score;

  GPConfig(void) {
    this->nb_populations;
    this->nb_individuals;

    // population

    // genetic operators
    this->selection_config selection;
    this->crossover_config crossover;
    this->mutation_config mutation;

    // termination criteria
    this->max_generations;
    this->target_score;
  }
};

}  // end of yarl namespace
#endif
