#include "yarl/optimization/optimizers/ransac.hpp"

namespace yarl {

void ransac_setup(struct ransac *opt) {
  opt->configured = false;

  opt->max_iter = 0;
  opt->thresh_ratio = 1.0;
  opt->thresh_dist = 0.0;

  opt->iter = 0;
  opt->max_inliers = 0;
  opt->model_params[0] = 0.0;
  opt->model_params[1] = 0.0;
}

int ransac_configure(struct ransac *opt,
                     int max_iter,
                     double thresh_ratio,
                     double thresh_dist) {
  opt->configured = true;

  opt->max_iter = max_iter;
  opt->thresh_ratio = thresh_ratio;
  opt->thresh_dist = thresh_dist;

  opt->iter = 0;
  opt->max_inliers = 0;
  opt->model_params[0] = 0.0;
  opt->model_params[1] = 0.0;

  return 0;
}

int ransac_random_sample(struct ransac *opt, const MatX &data, Vec2 &sample) {
  int rand_index;

  // pre-check
  if (opt->configured == false) {
    return -1;
  } else if (data.rows() != 2) {
    return -2;
  } else if (data.cols() < 2) {
    return -3;
  }

  // random sample
  rand_index = rand() % (data.cols() - 1);
  sample << data(0, rand_index), data(1, rand_index);

  return 0;
}

int ransac_compute_distances(struct ransac *opt,
                             const MatX &data,
                             const Vec2 &p1,
                             const Vec2 &p2,
                             VecX &dists) {
  double pdiff_norm;
  Vec2 pdiff, pdiff_unit, norm;
  MatX repmat(2, 1);

  // pre-check
  if (opt->configured == false) {
    return -1;
  }

  // diff between p2 and p1
  pdiff = p2 - p1;
  pdiff_norm = pdiff.norm();
  pdiff_unit << (pdiff(0) / pdiff_norm), (pdiff(1) / pdiff_norm);

  // Ax + By + C = 0; A = -pdiff_unit(1), B = pdiff_unit(0)
  norm << -pdiff_unit(1), pdiff_unit(0);

  // calc dist between line formed by two random and all other points
  repmat << p1(0), p1(1);
  dists = norm.transpose() * (data - repmat.replicate(1, data.cols()));

  return 0;
}

int ransac_compute_inliers(struct ransac *opt, VecX &dists) {
  // pre-check
  if (opt->configured == false) {
    return -1;
  }

  // compute inliers
  opt->inliers.clear();
  for (int i = 0; i < dists.rows(); i++) {
    if (fabs(dists[i]) <= opt->thresh_dist) {
      opt->inliers.push_back(i);
    }
  }

  return 0;
}

int ransac_update(struct ransac *opt, const Vec2 &p1, const Vec2 &p2) {
  int conditions_met;

  // pre-check
  if (opt->configured == false) {
    return -1;
  }

  // setup
  conditions_met = 0;
  conditions_met += ((int) opt->inliers.size() >= opt->threshold) ? 1 : 0;
  conditions_met += ((int) opt->inliers.size() > opt->max_inliers) ? 1 : 0;

  if (conditions_met == 2) {
    opt->max_inliers = opt->inliers.size();
    opt->model_params[0] = (p2(1) - p1(1)) / (p2(0) - p1(0));
    opt->model_params[1] = p1(1) - opt->model_params[0] * p1(0);
  }

  return 0;
}

void ransac_print_stats(struct ransac *opt) {
  printf("iter: %d\t", opt->iter);
  printf("inliers: %d\t", opt->max_inliers);
  printf("m: %f\t", opt->model_params[0]);
  printf("c: %f\n", opt->model_params[1]);
}

int ransac_optimize(struct ransac *opt, const MatX &data) {
  Vec2 p1;
  Vec2 p2;
  VecX dists;

  // pre-check
  if (opt->configured == false) {
    return -1;
  }

  // setup
  opt->threshold = round(opt->thresh_ratio * data.cols());

  // optimize
  for (opt->iter = 0; opt->iter < opt->max_iter; opt->iter++) {
    // random sample 2 points
    ransac_random_sample(opt, data, p1);
    ransac_random_sample(opt, data, p2);

    // compute distances and inliers
    ransac_compute_distances(opt, data, p1, p2, dists);
    ransac_compute_inliers(opt, dists);

    // update better model if found
    ransac_update(opt, p1, p2);
    ransac_print_stats(opt);
  }

  return 0;
}

}  // end of yarl namespace
