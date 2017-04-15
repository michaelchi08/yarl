#ifndef YARL_UTILS_STATS_HPP
#define YARL_UTILS_STATS_HPP

#include "yarl/utils/math.hpp"

namespace yarl {

int linreg(const std::vector<Eigen::Vector2d> &pts,
           double &m,
           double &b,
           double &r);

}  // end of yarl namespace
#endif
