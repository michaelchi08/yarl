#ifndef KINEMATICS_TWOWHEEL_HPP
#define KINEMATICS_TWOWHEEL_HPP

#include "battery/utils/utils.hpp"

namespace battery {

class TwoWheelRobotModel {
public:
  bool initialized;

  TwoWheelRobotModel(void);
  VecX gFunc(VecX x, VecX u, float dt);
  MatX GFunc(VecX x, VecX u, float dt);
  VecX hFunc(VecX x);
  MatX HFunc(VecX y);
};

}  // end of battery namespace
#endif
