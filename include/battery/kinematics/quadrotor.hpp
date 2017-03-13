#ifndef __KINEMATICS_QUADROTOR_HPP__
#define __KINEMATICS_QUADROTOR_HPP__

#include "battery/utils/utils.hpp"

namespace battery {

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

} // end of battery namespace
#endif
