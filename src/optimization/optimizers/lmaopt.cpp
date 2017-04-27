#include "yarl/optimization/optimizers/lmaopt.hpp"

namespace yarl {

int LMAOpt::configure(const LMASettings &settings) {
  this->configured = true;

  this->max_iter = settings.max_iter;
  this->lambda = settings.lambda;
  this->function = settings.function;
  this->jacobian = settings.jacobian;
  this->nb_inputs = settings.nb_inputs;
  this->nb_params = settings.nb_params;

  this->x = settings.x;
  this->y = settings.y;
  this->beta = settings.beta;

  this->y_est = MatX::Zero(this->y.rows(), 1);
  this->diff = MatX::Zero(this->y.rows(), 1);

  this->J = MatX::Zero(this->y.rows(), this->nb_params);
  this->H = MatX::Zero(this->nb_params, this->nb_params);

  this->error = FLT_MAX;

  return 0;
}

int LMAOpt::evalFunction(const VecX &beta, double &error) {
  // pre-check
  if (this->configured == false) {
    return -1;
  }

  // evaluate function
  for (int i = 0; i < this->y.rows(); i++) {
    this->y_est(i) = this->function(
      this->x.block(i, 0, 1, this->nb_inputs).transpose(), beta);
  }

  // calculate error
  this->diff = this->y - y_est;
  error = diff.dot(diff);

  return 0;
}

int LMAOpt::calcGradients(const VecX &beta) {
  // pre-check
  if (this->configured == false) {
    return -1;
  }

  // calculate jacobian
  for (int i = 0; i < this->y.rows(); i++) {
    this->J.block(i, 0, 1, this->nb_params) =
      this
        ->jacobian(this->x.block(i, 0, 1, this->nb_inputs).transpose(), beta)
        .transpose();
  }

  // approximate Hessian
  this->H = this->J.transpose() * this->J;

  return 0;
}

int LMAOpt::iterate() {
  MatX I, H_est, I_adaptive;
  VecX delta, beta_est;
  double error_est;

  // pre-check
  if (this->configured == false) {
    return -1;
  }

  // Levenberg (1994) - damp hessian
  // I = MatX::Identity(this->nb_params, this->nb_params);
  // H_est = this->H + this->lambda * I;

  // Marquardt (1963) - adaptive component-wise damping
  I = MatX::Identity(this->nb_params, this->nb_params);
  I.diagonal() = this->H.diagonal();
  H_est = this->H + this->lambda * I;

  // update params
  delta = -H_est.inverse() * (this->J.transpose() * this->diff);
  beta_est = this->beta + delta;

  // evaluate new error
  this->evalFunction(beta_est, error_est);

  // adjust damping factor
  if (error_est > this->error) {
    this->lambda *= 10.0;

  } else {
    this->lambda /= 10.0;
    this->beta = beta_est;
    this->error = error_est;
    this->calcGradients(beta_est);
  }

  return 0;
}

int LMAOpt::optimize() {
  // pre-check
  if (this->configured == false) {
    log_error(ELMAC);
    return -1;
  }

  // initialize error and gradients
  this->evalFunction(this->beta, this->error);
  this->calcGradients(this->beta);

  // iterate
  for (int i = 0; i < this->max_iter; i++) {
    this->iterate();
  }

  return 0;
}

}  // end of yarl namespace
