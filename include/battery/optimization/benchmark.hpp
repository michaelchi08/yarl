#ifndef OPTIMIZATION_BENCHMARK_HPP
#define OPTIMIZATION_BENCHMARK_HPP

#include "battery/optimization/benchmark.hpp"
#include "battery/utils/utils.hpp"

namespace battery {

double ackley(VecX x);
double beale(VecX x);
double booth(VecX x);
double matyas(VecX x);
double sphere(VecX x);
double rosenbrock(VecX x, VecX beta);
VecX rosenbrock_jacobian(VecX x, VecX beta);

}  // end of battery namespace
#endif
