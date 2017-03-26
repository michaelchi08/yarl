#include "yarl/optimization/optimizers/gdopt.hpp"

namespace yarl {

void gdopt_setup(struct gdopt *opt) {
  opt->configured = false;

  opt->max_iter = 1000;
  opt->eta = VecX();
  opt->x = VecX();
  opt->f = nullptr;
}

int gdopt_configure(struct gdopt *opt,
                    int max_iter,
                    VecX eta,
                    VecX x,
                    std::function<double(VecX x)> f) {
  opt->configured = true;

  opt->max_iter = max_iter;
  opt->eta = eta;
  opt->x = x;
  opt->f = f;

  return 0;
}

int gdopt_calculate_gradient(struct gdopt *opt, VecX &df) {
  double step;
  VecX px, nx;

  // pre-check
  if (opt->configured == false) {
    log_err(EGDC);
    return -1;
  }

  // setup
  step = 0.001;

  // calculate gradient using central finite difference
  for (int i = 0; i < opt->x.rows(); i++) {
    px = opt->x;
    nx = opt->x;
    px(i) += step;
    nx(i) -= step;
    df(i) = (opt->f(px) - opt->f(nx)) / (step * 2);
  }

  return 0;
}

int gdopt_optimize(struct gdopt *opt) {
  VecX df;

  // pre-check
  if (opt->configured == false) {
    log_err(EGDC);
    return -1;
  }

  // setup
  df.resize(opt->x.rows(), 1);

  // optimize
  for (int i = 0; i < opt->max_iter; i++) {
    gdopt_calculate_gradient(opt, df);
    opt->x -= opt->eta.cwiseProduct(df);
  }

  return 0;
}

}  // end of yarl namespace
