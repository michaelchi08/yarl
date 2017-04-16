#ifndef YARL_OPTIMIZATION_METRIC_HPP
#define YARL_OPTIMIZATION_METRIC_HPP

#include "yarl/optimization/gp/data.hpp"

namespace yarl {
namespace gp {

class HalsteadMetric {
  int nb_unique_operators;
  int nb_unique_operands;
  int nb_total_operators;
  int nb_total_operands;

  int vocab;
  int length;
  float volume;
  float difficulty;
  float effort;

  HalsteadMetric()
    : nb_unique_operators(0),
      nb_unique_operands(0),
      nb_total_operators(0),
      nb_total_operands(0),

      vocab(0),
      length(0),
      volume(0.0),
      difficulty(0.0),
      effort(0.0) {}

  int calculate();
  void print();
};

// FUNCTIONS
double mse(const Data &desired,
           const std::string &predict,
           const VecX &predicted);
double sse(const Data &desired,
           const std::string &predict,
           const VecX &predicted);

}  // end of gp namespace
}  // end of yarl namespace
#endif
