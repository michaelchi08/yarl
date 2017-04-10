# CONTROL
SET(
  yarl_control
  control/gimbal/attitude_controller.cpp
  control/quadrotor/attitude_controller.cpp
  control/quadrotor/position_controller.cpp
  control/pid.cpp
)

# ESTIMATION
SET(
  yarl_estimation
  estimation/ekf.cpp
  estimation/kf.cpp
)

# MODELS
SET(
  yarl_models
  models/gimbal.cpp
  models/quadrotor.cpp
  models/two_wheel.cpp
)

# OPTIMIZATION
LIST(
  APPEND yarl_optimization
  optimization/ceres/ba.cpp
  optimization/ceres/ceres_examples.cpp
)

LIST(
  APPEND yarl_optimization
  optimization/factor_graph/factor_graph.cpp
)

LIST(
  APPEND yarl_optimization
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

LIST(
  APPEND yarl_optimization
  optimization/optimizers/gdopt.cpp
  optimization/optimizers/llsopt.cpp
  optimization/optimizers/lmaopt.cpp
  optimization/optimizers/ransac.cpp
)

LIST(
  APPEND yarl_optimization
  optimization/benchmark.cpp
  optimization/testcase.cpp
)

# UTILS
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

# VISION
SET(
  yarl_vision
  vision/calibration.cpp
  vision/camera.cpp
  vision/chessboard.cpp
  vision/dataset.cpp
  vision/eight_point.cpp
  vision/fast.cpp
  vision/good.cpp
  vision/utils.cpp
  vision/vo.cpp
)

# YARL LIBRARY
ADD_LIBRARY(
  yarl STATIC
  ${yarl_control}
  ${yarl_estimation}
  ${yarl_models}
  ${yarl_optimization}
  ${yarl_utils}
  ${yarl_vision}
)
