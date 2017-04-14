#ifndef YARL_OPTIMIZATION_BENCHMARK_HPP
#define YARL_OPTIMIZATION_BENCHMARK_HPP

#include "yarl/optimization/benchmark.hpp"
#include "yarl/utils/utils.hpp"

namespace yarl {

double ackley(const VecX &x);
double beale(const VecX &x);
double booth(const VecX &x);
double matyas(const VecX &x);
double sphere(const VecX &x);
double rosenbrock(const VecX &x, const VecX &beta);
VecX rosenbrock_jacobian(const VecX &x, const VecX &beta);

}  // end of yarl namespace
#endif
