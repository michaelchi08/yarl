#ifndef YARL_UTILS_STATS_HPP
#define YARL_UTILS_STATS_HPP

#include "yarl/utils/math.hpp"

namespace yarl {

/**
 * Linear Regression
 */
int linreg(const std::vector<Eigen::Vector2d> &pts,
           double &m,
           double &b,
           double &r);

}  // namespace yarl
#endif
