#ifndef YARL_VISION_UTILS_HPP
#define YARL_VISION_UTILS_HPP

#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include "yarl/utils/utils.hpp"

namespace yarl {

double focal_length(double hfov, double image_width);
Vec2 focal_length(double hfov,
                  double vfov,
                  double image_width,
                  double image_height);
double diag_focal_length(double hfov,
                         double vfov,
                         double image_width,
                         double image_height);
void cvpts2mat(const std::vector<cv::Point2f> &points, MatX &mat);
void cvmatconcat(const cv::Mat &img1, const cv::Mat &img2, cv::Mat &out);
void projection_matrix(const Mat3 &K, const Mat3 &R, const Vec3 &t, MatX &P);
void normalize_2dpts(double image_width, double image_height, MatX &pts);

}  // end of yarl namespace
#endif
