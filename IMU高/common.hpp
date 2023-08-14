//
//  common.hpp
//  IMU高
//
//  Created by wzb on 2023/8/12.
//

#ifndef COMMON_HPP
#define COMMON_HPP

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

struct IMUMsg
{
  IMUMsg() = default;
  IMUMsg(double timestamp, Eigen::Vector3d gyro, Eigen::Vector3d acc)
      : timestamp_(timestamp), acc_(acc), gyro_(gyro){};

  double timestamp_{0.0};
  Eigen::Vector3d acc_;
  Eigen::Vector3d gyro_;
};

struct IMUIntegrationResult
{
  IMUIntegrationResult() = default;
  IMUIntegrationResult(const double &timestamp, const Eigen::Vector3d &P,
                       const Eigen::Quaterniond &Q, const Eigen::Vector3d &V)
      : timestamp_(timestamp), P_(P), V_(V), Q_(Q){};

  double timestamp_{0.0};
  Eigen::Vector3d P_;
  Eigen::Vector3d V_;
  Eigen::Quaterniond Q_;
};

inline void ReadImuMsg(std::ifstream &fin, std::vector<IMUMsg> &imu_msg)
{
  if (!fin)
  {
    std::cerr << "Coule not find file\n";
    return;
  }
  while (!fin.eof())
  {
    std::string line;
    std::getline(fin, line);
    if (line.empty())
    {
      continue;
    }

    if (line[0] == '#')
    {
      continue;
    }

    std::stringstream ss;
    ss << line;
    std::string data_type;
    ss >> data_type;
    if (data_type == "IMU")
    {
      double time, gx, gy, gz, ax, ay, az;
      ss >> time >> gx >> gy >> gz >> ax >> ay >> az;
      imu_msg.push_back(IMUMsg(time, Eigen::Vector3d(gx, gy, gz),
                               Eigen::Vector3d(ax, ay, az)));
    }
  }
  std::cout << "Read IMU msgs success\n";
}

inline void SaveImuIntegrationResult(
    const std::string &file_path,
    const std::vector<IMUIntegrationResult> &imu_inte_result)
{
  std::ofstream fout(file_path);
  for (const auto &imu_traj : imu_inte_result)
  {
    fout << std::setprecision(18) << imu_traj.timestamp_ << " " << std::setprecision(9);
    fout << imu_traj.P_(0) << " " << imu_traj.P_(1) << " " << imu_traj.P_(2) << " ";
    //fout << imu_traj.Q_.w() << " " << imu_traj.Q_.x() << " " << imu_traj.Q_.y() << " " << imu_traj.Q_.z() << " ";
    //fout << imu_traj.V_(0) << " " << imu_traj.V_(1) << " " << imu_traj.V_(2) << " ";
    fout << std::endl;
  }
}

#endif  // COMMON_HPP
