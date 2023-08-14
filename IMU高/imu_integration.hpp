//
//  imu_integration.hpp
//  IMU高
//
//  Created by wzb on 2023/8/12.
//

#ifndef imu_integration_hpp
#define imu_integration_hpp

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include "so3.hpp"

#include "common.hpp"

class ImuIntegration
{
 public:
  ImuIntegration() = default;
  ~ImuIntegration() = default;
  ImuIntegration(const Eigen::Vector3d &gravity, const Eigen::Vector3d &init_bg,
                 const Eigen::Vector3d &init_ba)
      : gravity_(gravity), init_ba_(init_ba), init_bg_(init_bg)
  {
  }

  void AddNewImgMessage(const IMUMsg &imu_msg)
  {
    // Final P: -3.38794e+06  5.73752e+06  -512933
    // 其实第一帧 IMU 数据也可以不判断，因为后面有 dt<0.1 的判断
    if (first_imu_)
    {
      first_imu_ = false;
      timestamp_ = imu_msg.timestamp_;
    }

    double dt = (imu_msg.timestamp_ - timestamp_)*0.001;
//      double dt = (imu_msg.timestamp_ - timestamp_);
    if (dt > 0 && dt < 0.1)
    {
      P_ = P_ + V_ * dt + 0.5 * (R_ * (imu_msg.acc_ - init_ba_)) * dt * dt +
           0.5 * gravity_ * dt * dt;
      V_ = V_ + R_ * (imu_msg.acc_ - init_ba_) * dt + gravity_ * dt;
      R_ = R_ * Sophus::SO3d::exp((imu_msg.gyro_ - init_bg_) * dt);
    }

    timestamp_ = imu_msg.timestamp_;
  }

  Eigen::Vector3d GetPosition() const { return P_; }
  Eigen::Vector3d GetVelocity() const { return V_; }
  Eigen::Quaterniond GetRotation() const { return R_.unit_quaternion(); }

 private:
  Sophus::SO3d R_;
  Eigen::Quaterniond R_quaternion_ = Eigen::Quaterniond::UnitRandom();
  Eigen::Vector3d P_ = Eigen::Vector3d::Zero();
  Eigen::Vector3d V_ = Eigen::Vector3d::Zero();
  Eigen::Vector3d gravity_ = Eigen::Vector3d(0, 0, -9.81);
  Eigen::Vector3d init_ba_ = Eigen::Vector3d::Zero();
  Eigen::Vector3d init_bg_ = Eigen::Vector3d::Zero();
  double timestamp_{0.0};
  bool first_imu_{true};
};

#endif /* imu_integration_hpp */
