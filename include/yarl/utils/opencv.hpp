#ifndef YARL_UTILS_OPENCV_HPP
#define YARL_UTILS_OPENCV_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace yarl {

bool cvMatIsEqual(const cv::Mat &m1, const cv::Mat &m2);

}  // end of yarl namespace
#endif
