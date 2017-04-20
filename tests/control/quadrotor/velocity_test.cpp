#include "yarl/test.hpp"
#include "yarl/control/quadrotor/velocity.hpp"

#define TEST_CONFIG "tests/configs/control/velocity_controller.yaml"

namespace yarl {
namespace control {

TEST(VelocityController, constructor) {
  VelocityController controller;

  ASSERT_FALSE(controller.configured);

  ASSERT_FLOAT_EQ(0.0, controller.dt);

  ASSERT_FLOAT_EQ(0.0, controller.vx_controller.k_p);
  ASSERT_FLOAT_EQ(0.0, controller.vx_controller.k_i);
  ASSERT_FLOAT_EQ(0.0, controller.vx_controller.k_d);

  ASSERT_FLOAT_EQ(0.0, controller.vy_controller.k_p);
  ASSERT_FLOAT_EQ(0.0, controller.vy_controller.k_i);
  ASSERT_FLOAT_EQ(0.0, controller.vy_controller.k_d);

  ASSERT_FLOAT_EQ(0.0, controller.vz_controller.k_p);
  ASSERT_FLOAT_EQ(0.0, controller.vz_controller.k_i);
  ASSERT_FLOAT_EQ(0.0, controller.vz_controller.k_d);

  ASSERT_FLOAT_EQ(0.0, controller.roll_limit[0]);
  ASSERT_FLOAT_EQ(0.0, controller.roll_limit[1]);

  ASSERT_FLOAT_EQ(0.0, controller.pitch_limit[0]);
  ASSERT_FLOAT_EQ(0.0, controller.pitch_limit[1]);

  ASSERT_FLOAT_EQ(0.0, controller.throttle_limit[0]);
  ASSERT_FLOAT_EQ(0.0, controller.throttle_limit[1]);

  ASSERT_FLOAT_EQ(0.0, controller.setpoints(0));
  ASSERT_FLOAT_EQ(0.0, controller.setpoints(1));
  ASSERT_FLOAT_EQ(0.0, controller.setpoints(2));

  ASSERT_FLOAT_EQ(0.0, controller.outputs(0));
  ASSERT_FLOAT_EQ(0.0, controller.outputs(1));
  ASSERT_FLOAT_EQ(0.0, controller.outputs(2));
  ASSERT_FLOAT_EQ(0.0, controller.outputs(3));
}

TEST(VelocityController, configure) {
  VelocityController controller;

  controller.configure(TEST_CONFIG);

  ASSERT_TRUE(controller.configured);

  ASSERT_FLOAT_EQ(0.0, controller.dt);

  ASSERT_FLOAT_EQ(0.1, controller.vx_controller.k_p);
  ASSERT_FLOAT_EQ(0.2, controller.vx_controller.k_i);
  ASSERT_FLOAT_EQ(0.3, controller.vx_controller.k_d);

  ASSERT_FLOAT_EQ(0.1, controller.vy_controller.k_p);
  ASSERT_FLOAT_EQ(0.2, controller.vy_controller.k_i);
  ASSERT_FLOAT_EQ(0.3, controller.vy_controller.k_d);

  ASSERT_FLOAT_EQ(0.1, controller.vz_controller.k_p);
  ASSERT_FLOAT_EQ(0.2, controller.vz_controller.k_i);
  ASSERT_FLOAT_EQ(0.3, controller.vz_controller.k_d);

  ASSERT_FLOAT_EQ(deg2rad(-40.0), deg2rad(controller.roll_limit[0]));
  ASSERT_FLOAT_EQ(deg2rad(40.0), deg2rad(controller.roll_limit[1]));

  ASSERT_FLOAT_EQ(deg2rad(-40.0), deg2rad(controller.pitch_limit[0]));
  ASSERT_FLOAT_EQ(deg2rad(40.0), deg2rad(controller.pitch_limit[1]));

  ASSERT_FLOAT_EQ(-1.0, controller.throttle_limit[0]);
  ASSERT_FLOAT_EQ(1.0, controller.throttle_limit[1]);

  ASSERT_FLOAT_EQ(0.0, controller.setpoints(0));
  ASSERT_FLOAT_EQ(0.0, controller.setpoints(1));
  ASSERT_FLOAT_EQ(0.0, controller.setpoints(2));

  ASSERT_FLOAT_EQ(0.0, controller.outputs(0));
  ASSERT_FLOAT_EQ(0.0, controller.outputs(1));
  ASSERT_FLOAT_EQ(0.0, controller.outputs(2));
  ASSERT_FLOAT_EQ(0.0, controller.outputs(3));
}

TEST(VelocityController, update) {
  Vec3 setpoints;
  Vec3 actual;
  double dt;
  VelocityController controller;

  // setup
  controller.configure(TEST_CONFIG);

  // CHECK HOVERING PID OUTPUT
  setpoints << 0, 0, 0;
  actual << 0, 0, 0;
  dt = 0.1;
  controller.update(setpoints, actual, dt);
  controller.printOutputs();

  ASSERT_FLOAT_EQ(0.0, controller.outputs(0));
  ASSERT_FLOAT_EQ(0.0, controller.outputs(1));
  ASSERT_FLOAT_EQ(0.0, controller.outputs(3));

  // CHECK MOVING TOWARDS THE X LOCATION
  setpoints << 1, 0, 0;
  actual << 0, 0, 0;
  dt = 0.1;

  controller.reset();
  controller.update(setpoints, actual, dt);
  controller.printOutputs();

  ASSERT_FLOAT_EQ(0.0, controller.outputs(0));
  ASSERT_TRUE(controller.outputs(1) > 0.0);

  // CHECK MOVING TOWARDS THE Y LOCATION
  setpoints << 0, 1, 0;
  actual << 0, 0, 0;
  dt = 0.1;

  controller.reset();
  controller.update(setpoints, actual, dt);
  controller.printOutputs();

  ASSERT_TRUE(controller.outputs(0) < 0.0);
  ASSERT_FLOAT_EQ(0.0, controller.outputs(1));

  // CHECK MOVING TOWARDS THE X AND Y LOCATION
  setpoints << 1, 1, 0;
  actual << 0, 0, 0;
  dt = 0.1;

  controller.reset();
  controller.update(setpoints, actual, dt);
  controller.printOutputs();

  ASSERT_TRUE(controller.outputs(0) < 0.0);
  ASSERT_TRUE(controller.outputs(1) > 0.0);
}

}  // end of control namepsace
}  // end of yarl namepsace
