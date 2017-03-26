#include "yarl/estimation/ekf.hpp"

namespace yarl {

int ekf_setup(struct ekf *e, VecX mu, MatX R, MatX Q) {
  int nb_states;

  nb_states = mu.size();
  e->mu = mu;

  e->R = R;
  e->Q = Q;

  e->S = MatX::Identity(nb_states, nb_states);
  e->I = MatX::Identity(nb_states, nb_states);
  e->K = MatX::Zero(nb_states, nb_states);

  e->mu_p = VecX::Zero(nb_states);
  e->S_p = MatX::Zero(nb_states, nb_states);

  return 0;
}

int ekf_prediction_update(struct ekf *e, VecX g, MatX G) {
  e->mu_p = g;
  e->S_p = G * e->S * G.transpose() + e->R;
  return 0;
}

int ekf_measurement_update(struct ekf *e, VecX h, MatX H, VecX y) {
  // clang-format off
  e->K = e->S_p * H.transpose() * (H * e->S_p * H.transpose() + e->Q).inverse();
  e->mu = e->mu_p + e->K * (y - h);
  e->S = (e->I - e->K * H) * e->S_p;
  // clang-format on

  return 0;
}

}  // end of yarl namespace
