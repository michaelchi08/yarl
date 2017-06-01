#ifndef YARL_VISION_UTILS_HPP
#define YARL_VISION_UTILS_HPP

#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include "yarl/utils/utils.hpp"

namespace yarl {

/** Calculate theoretical focal length
 *
 * @param fov field of view in radians
 * @param image_width image width in pixels
 */
double focal_length(double fov, double image_width);

/** Calculate theoretical focal length in two dimensions
 * @param hfov, vfov horizontal and vertical field of view in radians
 * @param image_width, image_height image dimensions in pixels
 */
Vec2 focal_length(double hfov,
                  double vfov,
                  double image_width,
                  double image_height);

/** Calculate theoretical diagonal focal length in two dimensions
 * @param hfov, vfov horizontal and vertical field of view in radians
 * @param image_width, image_height image dimensions in pixels
 */
double diag_focal_length(double hfov,
                         double vfov,
                         double image_width,
                         double image_height);

/** Convert 2D keypoints to a matrix
 * @param std::vector of 2D keypoints
 * @param matrix output
 */
void cvpts2mat(const std::vector<cv::Point2f> &points, MatX &mat);

/** Calculate camera projection matrix
 *
 * @param K camera intrinsic matrix
 * @param R camera rotation matrix
 * @param t camera position
 * @param[out] P camera projection matrix
 */
void projection_matrix(const Mat3 &K, const Mat3 &R, const Vec3 &t, MatX &P);

}  // namespace yarl
#endif
