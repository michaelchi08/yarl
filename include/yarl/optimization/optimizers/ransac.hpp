#ifndef OPTIMIZATION_OPTIMIZERS_RANSAC_HPP
#define OPTIMIZATION_OPTIMIZERS_RANSAC_HPP

#include <iostream>
#include <math.h>

#include <Eigen/Dense>

#include "yarl/utils/math.hpp"
#include "yarl/utils/utils.hpp"

namespace yarl {

struct ransac {
  bool configured;

  int max_iter;
  double thresh_ratio;
  double thresh_dist;

  int iter;
  std::vector<int> inliers;
  double threshold;
  int max_inliers;
  double model_params[2];
};

void ransac_setup(struct ransac *opt);
int ransac_configure(struct ransac *opt,
                     int max_iter,
                     double threshold_ratio,
                     double threshold_dist);
int ransac_random_sample(struct ransac *opt, const MatX &data, Vec2 &sample);
int ransac_compute_distances(struct ransac *opt,
                             const MatX &data,
                             const Vec2 &p1,
                             const Vec2 &p2,
                             VecX &dists);
int ransac_compute_inliers(struct ransac *opt, VecX &dists);
int ransac_update(struct ransac *opt, const Vec2 &p1, const Vec2 &p2);
void ransac_print_stats(struct ransac *opt);
int ransac_optimize(struct ransac *opt, const MatX &data);

}  // end of yarl namespace
#endif
