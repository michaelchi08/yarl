# YARL LIBRARY
SET(
  yarl_control
  control/gimbal/attitude_controller.cpp
  control/quadrotor/attitude_controller.cpp
  control/quadrotor/position_controller.cpp
  control/pid.cpp
)

SET(
  yarl_estimation
  estimation/ekf.cpp
  estimation/kf.cpp
)

SET(
  yarl_models
  models/gimbal.cpp
  models/quadrotor.cpp
  models/two_wheel.cpp
)

SET(
  yarl_optimization_ceres
  optimization/ceres/ba.cpp
  optimization/ceres/ceres_examples.cpp
)

SET(
  yarl_optimization_gp
  optimization/gp/crossover.cpp
  optimization/gp/data.cpp
  optimization/gp/gpopt.cpp
  optimization/gp/metric.cpp
  optimization/gp/mutation.cpp
  optimization/gp/node.cpp
  optimization/gp/population.cpp
  optimization/gp/selection.cpp
  optimization/gp/tree.cpp
)

SET(
  yarl_optimization_optimizers
  optimization/optimizers/gdopt.cpp
  optimization/optimizers/llsopt.cpp
  optimization/optimizers/lmaopt.cpp
  optimization/optimizers/ransac.cpp
)

SET(
  yarl_optimization
  optimization/factor_graph.cpp
  optimization/benchmark.cpp
  optimization/testcase.cpp
)

SET(
  yarl_utils
  utils/config.cpp
  utils/data.cpp
  utils/file.cpp
  utils/math.cpp
  utils/opencv.cpp
  utils/stats.cpp
  utils/string.cpp
  utils/time.cpp
)

SET(
  yarl_vision
  vision/calibration.cpp
  vision/camera.cpp
  vision/chessboard.cpp
  vision/eight_point.cpp
  vision/fast.cpp
  vision/good.cpp
  vision/utils.cpp
  vision/vo.cpp
)

LIST(
  APPEND yarl_modules
  ${yarl_control}
  ${yarl_estimation}
  ${yarl_models}
  ${yarl_optimization_ceres}
  ${yarl_optimization_gp}
  ${yarl_optimization_optimizers}
  ${yarl_optimization}
  ${yarl_utils}
  ${yarl_vision}
)

ADD_LIBRARY(yarl STATIC ${yarl_modules})
