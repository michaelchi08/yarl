#ifndef UTILS_STATS_HPP
#define UTILS_STATS_HPP

#include "yarl/utils/math.hpp"

namespace yarl {

int linreg(std::vector<Eigen::Vector2d> pts, double *m, double *b, double *r);

}  // end of yarl namespace
#endif
