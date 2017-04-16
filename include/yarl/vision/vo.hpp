#ifndef YARL_VISION_VO_HPP
#define YARL_VISION_VO_HPP

#include "yarl/utils/utils.hpp"
#include "yarl/vision/camera.hpp"
#include "yarl/vision/utils.hpp"

namespace yarl {

class VisualOdometry {
public:
  bool configured;

  double focal_length;
  cv::Point2f principle_point;

  cv::Mat mask;
  cv::Mat E;
  cv::Mat R;
  cv::Mat t;

  VisualOdometry() :
      configured(false),
      focal_length(0.0),
      principle_point() {}

  int configure(Mat3 K);
  int featureTracking(cv::Mat img_1,
                      cv::Mat img_2,
                      std::vector<cv::Point2f> &pts_1,
                      std::vector<cv::Point2f> &pts_2,
                      std::vector<float> &errors,
                      std::vector<uchar> &status);
  int measure(std::vector<cv::Point2f> &pts_1,
              std::vector<cv::Point2f> &pts_2);
  int drawOpticalFlow(cv::Mat img_1,
                      cv::Mat img_2,
                      std::vector<cv::Point2f> pts_1,
                      std::vector<cv::Point2f> pts_2,
                      cv::Mat &output);
};

}  // end of yarl namespace
#endif
