#ifndef KINEMATICS_QUADROTOR_HPP
#define KINEMATICS_QUADROTOR_HPP

#include "yarl/utils/utils.hpp"

namespace yarl {

class QuadrotorModel {
public:
  bool initialized;

  float Ix;
  float Iy;
  float Iz;

  float ktau;
  float kt;

  float tauf;
  float taup;
  float tauq;
  float taur;

  float m;
  float g;

  QuadrotorModel(void);
  VecX gFunc(VecX x, VecX u, float dt);
  MatX GFunc(VecX x, VecX u, float dt);
  VecX hFunc(VecX x);
  MatX HFunc(VecX y);
};

}  // end of yarl namespace
#endif
