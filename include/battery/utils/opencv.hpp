#ifndef UTILS_OPENCV_HPP
#define UTILS_OPENCV_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace battery {

bool cvMatIsEqual(const cv::Mat m1, const cv::Mat m2);

} // end of battery namespace
#endif
