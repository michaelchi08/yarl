# YARL LIBRARY
ADD_LIBRARY(
  yarl
  STATIC
  # CONTROL
  control/pid.cpp
  # ESTIMATION
  estimation/ekf.cpp
  estimation/kf.cpp
  # MODELS
  models/quadrotor.cpp
  models/two_wheel.cpp
  # OPTIMIZATION CERES
  optimization/ceres/ba.cpp
  optimization/ceres/ceres_examples.cpp
  # OPTIMIZATION GP
  optimization/gp/crossover.cpp
  optimization/gp/data.cpp
  optimization/gp/gpopt.cpp
  optimization/gp/metric.cpp
  optimization/gp/mutation.cpp
  optimization/gp/node.cpp
  optimization/gp/population.cpp
  optimization/gp/selection.cpp
  optimization/gp/tree.cpp
  # OPTIMIZATION OPTIMIZERS
  optimization/optimizers/gdopt.cpp
  optimization/optimizers/llsopt.cpp
  optimization/optimizers/lmaopt.cpp
  optimization/optimizers/ransac.cpp
  # OPTIMIZATION
  optimization/benchmark.cpp
  optimization/testcase.cpp
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
  vision/eight_point.cpp
  vision/fast.cpp
  vision/good.cpp
  vision/utils.cpp
  vision/vo.cpp
)
