#include "battery/optimization/optimizers/gd.hpp"

namespace battery {

GDOpt::GDOpt(void) {
  this->configured = false;

  this->max_iter = 1000;
  this->eta = VecX();
  this->x = VecX();
  this->f = nullptr;
}

int GDOpt::configure(int max_iter,
                     VecX eta,
                     VecX x,
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

  try {
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

  } catch (const std::bad_function_call &e) {
    log_err(EGDF, e.what());
    return -2;
  }

  return 0;
}

int GDOpt::optimize(void) {
  VecX df;

  try {
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

  } catch (const std::bad_function_call &e) {
    log_err(EGDF, e.what());
    return -2;
  }

  return 0;
}

}  // end of battery namespace
