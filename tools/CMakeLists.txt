SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/tools)

ADD_EXECUTABLE(calibration vision/calibration.cpp)
TARGET_LINK_LIBRARIES(calibration ${YARL_DEPS})

# ADD_EXECUTABLE(feature_demo vision/feature_demo.cpp)
# TARGET_LINK_LIBRARIES(feature_demo ${YARL_DEPS})

# ADD_EXECUTABLE(optical_flow vision/optical_flow.cpp)
# TARGET_LINK_LIBRARIES(optical_flow ${YARL_DEPS})

# ADD_EXECUTABLE(video_capture vision/video_capture.cpp)
# TARGET_LINK_LIBRARIES(video_capture ${YARL_DEPS})
