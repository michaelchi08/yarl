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

  HalsteadMetric(void);
  int calculate(void);
  void print(void);
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
