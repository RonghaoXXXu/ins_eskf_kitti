#ifndef INS_ESKF_INS_ESKF_ROS_WRAPPER_H
#define INS_ESKF_INS_ESKF_ROS_WRAPPER_H


#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/NavSatFix.h>
#include <geometry_msgs/TwistStamped.h>
#include <ins_eskf/ins_eskf.h>

#include <glog/logging.h>
#include <string>
#include <deque>
#include <mutex>
namespace ins_eskf{

class Ins_eskf_ROS_Wrapper{

public:
    Ins_eskf_ROS_Wrapper(ros::NodeHandle &_nh,YAML::Node& _node);

private:
    void imu_cb(const sensor_msgs::ImuConstPtr& imu_in);
    void gps_cb(const sensor_msgs::NavSatFixConstPtr& gps_in);
    void kitti_vel_cb(const geometry_msgs::TwistStampedConstPtr& twist_in);
    void register_sub_pub();
    void initialization_kitti();
    bool synce_measure();
    Ins_eskf::IMU_data imu_msg_2_data(sensor_msgs::Imu _imu_msg); //TODO
    Ins_eskf::GPS_data gps_msg_2_data(sensor_msgs::NavSatFix _gps_msg); //TODO


    void DEBUG_check_synce_measure();
private:
    ros::NodeHandle nh;
    ros::Subscriber sub_imu;
    ros::Subscriber sub_gps;
    ros::Subscriber sub_vel;
    ros::Publisher pub_pos;
    std::shared_ptr<Ins_eskf> p_ins_eskf;

    std::string dataset = "kitti";



    std::string imu_topic,gps_topic;
    std::string kitti_vel_topic;
    bool initialized = false;
    std::mutex mtx;
    std::deque<sensor_msgs::NavSatFix> gps_buf;
    std::deque<sensor_msgs::Imu> imu_buf;
    std::vector<geometry_msgs::TwistStamped> init_twist_buf;
    Ins_eskf::State init_state;
    Ins_eskf::Measure measure;
    double initialization_stamp = -1;
};


}



#endif