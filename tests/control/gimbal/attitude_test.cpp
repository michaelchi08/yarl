#include "yarl/test.hpp"
#include "yarl/models/gimbal.hpp"
#include "yarl/control/gimbal/attitude.hpp"

namespace yarl {
namespace control {

#define ATTITUDE_CONTROLLER_OUTPUT "/tmp/gimbal_attitude_controller.dat"

TEST(GimbalAttitudeController, constructor) {
  AttitudeController controller;
}

TEST(GimbalAttitudeController, calculate) {
  Vec3 setpoints;
  Vec3 actual;
  Vec3 motor_inputs;
  FILE *output_file;

  // setup
  setpoints << deg2rad(10.0), deg2rad(-10.0), 0.0;
  output_file = fopen(ATTITUDE_CONTROLLER_OUTPUT, "w");
  fprintf(output_file, "t, roll, pitch\n");

  // control attitude
  double t = 0;
  double dt = 0.001;
  models::GimbalModel gimbal;
  AttitudeController controller;

  for (int i = 0; i < 1000; i++) {
    actual << gimbal.states(0), gimbal.states(2), 0.0;
    motor_inputs = controller.calculate(setpoints, actual, dt);
    gimbal.update(motor_inputs, dt);

    fprintf(output_file, "%f, ", t);
    fprintf(output_file, "%f, ", rad2deg(gimbal.states(0)));
    fprintf(output_file, "%f\n", rad2deg(gimbal.states(2)));
    t += dt;
  }

  // clean up
  fclose(output_file);
}

}  // end of gimbal namespace
}  // namespace yarl
