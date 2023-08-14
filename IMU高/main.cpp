//
//  main.cpp
//  IMU高
//
//  Created by wzb on 2023/8/12.
//

#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <string>
//#include <cmath>
//#include <vector>
//#include <Eigen/Dense>
//#include "Eigen/src/Geometry/EulerAngles.h"
//#include "unistd.h"
//
/////路径
//std::string filePath = "/Users/wzb/Desktop/5i5j/调研项目/imu方案/imu-data/手机平放头朝左/imu0数据.txt";
//std::string outputPath = "/Users/wzb/Desktop/5i5j/调研项目/imu方案/imu-data/手机平放头朝左/";
//std::string fileName_out = "结果数据";
//
///*函数 功能*/////////////////////////////////////
//class File
//{
//public:
//
//    /*显示进度条*/
//    void ShowProgressBar(int i, int count)
//    {
//        /*控制台进度条显示*/
//        if (i < count - 1)
//            printf("\r运行中[%.2lf%%]:", i*100.0 / (count - 1));
//        else
//        {
//            printf("\r运行完成[%.2lf%%]:", i*100.0 / (count - 1));
//        }
//        int show_num = i * 20 / count;
//        for (int j = 1; j <= show_num; j++)
//        {
//            std::cout << "█";
//            sleep(0.000001);
//        }
//    }
//
//    /*读取txt，存入imu*/
//    void ReadTxt(std::string filePath, std::vector<ImuData> &imu)
//    {
//        std::cout << "imu读取并存储" << std::endl;
//
//        /*1、读取txt文件*/
//        std::ifstream ifs(filePath);
//        std::string line;
//
//        int i = 0;
//        while (std::getline(ifs, line))//将ifs文件中的每一行字符读入到line中
//        {
//            //跳过表头
//            if (i < rowStartRead)
//            {
//                i++;
//                continue;
//            }
//
//            std::istringstream ss(line);//使用string初始化stringstream
//            //将一行字符存入临时的string容器
//            std::vector<std::string> temp_v;
//            std::string temp;
//            while (ss >> temp)
//                temp_v.push_back(temp);
//            //若读取到空行，跳过
//            if (temp_v.size() == 0)
//            {
//                i++;
//                continue;
//            }
//            //string容器存入p中
//            ImuData p;
//            p.Timestamps = stof(temp_v[0]);//stod//调换y和z
//            p.gyro_x = stof(temp_v[1]);
//            p.gyro_y = stof(temp_v[3]);
//            p.gyro_z = stof(temp_v[2]);
//            p.accel_x = stof(temp_v[4]);
//            p.accel_y = stof(temp_v[6]);
//            //p.accel_y = stof(temp_v[5]) - 9.8f;
//            p.accel_z = stof(temp_v[5]);
//
//            /*2、将p存入imuInf*/
//            imu.push_back(p);
//
//
//            //显示进度条
//            //ShowProgressBar(i, totalRow);
//
//            i++;
//        }
//
//        ifs.close();
//    }
//
//    /*存储数据为txt文件*/
//    void SaveTxt(std::vector<ImuState> imu)
//    {
//        std::ofstream ofs;
//        ofs.flags(std::ios::fixed);
//        ofs.precision(10);//保留小数点后3位
//        ofs.open(outputPath + fileName_out + ".txt", std::ios::out);
//        std::cout << std::endl << "正在保存文件：" + outputPath + fileName_out + ".txt" << std::endl;
//
//        //表头
////        ofs << "Timestamps" << "      "
//        ofs << "X" << "      "
//            << "Y" << "      "
//            << "Z" << "      "
////            << "Heading" << "      "
////            << "Pitch" << "      "
////            << "Roll" << "      "
//        << std::endl;
//        //imu数据
//        for (int i = 0; i < imu.size(); i++)
//        {
////            ofs << i << "      "
//               ofs << imu[i].x << "      "
//                << imu[i].y << "      "
//                << imu[i].z << "      "
////                << imu[i].yaw << "      "
////                << imu[i].pitch << "      "
////                << imu[i].roll
//            << std::endl;
//
//            //显示进度条
//            //ShowProgressBar(i, imu.size());
//        }
//        ofs.close();
//
//    }
//
//private:
//};
//
//
//
//
///*函数 计算*/////////////////////////////////////
///*计算txt行数*/
//int CountLines(std::string filename)
//{
//    std::cout << "正在计算txt总行数......";
//
//    std::ifstream ReadFile;
//    int n = 0;
//    std::string tmp;
//    ReadFile.open(filename, std::ios::in);//ios::in 表示以只读的方式读取文件
//    if (ReadFile.fail())//文件打开失败:返回0
//    {
//        return 0;
//    }
//    else//文件存在
//    {
//        while (getline(ReadFile, tmp, '\n'))
//        {
//            n++;
//        }
//        ReadFile.close();
//        std::cout << "计算完成，文件行数：" << n << std::endl;
//        return n;
//    }
//}

//int main(int argc, const char * argv[]) {
//    // insert code here...
//    std::cout << "Hello, World!\n";
//    return 0;
//}
