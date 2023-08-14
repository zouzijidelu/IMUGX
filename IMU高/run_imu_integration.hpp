//
//  run_imu_integration.hpp
//  IMU高
//
//  Created by wzb on 2023/8/12.
//

//#include <gflags/gflags.h>

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <iostream>
#include <ostream>

#include "common.hpp"
#include "imu_integration.hpp"

//DEFINE_string(txt_file_path, "../slam_in_auto_driving/chapter3/dataset/10.txt",
//              "Imu integration file");
//DEFINE_string(output_inter_trajectory_path, "./output_trajectory.txt",
//              "output trajectory file");

int main(int argc, char *argv[])
{
  //google::ParseCommandLineFlags(&argc, &argv, true);
  std::ifstream fin("/Users/wzb/Desktop/5i5j/调研项目/IMU高/IMU高/imu0数据.txt");
//    std::ifstream fin("/Users/wzb/Desktop/5i5j/调研项目/IMU高/IMU高/10.txt");
  std::vector<IMUMsg> imu_msgs;
  std::vector<IMUIntegrationResult> imu_inter_result;
  ReadImuMsg(fin, imu_msgs);

  // 该实验中，我们假设零偏已知
  Eigen::Vector3d gravity(0, 0, -9.8);  // 重力方向
  Eigen::Vector3d init_bg(00.000224886, -7.61038e-05, -0.000742259);
  Eigen::Vector3d init_ba(-0.165205, 0.0926887, 0.0058049);

  ImuIntegration imu_integration(gravity, init_bg, init_ba);

  for (auto &imu_msg : imu_msgs)
  {
    imu_integration.AddNewImgMessage(imu_msg);
    imu_inter_result.push_back(IMUIntegrationResult(
        imu_msg.timestamp_, imu_integration.GetPosition(),
        imu_integration.GetRotation(), imu_integration.GetVelocity()));
  }

  SaveImuIntegrationResult("/Users/wzb/Desktop/5i5j/调研项目/IMU高/IMU高/output_trajectory.txt",imu_inter_result);
  // 高博书中程序输出的结果
  // T: 1624429630.2702086
  // P : -3387943.36 5737523.81 -512933.307
  // Q : 0.982857044 -0.132676506 0.0940114453 0.0868954789
  // V : -572.166705 4626.10758 -496.605214
  std::cout << "Final P: " << imu_integration.GetPosition().transpose()
            << std::endl;
  std::cout << "Final V: " << imu_integration.GetVelocity().transpose()
            << std::endl;
  std::cout << "Final Q: " << imu_integration.GetRotation().coeffs().transpose()
            << std::endl;

  return 0;
}
