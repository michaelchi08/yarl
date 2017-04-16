#ifndef YARL_UTILS_DATA_HPP
#define YARL_UTILS_DATA_HPP

#include <fstream>
#include <iostream>
#include <vector>

#include "yarl/utils/log.hpp"
#include "yarl/utils/math.hpp"
#include "yarl/utils/string.hpp"

namespace yarl {

// CSV ERROR MESSAGES
#define E_CSV_DATA_LOAD "Error! failed to load test data [%s]!!\n"
#define E_CSV_DATA_OPEN "Error! failed to open file for output [%s]!!\n"

class Pose {
public:
  Vec3 position;
  Quaternion orientation;

  Pose();
  Pose(Vec3 position, Quaternion orientation);
  Pose(double roll, double pitch, double yaw, double x, double y, double z);
  Mat3 rotationMatrix();
  void printPosition();
  void printOrientation();
  void print();
};

class Twist {
public:
  double linear_x;
  double linear_y;
  double linear_z;

  double angular_x;
  double angular_y;
  double angular_z;

  Twist() {
    this->linear_x = 0;
    this->linear_y = 0;
    this->linear_z = 0;
    this->angular_x = 0;
    this->angular_y = 0;
    this->angular_z = 0;
  }
};

int csvrows(const std::string &file_path);
int csvcols(const std::string &file_path);
int csvheader(const std::string &file_path, std::vector<std::string> &fields);
int csv2mat(const std::string &file_path, bool header, MatX &data);
int mat2csv(const std::string &file_path, MatX data);

}  // end of yarl namespace
#endif
