CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(yarl)

# COMPILER SETTINGS
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
IF (CMAKE_COMPILER_IS_GNUCXX)
    ADD_DEFINITIONS(-std=gnu++11)
ENDIF()

# DEPENDENCIES
FIND_PACKAGE(Ceres REQUIRED)
FIND_PACKAGE(Eigen3 REQUIRED)
FIND_PACKAGE(LibXml2 REQUIRED)
FIND_PACKAGE(OpenCV 3.0 REQUIRED)

# INCLUDES
INCLUDE_DIRECTORIES(include)
INCLUDE_DIRECTORIES(/usr/include/eigen3)
INCLUDE_DIRECTORIES(/usr/include/libxml2)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})

# GTEST
ADD_SUBDIRECTORY(deps/googletest)
INCLUDE_DIRECTORIES(${gtest_SOURCE_DIR} ${gtest_SOURCE_DIR}/include)

# YARL LIBRARY
ADD_LIBRARY(
  yarl
  STATIC
  # CONTROL
  src/control/pid.cpp
  # ESTIMATION
  src/estimation/ekf.cpp
  src/estimation/kf.cpp
  # MODELS
  src/models/quadrotor.cpp
  src/models/two_wheel.cpp
  # OPTIMIZATION CERES
  src/optimization/ceres/ba.cpp
  src/optimization/ceres/ceres_examples.cpp
  # OPTIMIZATION GP
  src/optimization/gp/crossover.cpp
  src/optimization/gp/data.cpp
  src/optimization/gp/gpopt.cpp
  src/optimization/gp/metric.cpp
  src/optimization/gp/mutation.cpp
  src/optimization/gp/node.cpp
  src/optimization/gp/population.cpp
  src/optimization/gp/selection.cpp
  src/optimization/gp/tree.cpp
  # OPTIMIZATION OPTIMIZERS
  src/optimization/optimizers/gdopt.cpp
  src/optimization/optimizers/llsopt.cpp
  src/optimization/optimizers/lmaopt.cpp
  src/optimization/optimizers/ransac.cpp
  # OPTIMIZATION
  src/optimization/benchmark.cpp
  src/optimization/testcase.cpp
  # UTILS
  src/utils/config.cpp
  src/utils/data.cpp
  src/utils/file.cpp
  src/utils/math.cpp
  src/utils/opencv.cpp
  src/utils/stats.cpp
  src/utils/string.cpp
  src/utils/time.cpp
  # VISION
  src/vision/calibration.cpp
  src/vision/camera.cpp
  src/vision/chessboard.cpp
  src/vision/eight_point.cpp
  src/vision/fast.cpp
  src/vision/good.cpp
  src/vision/utils.cpp
  src/vision/vo.cpp
)
SET(
  YARL_DEPS
  yarl
  xml2
  ceres
  ${OpenCV_LIBS}
  gtest
  glog
  pthread
)

# TESTS
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/tests)
FILE(COPY tests/data DESTINATION ${PROJECT_BINARY_DIR}/tests)
ADD_EXECUTABLE(
  # TARGET
  yarl_tests
  # TESTS
  # OPTIMIZATION CERES
  tests/optimization/ceres/ba_test.cpp
  tests/optimization/ceres/ceres_examples_test.cpp
  # OPTIMIZATION GP
  tests/optimization/gp/data_test.cpp
  tests/optimization/gp/node_test.cpp
  tests/optimization/gp/tree_test.cpp
  # OPTIMIZATION OPTIMIZERS
  tests/optimization/optimizers/gdopt_test.cpp
  tests/optimization/optimizers/llsopt_test.cpp
  tests/optimization/optimizers/lmaopt_test.cpp
  tests/optimization/optimizers/ransac_test.cpp
  # UTILS
  tests/utils/config_test.cpp
  tests/utils/data_test.cpp
  tests/utils/file_test.cpp
  tests/utils/math_test.cpp
  tests/utils/stats_test.cpp
  tests/utils/time_test.cpp
  # VISION
  tests/vision/calibration_test.cpp
  tests/vision/camera_test.cpp
  tests/vision/chessboard_test.cpp
  tests/vision/eight_point_test.cpp
  tests/vision/vo_test.cpp
  # TEST RUNNER
  tests/test_runner.cpp
)
TARGET_LINK_LIBRARIES(yarl_tests ${YARL_DEPS})
