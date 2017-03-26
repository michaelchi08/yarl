#include "yarl/estimation/kf.hpp"

namespace yarl {

int kf_setup(struct kf *e, VecX mu, MatX R, MatX C, MatX Q) {
  int nb_states;

  nb_states = mu.size();
  e->mu = mu;

  e->B = MatX::Zero(nb_states, nb_states);
  e->R = R;

  e->C = C;
  e->Q = Q;

  e->S = MatX::Identity(nb_states, nb_states);
  e->I = MatX::Identity(nb_states, nb_states);
  e->K = MatX::Zero(nb_states, nb_states);

  e->mu_p = VecX::Zero(nb_states);
  e->S_p = MatX::Zero(nb_states, nb_states);

  return 0;
}

int kf_estimate(struct kf *e, MatX A, VecX y) {
  MatX C_T;

  // prediction update
  e->mu_p = A * e->mu;
  e->S_p = A * e->S * A.transpose() + e->R;

  // measurement update
  // clang-format off
  e->K = e->S_p * e->C.transpose() * (e->C * e->S_p * e->C.transpose() + e->Q).inverse();
  e->mu = e->mu_p + e->K * (y - e->C * e->mu_p);
  e->S = (e->I - e->K * e->C) * e->S_p;
  // clang-format on

  return 0;
}

}  // end of yarl namespace
