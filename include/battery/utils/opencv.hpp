#ifndef __UTILS_OPENCV_HPP__
#define __UTILS_OPENCV_HPP__

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace battery {

bool cvMatIsEqual(const cv::Mat m1, const cv::Mat m2);

} // end of battery namespace
#endif
