#ifndef YARL_CONTROL_PID_HPP
#define YARL_CONTROL_PID_HPP

#include <float.h>
#include <math.h>

namespace yarl {

class PID {
public:
  double error_prev;
  double error_sum;

  double error_p;
  double error_i;
  double error_d;

  double k_p;
  double k_i;
  double k_d;

  PID(void);
  PID(double k_p, double k_i, double k_d);
  double calculate(double setpoint, double input, double dt);
};

}  // end of yarl namespace
#endif
