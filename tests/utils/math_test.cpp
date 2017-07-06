#include "yarl/test.hpp"
#include "yarl/utils/math.hpp"

namespace yarl {

TEST(Utils, sandbox2) {
  double roll = 0.1;
  double pitch = 0.2;
  double yaw = 0.3;
  Eigen::AngleAxisd rollAngle(roll, Eigen::Vector3d::UnitX());
  Eigen::AngleAxisd yawAngle(yaw, Eigen::Vector3d::UnitY());
  Eigen::AngleAxisd pitchAngle(pitch, Eigen::Vector3d::UnitZ());
  Eigen::Quaternion<double> q1 = rollAngle * pitchAngle * yawAngle;

  Vec3 euler{0.1, 0.2, 0.3};
  Quaternion q2;
  euler2quat(euler, 123, q2);

  std::cout << q1.w() << std::endl;
  std::cout << q1.x() << std::endl;
  std::cout << q1.y() << std::endl;
  std::cout << q1.z() << std::endl;
  std::cout << std::endl;

  std::cout << q2.w() << std::endl;
  std::cout << q2.x() << std::endl;
  std::cout << q2.y() << std::endl;
  std::cout << q2.z() << std::endl;

  // Eigen::Matrix3d rotationMatrix = q.toRotationMatrix();
  // Vec3 v{1.0, 2.0, 3.0};
  // std::cout << rotationMatrix << std::endl;
  // std::cout << rotationMatrix * v.normalized() << std::endl;
}

TEST(Utils, median) {
  std::vector<double> v;

  v.push_back(6);
  v.push_back(3);
  v.push_back(4);
  v.push_back(1);
  v.push_back(5);
  v.push_back(8);

  EXPECT_FLOAT_EQ(4.5, median(v));

  v.push_back(9);
  EXPECT_FLOAT_EQ(5.0, median(v));
}

TEST(Utils, deg2radAndrad2deg) {
  double d_deg;
  double d_rad;

  d_deg = 10;
  d_rad = deg2rad(d_deg);
  EXPECT_FLOAT_EQ(d_deg, rad2deg(d_rad));
}

TEST(Utils, euler2quat) {
  float roll;
  float pitch;
  float yaw;
  Vec3 euler;
  Quaternion q;

  // check identity quat is returned
  roll = 0;
  pitch = 0;
  yaw = 0;

  euler << roll, pitch, yaw;
  euler2quat(euler, 321, q);
  EXPECT_FLOAT_EQ(0.0, q.x());
  EXPECT_FLOAT_EQ(0.0, q.y());
  EXPECT_FLOAT_EQ(0.0, q.z());
  EXPECT_FLOAT_EQ(1.0, q.w());

  // check valid quat is returned
  roll = M_PI / 2;
  pitch = M_PI;
  yaw = -M_PI / 2;

  euler << roll, pitch, yaw;
  euler2quat(euler, 321, q);
  EXPECT_FLOAT_EQ(0.5, q.x());
  EXPECT_FLOAT_EQ(0.5, q.y());
  EXPECT_FLOAT_EQ(-0.5, q.z());
  EXPECT_FLOAT_EQ(-0.5, q.w());
}

TEST(Utils, sandbox) {
  double roll, pitch, yaw;
  Vec3 euler;
  Quaternion q_nwu, q_ned;

  roll = deg2rad(10.0);
  pitch = deg2rad(20.0);
  yaw = deg2rad(30.0);
  euler << roll, pitch, yaw;

  // NWU
  euler2quat(euler, 321, q_nwu);

  // NWU to NED
  nwu2ned(q_nwu, q_ned);
  quat2euler(q_ned, 321, euler);
  EXPECT_FLOAT_EQ(10, rad2deg(euler(0)));
  EXPECT_FLOAT_EQ(-20, rad2deg(euler(1)));
  EXPECT_FLOAT_EQ(-30, rad2deg(euler(2)));

  // NED to NWU
  ned2nwu(q_ned, q_nwu);
  quat2euler(q_nwu, 321, euler);
  EXPECT_FLOAT_EQ(10, rad2deg(euler(0)));
  EXPECT_FLOAT_EQ(20, rad2deg(euler(1)));
  EXPECT_FLOAT_EQ(30, rad2deg(euler(2)));
}

TEST(Utils, euler2rot) {
  double roll;
  double pitch;
  double yaw;
  Vec3 euler;
  Mat3 rot;

  double r01, r02, r03;
  double r11, r12, r13;
  double r21, r22, r23;

  // test roll, pitch, yaw set to 0
  roll = 0.0;
  pitch = 0.0;
  yaw = 0.0;
  euler << roll, pitch, yaw;
  euler2rot(euler, 321, rot);

  r01 = 1.0;
  r02 = 0.0;
  r03 = 0.0;

  r11 = 0.0;
  r12 = 1.0;
  r13 = 0.0;

  r21 = 0.0;
  r22 = 0.0;
  r23 = 1.0;

  EXPECT_FLOAT_EQ(r01, rot(0, 0));
  EXPECT_FLOAT_EQ(r02, rot(0, 1));
  EXPECT_FLOAT_EQ(r03, rot(0, 2));

  EXPECT_FLOAT_EQ(r11, rot(1, 0));
  EXPECT_FLOAT_EQ(r12, rot(1, 1));
  EXPECT_FLOAT_EQ(r13, rot(1, 2));

  EXPECT_FLOAT_EQ(r21, rot(2, 0));
  EXPECT_FLOAT_EQ(r22, rot(2, 1));
  EXPECT_FLOAT_EQ(r23, rot(2, 2));
}

TEST(Utils, enu2nwu) {
  Vec3 enu, nwu;

  enu << 1.0, 2.0, 3.0;
  enu2nwu(enu, nwu);

  EXPECT_FLOAT_EQ(2.0, nwu(0));
  EXPECT_FLOAT_EQ(-1.0, nwu(1));
  EXPECT_FLOAT_EQ(3.0, nwu(2));
}

TEST(Utils, nwu2enu) {
  Vec3 enu, nwu;

  nwu << 1.0, 2.0, 3.0;
  nwu2enu(nwu, enu);

  EXPECT_FLOAT_EQ(-2.0, enu(0));
  EXPECT_FLOAT_EQ(1.0, enu(1));
  EXPECT_FLOAT_EQ(3.0, enu(2));
}

TEST(Utils, cf2enu) {
  Vec3 cf, enu;

  cf << 1.0, 2.0, 3.0;
  cf2enu(cf, enu);

  EXPECT_FLOAT_EQ(1.0, enu(0));
  EXPECT_FLOAT_EQ(3.0, enu(1));
  EXPECT_FLOAT_EQ(-2.0, enu(2));
}

TEST(Utils, target2body) {
  Vec3 target_pos_if;
  Vec3 body_pos_if;
  Vec3 euler;
  Quaternion quat;
  Vec3 target_pos_bf;

  // setup
  target_pos_if << 2.0, 1.0, 0.0;
  body_pos_if << 1.0, 2.0, 0.0;

  // TEST EULER VERSION OF target2body()
  // test 0 degree
  euler << 0.0, 0.0, deg2rad(0.0);
  target2body(target_pos_if, body_pos_if, euler, target_pos_bf);
  std::cout << target_pos_bf.transpose() << std::endl;

  EXPECT_FLOAT_EQ(-1.0, target_pos_bf(0));
  EXPECT_FLOAT_EQ(-1.0, target_pos_bf(1));
  EXPECT_FLOAT_EQ(0.0, target_pos_bf(2));

  // test 90 degree
  euler << 0.0, 0.0, deg2rad(90.0);
  target2body(target_pos_if, body_pos_if, euler, target_pos_bf);
  std::cout << target_pos_bf.transpose() << std::endl;

  EXPECT_FLOAT_EQ(-1.0, target_pos_bf(0));
  EXPECT_FLOAT_EQ(1.0, target_pos_bf(1));
  EXPECT_FLOAT_EQ(0.0, target_pos_bf(2));

  // test 180 degree
  euler << 0.0, 0.0, deg2rad(180.0);
  target2body(target_pos_if, body_pos_if, euler, target_pos_bf);
  std::cout << target_pos_bf.transpose() << std::endl;

  EXPECT_FLOAT_EQ(1.0, target_pos_bf(0));
  EXPECT_FLOAT_EQ(1.0, target_pos_bf(1));
  EXPECT_FLOAT_EQ(0.0, target_pos_bf(2));

  // test 270 degree
  euler << 0.0, 0.0, deg2rad(270.0);
  target2body(target_pos_if, body_pos_if, euler, target_pos_bf);
  std::cout << target_pos_bf.transpose() << std::endl;

  EXPECT_FLOAT_EQ(1.0, target_pos_bf(0));
  EXPECT_FLOAT_EQ(-1.0, target_pos_bf(1));
  EXPECT_FLOAT_EQ(0.0, target_pos_bf(2));

  // TEST QUATERNION VERSION OF target2body()
  // test 0 degree
  euler << 0.0, 0.0, deg2rad(0.0);
  euler2quat(euler, 123, quat);
  target2body(target_pos_if, body_pos_if, quat, target_pos_bf);

  EXPECT_FLOAT_EQ(-1.0, target_pos_bf(0));
  EXPECT_FLOAT_EQ(-1.0, target_pos_bf(1));
  EXPECT_FLOAT_EQ(0.0, target_pos_bf(2));

  // test 90 degree
  euler << 0.0, 0.0, deg2rad(90.0);
  euler2quat(euler, 123, quat);
  target2body(target_pos_if, body_pos_if, quat, target_pos_bf);

  EXPECT_FLOAT_EQ(-1.0, target_pos_bf(0));
  EXPECT_FLOAT_EQ(1.0, target_pos_bf(1));
  EXPECT_FLOAT_EQ(0.0, target_pos_bf(2));

  // test 180 degree
  euler << 0.0, 0.0, deg2rad(180.0);
  euler2quat(euler, 321, quat);
  target2body(target_pos_if, body_pos_if, quat, target_pos_bf);

  EXPECT_FLOAT_EQ(1.0, target_pos_bf(0));
  EXPECT_FLOAT_EQ(1.0, target_pos_bf(1));
  EXPECT_FLOAT_EQ(0.0, target_pos_bf(2));

  // test 270 degree
  euler << 0.0, 0.0, deg2rad(270.0);
  euler2quat(euler, 321, quat);
  target2body(target_pos_if, body_pos_if, quat, target_pos_bf);

  EXPECT_FLOAT_EQ(1.0, target_pos_bf(0));
  EXPECT_FLOAT_EQ(-1.0, target_pos_bf(1));
  EXPECT_FLOAT_EQ(0.0, target_pos_bf(2));
}

TEST(Utils, target2bodyplanar) {
  Vec3 target_pos_if;
  Vec3 body_pos_if;
  Vec3 euler;
  Quaternion quat;
  Vec3 target_pos_bpf;

  // setup
  target_pos_if << 2.0, 1.0, 0.0;
  body_pos_if << 1.0, 2.0, 0.0;

  // TEST EULER VERSION OF target2bodyplanar()
  // test 0 degree
  euler << 0.0, 0.0, deg2rad(0.0);
  target2bodyplanar(target_pos_if, body_pos_if, euler, target_pos_bpf);
  std::cout << target_pos_bpf.transpose() << std::endl;

  EXPECT_FLOAT_EQ(-1.0, target_pos_bpf(0));
  EXPECT_FLOAT_EQ(-1.0, target_pos_bpf(1));
  EXPECT_FLOAT_EQ(0.0, target_pos_bpf(2));

  // test 90 degree
  euler << 0.0, 0.0, deg2rad(90.0);
  target2bodyplanar(target_pos_if, body_pos_if, euler, target_pos_bpf);
  std::cout << target_pos_bpf.transpose() << std::endl;

  EXPECT_FLOAT_EQ(-1.0, target_pos_bpf(0));
  EXPECT_FLOAT_EQ(1.0, target_pos_bpf(1));
  EXPECT_FLOAT_EQ(0.0, target_pos_bpf(2));

  // test 180 degree
  euler << 0.0, 0.0, deg2rad(180.0);
  target2bodyplanar(target_pos_if, body_pos_if, euler, target_pos_bpf);
  std::cout << target_pos_bpf.transpose() << std::endl;

  EXPECT_FLOAT_EQ(1.0, target_pos_bpf(0));
  EXPECT_FLOAT_EQ(1.0, target_pos_bpf(1));
  EXPECT_FLOAT_EQ(0.0, target_pos_bpf(2));

  // test 270 degree
  euler << 0.0, 0.0, deg2rad(270.0);
  target2bodyplanar(target_pos_if, body_pos_if, euler, target_pos_bpf);
  std::cout << target_pos_bpf.transpose() << std::endl;

  EXPECT_FLOAT_EQ(1.0, target_pos_bpf(0));
  EXPECT_FLOAT_EQ(-1.0, target_pos_bpf(1));
  EXPECT_FLOAT_EQ(0.0, target_pos_bpf(2));

  // TEST QUATERNION VERSION OF target2bodyplanar()
  // test 0 degree
  euler << 0.0, 0.0, deg2rad(0.0);
  euler2quat(euler, 123, quat);
  target2bodyplanar(target_pos_if, body_pos_if, quat, target_pos_bpf);

  EXPECT_FLOAT_EQ(-1.0, target_pos_bpf(0));
  EXPECT_FLOAT_EQ(-1.0, target_pos_bpf(1));
  EXPECT_FLOAT_EQ(0.0, target_pos_bpf(2));

  // test 90 degree
  euler << 0.0, 0.0, deg2rad(90.0);
  euler2quat(euler, 123, quat);
  target2bodyplanar(target_pos_if, body_pos_if, quat, target_pos_bpf);

  EXPECT_FLOAT_EQ(-1.0, target_pos_bpf(0));
  EXPECT_FLOAT_EQ(1.0, target_pos_bpf(1));
  EXPECT_FLOAT_EQ(0.0, target_pos_bpf(2));

  // test 180 degree
  euler << 0.0, 0.0, deg2rad(180.0);
  euler2quat(euler, 321, quat);
  target2bodyplanar(target_pos_if, body_pos_if, quat, target_pos_bpf);

  EXPECT_FLOAT_EQ(1.0, target_pos_bpf(0));
  EXPECT_FLOAT_EQ(1.0, target_pos_bpf(1));
  EXPECT_FLOAT_EQ(0.0, target_pos_bpf(2));

  // test 270 degree
  euler << 0.0, 0.0, deg2rad(270.0);
  euler2quat(euler, 321, quat);
  target2bodyplanar(target_pos_if, body_pos_if, quat, target_pos_bpf);

  EXPECT_FLOAT_EQ(1.0, target_pos_bpf(0));
  EXPECT_FLOAT_EQ(-1.0, target_pos_bpf(1));
  EXPECT_FLOAT_EQ(0.0, target_pos_bpf(2));
}

TEST(Utils, target2inertial) {
  Vec3 target_pos_bf, target_pos_if, body_pos_if, euler;
  Quaternion quat;

  // setup
  target_pos_bf << 2.0, 1.0, 0.0;
  body_pos_if << 1.0, 2.0, 0.0;

  // TEST EULER VERSION OF target2inertial()
  // test 0 degree
  euler << 0.0, 0.0, deg2rad(0.0);
  target2inertial(target_pos_bf, body_pos_if, euler, target_pos_if);
  std::cout << target_pos_if.transpose() << std::endl;

  EXPECT_FLOAT_EQ(0.0, target_pos_if(0));
  EXPECT_FLOAT_EQ(4.0, target_pos_if(1));
  EXPECT_FLOAT_EQ(0.0, target_pos_if(2));

  // test 90 degree
  euler << 0.0, 0.0, deg2rad(90.0);
  target2inertial(target_pos_bf, body_pos_if, euler, target_pos_if);
  std::cout << target_pos_if.transpose() << std::endl;

  EXPECT_FLOAT_EQ(-1.0, target_pos_if(0));
  EXPECT_FLOAT_EQ(1.0, target_pos_if(1));
  EXPECT_FLOAT_EQ(0.0, target_pos_if(2));

  // test 180 degree
  euler << 0.0, 0.0, deg2rad(180.0);
  target2inertial(target_pos_bf, body_pos_if, euler, target_pos_if);
  std::cout << target_pos_if.transpose() << std::endl;

  EXPECT_FLOAT_EQ(2.0, target_pos_if(0));
  EXPECT_FLOAT_EQ(0.0, target_pos_if(1));
  EXPECT_FLOAT_EQ(0.0, target_pos_if(2));

  // test 270 degree
  euler << 0.0, 0.0, deg2rad(270.0);
  target2inertial(target_pos_bf, body_pos_if, euler, target_pos_if);
  std::cout << target_pos_if.transpose() << std::endl;

  EXPECT_FLOAT_EQ(3.0, target_pos_if(0));
  EXPECT_FLOAT_EQ(3.0, target_pos_if(1));
  EXPECT_FLOAT_EQ(0.0, target_pos_if(2));

  // TEST QUATERNION VERSION OF target2inertial()
  // test 0 degree
  euler << 0.0, 0.0, deg2rad(0.0);
  euler2quat(euler, 321, quat);
  target2inertial(target_pos_bf, body_pos_if, quat, target_pos_if);
  std::cout << target_pos_if.transpose() << std::endl;

  EXPECT_FLOAT_EQ(0.0, target_pos_if(0));
  EXPECT_FLOAT_EQ(4.0, target_pos_if(1));
  EXPECT_FLOAT_EQ(0.0, target_pos_if(2));

  // test 90 degree
  euler << 0.0, 0.0, deg2rad(90.0);
  euler2quat(euler, 321, quat);
  target2inertial(target_pos_bf, body_pos_if, quat, target_pos_if);
  std::cout << target_pos_if.transpose() << std::endl;

  EXPECT_FLOAT_EQ(-1.0, target_pos_if(0));
  EXPECT_FLOAT_EQ(1.0, target_pos_if(1));
  EXPECT_FLOAT_EQ(0.0, target_pos_if(2));

  // test 180 degree
  euler << 0.0, 0.0, deg2rad(180.0);
  euler2quat(euler, 321, quat);
  target2inertial(target_pos_bf, body_pos_if, quat, target_pos_if);
  std::cout << target_pos_if.transpose() << std::endl;

  EXPECT_FLOAT_EQ(2.0, target_pos_if(0));
  EXPECT_FLOAT_EQ(0.0, target_pos_if(1));
  EXPECT_FLOAT_EQ(0.0, target_pos_if(2));

  // test 270 degree
  euler << 0.0, 0.0, deg2rad(270.0);
  euler2quat(euler, 321, quat);
  target2inertial(target_pos_bf, body_pos_if, quat, target_pos_if);
  std::cout << target_pos_if.transpose() << std::endl;

  EXPECT_FLOAT_EQ(3.0, target_pos_if(0));
  EXPECT_FLOAT_EQ(3.0, target_pos_if(1));
  EXPECT_FLOAT_EQ(0.0, target_pos_if(2));
}

TEST(Utils, inertial2body) {
  Vec3 enu_if, nwu_bf, euler;
  Quaternion orientation_if;

  // test 0 yaw
  euler << 0, 0, deg2rad(0);
  euler2quat(euler, 321, orientation_if);
  enu_if << 1, 0, 0;
  inertial2body(enu_if, orientation_if, nwu_bf);

  EXPECT_FLOAT_EQ(0, round(nwu_bf(0)));
  EXPECT_FLOAT_EQ(-1, round(nwu_bf(1)));
  EXPECT_FLOAT_EQ(0, round(nwu_bf(2)));

  // test 90 deg yaw
  euler << 0, 0, deg2rad(90);
  euler2quat(euler, 321, orientation_if);
  enu_if << 1, 0, 0;
  inertial2body(enu_if, orientation_if, nwu_bf);

  EXPECT_FLOAT_EQ(-1, round(nwu_bf(0)));
  EXPECT_FLOAT_EQ(0, round(nwu_bf(1)));
  EXPECT_FLOAT_EQ(0, round(nwu_bf(2)));

  // test 180 deg yaw
  euler << 0, 0, deg2rad(180);
  euler2quat(euler, 321, orientation_if);
  enu_if << 1, 0, 0;
  inertial2body(enu_if, orientation_if, nwu_bf);

  EXPECT_FLOAT_EQ(0, round(nwu_bf(0)));
  EXPECT_FLOAT_EQ(1, round(nwu_bf(1)));
  EXPECT_FLOAT_EQ(0, round(nwu_bf(2)));

  // test -90 deg yaw
  euler << 0, 0, deg2rad(-90);
  euler2quat(euler, 321, orientation_if);
  enu_if << 1, 0, 0;
  inertial2body(enu_if, orientation_if, nwu_bf);

  EXPECT_FLOAT_EQ(1, round(nwu_bf(0)));
  EXPECT_FLOAT_EQ(0, round(nwu_bf(1)));
  EXPECT_FLOAT_EQ(0, round(nwu_bf(2)));
}

TEST(Utils, wrapTo180) {
  double retval;

  // normal cases
  retval = wrapTo180(90.0);
  EXPECT_FLOAT_EQ(90.0, retval);

  retval = wrapTo180(180.0);
  EXPECT_FLOAT_EQ(-180.0, retval);

  retval = wrapTo180(270.0);
  EXPECT_FLOAT_EQ(-90.0, retval);

  retval = wrapTo180(360.0);
  EXPECT_FLOAT_EQ(0.0, retval);

  // edge cases
  retval = wrapTo180(-180.0);
  EXPECT_FLOAT_EQ(-180.0, retval);

  retval = wrapTo180(-90.0);
  EXPECT_FLOAT_EQ(-90.0, retval);

  retval = wrapTo180(450.0);
  EXPECT_FLOAT_EQ(90.0, retval);
}

TEST(Utils, wrapTo360) {
  double retval;

  // normal cases
  retval = wrapTo360(90.0);
  EXPECT_FLOAT_EQ(90.0, retval);

  retval = wrapTo360(180.0);
  EXPECT_FLOAT_EQ(180.0, retval);

  retval = wrapTo360(270.0);
  EXPECT_FLOAT_EQ(270.0, retval);

  retval = wrapTo360(360.0);
  EXPECT_FLOAT_EQ(0.0, retval);

  retval = wrapTo360(450.0);
  EXPECT_FLOAT_EQ(90.0, retval);

  // edge cases
  retval = wrapTo360(-180.0);
  EXPECT_FLOAT_EQ(180.0, retval);

  retval = wrapTo360(-90.0);
  EXPECT_FLOAT_EQ(270.0, retval);
}

TEST(Utils, cross_track_error) {
  Vec2 pos, p1, p2;

  pos << 2, 2;
  p1 << 1, 1;
  p2 << 5, 5;
  EXPECT_FLOAT_EQ(0.0, cross_track_error(p1, p2, pos));

  pos << 2, 3;
  p1 << 1, 1;
  p2 << 5, 5;
  EXPECT_TRUE(0.0 < cross_track_error(p1, p2, pos));
}

TEST(Utils, point_left_right) {
  Vec2 pos, p1, p2;

  pos << 2, 3;
  p1 << 1, 1;
  p2 << 5, 5;
  EXPECT_EQ(1, point_left_right(p1, p2, pos));

  pos << 2, 1;
  p1 << 1, 1;
  p2 << 5, 5;
  EXPECT_EQ(2, point_left_right(p1, p2, pos));

  pos << 2, 2;
  p1 << 1, 1;
  p2 << 5, 5;
  EXPECT_EQ(0, point_left_right(p1, p2, pos));

  pos << 2, 1;
  p1 << 5, 5;
  p2 << 1, 1;
  EXPECT_EQ(1, point_left_right(p1, p2, pos));

  pos << 2, 3;
  p1 << 5, 5;
  p2 << 1, 1;
  EXPECT_EQ(2, point_left_right(p1, p2, pos));

  pos << 2, 2;
  p1 << 5, 5;
  p2 << 1, 1;
  EXPECT_EQ(0, point_left_right(p1, p2, pos));
}

// TEST(Utils, closest_point) {
//   int retval;
//   Vec2 p1, p2, p3, closest;
//
//   // setup
//   p1 << 0, 0;
//   p2 << 5, 0;
//
//   // point middle of point a, b
//   p3 << 2, 2;
//   retval = closest_point(p1, p2, p3, closest);
//   EXPECT_EQ(0, retval);
//   EXPECT_FLOAT_EQ(2.0, closest(0));
//   EXPECT_FLOAT_EQ(0.0, closest(1));
//
//   // point before of point a
//   p3 << -1, 2;
//   retval = closest_point(p1, p2, p3, closest);
//   EXPECT_EQ(1, retval);
//   EXPECT_FLOAT_EQ(-1.0, closest(0));
//   EXPECT_FLOAT_EQ(0.0, closest(1));
//
//   // point after point b
//   p3 << 6, 2;
//   retval = closest_point(p1, p2, p3, closest);
//   EXPECT_EQ(2, retval);
//   EXPECT_FLOAT_EQ(6.0, closest(0));
//   EXPECT_FLOAT_EQ(0.0, closest(1));
//
//   // if point 1 and 2 are same
//   p1 << 0, 0;
//   p2 << 0, 0;
//   p3 << 0, 2;
//   retval = closest_point(p1, p2, p3, closest);
//   EXPECT_EQ(-1, retval);
//   EXPECT_FLOAT_EQ(0.0, closest(0));
//   EXPECT_FLOAT_EQ(0.0, closest(1));
// }

TEST(Utils, linear_interpolation) {
  Vec2 a, b, result;

  a << 0, 5;
  b << 5, 0;
  result = linear_interpolation(a, b, 0.8);

  std::cout << result << std::endl;
}

}  // namespace yarl
