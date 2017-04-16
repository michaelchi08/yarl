#include "yarl/optimization/optimizers/gdopt.hpp"

namespace yarl {

int GDOpt::configure(int max_iter,
                     const VecX &eta,
                     const VecX &x,
                     std::function<double(VecX x)> f) {
  this->configured = true;

  this->max_iter = max_iter;
  this->eta = eta;
  this->x = x;
  this->f = f;

  return 0;
}

int GDOpt::calcGradient(VecX &df) {
  double step;
  VecX px, nx;

  // pre-check
  if (this->configured == false) {
    log_err(EGDC);
    return -1;
  }

  // setup
  step = 0.001;

  // calculate gradient using central finite difference
  for (int i = 0; i < this->x.rows(); i++) {
    px = this->x;
    nx = this->x;
    px(i) += step;
    nx(i) -= step;
    df(i) = (this->f(px) - this->f(nx)) / (step * 2);
  }

  return 0;
}

int GDOpt::optimize() {
  VecX df;

  // pre-check
  if (this->configured == false) {
    log_err(EGDC);
    return -1;
  }

  // setup
  df.resize(this->x.rows(), 1);

  // optimize
  for (int i = 0; i < this->max_iter; i++) {
    this->calcGradient(df);
    this->x -= this->eta.cwiseProduct(df);
  }

  return 0;
}

}  // end of yarl namespace
