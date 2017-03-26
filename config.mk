# GENERAL
CXX = g++
STANDARD = -std=c++11
PROJECT_NAME = yarl
LIB_NAME = lib$(PROJECT_NAME)

# BUILD DIRS
BUILD_PATH = $(PWD)/build
BIN_DIR = $(BUILD_PATH)/bin
OBJ_DIR = $(BUILD_PATH)/obj
TESTS_DIR = $(BUILD_PATH)/tests
LIB_DIR = $(BUILD_PATH)/lib
GTEST_LIB_DIR = ./deps/googletest/googletest/make

# LIBS
STD_LIB = -lm
YAML_CPP_LIB = -lyaml-cpp
OPENCV_LIB = -lopencv_calib3d \
             -lopencv_core \
             -lopencv_features2d \
             -lopencv_flann \
             -lopencv_highgui \
             -lopencv_imgcodecs \
             -lopencv_imgproc \
             -lopencv_ml \
             -lopencv_objdetect \
             -lopencv_photo \
             -lopencv_shape \
             -lopencv_stitching \
             -lopencv_superres \
             -lopencv_video \
             -lopencv_videoio \
             -lopencv_videostab
CERES_LIB = -lceres -lblas
CERES_LIB += -llapack -lcamd -lamd -lccolamd -lcolamd -lcholmod
CERES_LIB += -fopenmp -lpthread -lgomp -lm
CERES_LIB += -lcxsparse
GTEST_LIB = -lglog -lgtest -lpthread

# INCLUDE AND LIBRARY PATHS
INCLUDES = -I/usr/local/include/ \
		   -I/usr/include \
		   -I/usr/include/eigen3 \
		   -I$(PWD)/include
LIBS =  -L/usr/local/lib \
		-L/usr/lib \
        -L$(LIB_DIR) \
        -L$(GTEST_LIB_DIR) \
        -l$(PROJECT_NAME) \
        $(OPENCV_LIB) \
        $(CERES_LIB) \
        $(YAML_CPP_LIB) \
        $(GTEST_LIB)

# COMPILER FLAGS
DEBUG_FLAGS = -g -gdwarf-2
WARN_FLAGS = -Wall

CXXFLAGS = $(DEBUG_FLAGS) \
			$(WARN_FLAGS) \
			$(STANDARD) \
			$(INCLUDES)

# COMMANDS
MAKE_EXE = \
	echo "CXX [$@]"; \
	$(CXX) $(CXXFLAGS) -c $@.c -o $(OBJ_DIR)/$@.o; \
	$(CXX) $(OBJ_DIR)/$@.o -o $(BIN_DIR)/$@ $(LIBS);

MAKE_OBJ = \
	@echo "CXX [$<]"; \
	$(CXX) $(CXXFLAGS) -c $< -o $@;

MAKE_STATIC_LIB = \
	@echo "AR [$@]"; \
	$(AR) $(ARFLAGS) $@ $^;

MAKE_TEST = \
	echo "TEST [$@]"; \
	$(CXX) $(CXXFLAGS) -c $< -o $@;

MAKE_TEST_RUNNER = \
	echo "TEST RUNNER [$@]"; \
	$(CXX) $^ -o $@ $(LIBS);
