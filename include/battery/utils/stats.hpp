#ifndef UTILS_STATS_HPP
#define UTILS_STATS_HPP

#include "battery/utils/math.hpp"

namespace battery {

int linreg(std::vector<Eigen::Vector2d> pts, double *m, double *b, double *r);

}  // end of battery namespace
#endif
