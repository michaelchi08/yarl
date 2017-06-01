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
#define E_CSV_DATA_LOAD "Error! failed to load test data [%s]!"
#define E_CSV_DATA_OPEN "Error! failed to open file for output [%s]!"

class Pose {
public:
  Vec3 position;
  Quaternion orientation;

  Pose() : position(0.0, 0.0, 0.0), orientation(0.0, 0.0, 0.0, 0.0) {}

  Pose(Vec3 position, Quaternion orientation)
    : position(position), orientation(orientation) {}

  Pose(double roll, double pitch, double yaw, double x, double y, double z) {
    Vec3 euler{roll, pitch, yaw};
    euler2quat(euler, 321, this->orientation);
    this->position << x, y, z;
  }

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

  Twist()
    : linear_x(0),
      linear_y(0),
      linear_z(0),
      angular_x(0),
      angular_y(0),
      angular_z(0) {}
};

/**
 * Reads csv file at `file_path` where `csvrows()` and `csvcols()` returns the
 * number of rows and columns respectively. If the function failed to open the
 * csv file the function will return `-1`.
 */
int csvrows(const std::string &file_path);
int csvcols(const std::string &file_path);

/**
 * Load csv file containing a matrix located at `file_path`, `header` denotes
 * whether a header line exists in the csv file. The parsed matrix will be
 * loaded to `data`. On success the function will return `0` else if an error
 * occured a return value of `-1` will be given.
 */
int csvheader(const std::string &file_path, std::vector<std::string> &fields);
int csv2mat(const std::string &file_path, bool header, MatX &data);

/**
 * Save `data` matrix to file in csv format to location defined by
 * `file_path`. On success the function will return `0` else if an error
 * occured a return value of `-1` will be given.
 */
int mat2csv(const std::string &file_path, MatX data);

}  // namespace yarl
#endif
