SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/tests)
FILE(COPY data DESTINATION ${PROJECT_BINARY_DIR}/tests)
ADD_EXECUTABLE(
  # TARGET
  yarl_tests
  # TESTS
  # OPTIMIZATION CERES
  optimization/ceres/ba_test.cpp
  optimization/ceres/ceres_examples_test.cpp
  # OPTIMIZATION GP
  optimization/gp/crossover_test.cpp
  optimization/gp/data_test.cpp
  optimization/gp/gpopt_test.cpp
  optimization/gp/mutation_test.cpp
  optimization/gp/node_test.cpp
  optimization/gp/population_test.cpp
  optimization/gp/tree_test.cpp
  # OPTIMIZATION OPTIMIZERS
  optimization/optimizers/gdopt_test.cpp
  optimization/optimizers/llsopt_test.cpp
  optimization/optimizers/lmaopt_test.cpp
  optimization/optimizers/ransac_test.cpp
  # OPTIMIZATION FACTOR GRAPH
  optimization/factor_graph/factor_graph_test.cpp
  optimization/factor_graph/factor_test.cpp
  optimization/factor_graph/variable_test.cpp
  # UTILS
  utils/config_test.cpp
  utils/data_test.cpp
  utils/file_test.cpp
  utils/math_test.cpp
  utils/stats_test.cpp
  utils/time_test.cpp
  # VISION
  vision/calibration_test.cpp
  vision/camera_test.cpp
  vision/chessboard_test.cpp
  vision/dataset_test.cpp
  vision/eight_point_test.cpp
  vision/utils_test.cpp
  vision/vo_test.cpp
  # TEST RUNNER
  test_runner.cpp
)
TARGET_LINK_LIBRARIES(yarl_tests ${YARL_DEPS})
