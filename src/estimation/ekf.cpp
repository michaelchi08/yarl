#include "yarl/estimation/ekf.hpp"

namespace yarl {

int EKF::configure(const VecX &mu, const MatX &R, const MatX &Q) {
  int nb_states;

  nb_states = mu.size();
  this->mu = mu;

  this->R = R;
  this->Q = Q;

  this->S = MatX::Identity(nb_states, nb_states);
  this->I = MatX::Identity(nb_states, nb_states);
  this->K = MatX::Zero(nb_states, nb_states);

  this->mu_p = VecX::Zero(nb_states);
  this->S_p = MatX::Zero(nb_states, nb_states);

  return 0;
}

int EKF::predictionUpdate(const VecX &g, const MatX &G) {
  mu_p = g;
  S_p = G * S * G.transpose() + R;
  return 0;
}

int EKF::measurementUpdate(const VecX &h, const MatX &H, const VecX &y) {
  K = S_p * H.transpose() * (H * S_p * H.transpose() + Q).inverse();
  mu = mu_p + K * (y - h);
  S = (I - K * H) * S_p;

  return 0;
}

}  // end of yarl namespace
