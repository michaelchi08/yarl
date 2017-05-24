# YARL LIBRARY
ADD_LIBRARY(
  yarl STATIC
  # CONTROL
  control/gimbal/attitude.cpp
  control/quadrotor/attitude.cpp
  # control/quadrotor/landing.cpp
  control/quadrotor/position.cpp
  control/quadrotor/tracking.cpp
  control/quadrotor/velocity.cpp
  control/pid.cpp
  # DRIVERS
  drivers/i2c.cpp
  drivers/mpu6050.cpp
  drivers/mpu9250.cpp
  drivers/pca9685.cpp
  drivers/sbgc.cpp
  drivers/uart.cpp
  # ESTIMATION
  estimation/ekf.cpp
  estimation/kf.cpp
  # MODELS
  models/gimbal.cpp
  models/quadrotor.cpp
  models/two_wheel.cpp
  # OPTIMIZATION
  optimization/ceres/ba.cpp
  optimization/ceres/ceres_examples.cpp
  # optimization/factor_graph/factor_graph.cpp
  optimization/gp/crossover.cpp
  optimization/gp/data.cpp
  optimization/gp/gpopt.cpp
  optimization/gp/metric.cpp
  optimization/gp/mutation.cpp
  optimization/gp/node.cpp
  optimization/gp/population.cpp
  optimization/gp/selection.cpp
  optimization/gp/tree.cpp
  optimization/optimizers/gdopt.cpp
  optimization/optimizers/llsopt.cpp
  optimization/optimizers/lmaopt.cpp
  optimization/optimizers/ransac.cpp
  optimization/benchmark.cpp
  # UTILS
  utils/config.cpp
  utils/data.cpp
  utils/file.cpp
  utils/math.cpp
  utils/opencv.cpp
  utils/stats.cpp
  utils/string.cpp
  utils/time.cpp
  # VISION
  vision/calibration.cpp
  vision/camera.cpp
  vision/chessboard.cpp
  vision/dataset.cpp
  vision/eight_point.cpp
  vision/fast.cpp
  vision/good.cpp
  vision/models.cpp
  vision/utils.cpp
  vision/vo.cpp
)
