#include "yarl/estimation/kf.hpp"

namespace yarl {

KF::KF() {
  this->mu = VecX();

  this->B = MatX();
  this->R = MatX();

  this->C = MatX();
  this->Q = MatX();

  this->S = MatX();
  this->I = MatX();
  this->K = MatX();

  this->mu_p = VecX();
  this->S_p = MatX();
}

int KF::configure(const VecX &mu,
                  const MatX &R,
                  const MatX &C,
                  const MatX &Q) {
  int nb_states;

  nb_states = mu.size();
  this->mu = mu;

  this->B = MatX::Zero(nb_states, nb_states);
  this->R = R;

  this->C = C;
  this->Q = Q;

  this->S = MatX::Identity(nb_states, nb_states);
  this->I = MatX::Identity(nb_states, nb_states);
  this->K = MatX::Zero(nb_states, nb_states);

  this->mu_p = VecX::Zero(nb_states);
  this->S_p = MatX::Zero(nb_states, nb_states);

  return 0;
}

int KF::estimate(const MatX &A, const VecX &y) {
  // prediction update
  mu_p = A * mu;
  S_p = A * S * A.transpose() + R;

  // measurement update
  // clang-format off
  K = S_p * C.transpose() * (C * S_p * C.transpose() + Q).inverse();
  mu = mu_p + K * (y - C * mu_p);
  S = (I - K * C) * S_p;
  // clang-format on

  return 0;
}

}  // end of yarl namespace
