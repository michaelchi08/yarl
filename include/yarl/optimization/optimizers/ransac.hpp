#ifndef YARL_OPTIMIZATION_OPTIMIZERS_RANSAC_HPP
#define YARL_OPTIMIZATION_OPTIMIZERS_RANSAC_HPP

#include <iostream>
#include <math.h>

#include <Eigen/Dense>

#include "yarl/utils/math.hpp"
#include "yarl/utils/utils.hpp"

namespace yarl {

class RANSAC {
public:
  bool configured;

  int max_iter;
  double thresh_ratio;
  double thresh_dist;

  int iter;
  std::vector<int> inliers;
  double threshold;
  int max_inliers;
  double model_params[2];

  RANSAC(void);
  int configure(int max_iter, double threshold_ratio, double threshold_dist);
  int randomSample(const MatX &data, Vec2 &sample);
  int computeDistances(const MatX &data,
                       const Vec2 &p1,
                       const Vec2 &p2,
                       VecX &dists);
  int computeInliers(VecX &dists);
  int update(Vec2 &p1, Vec2 &p2);
  void printStats(void);
  int optimize(MatX &data);
};

}  // end of yarl namespace
#endif
