#include <ros/ros.h>
#include <std_msgs/String.h>

std::string data;
void subCallback(std_msgs::String msg){
    data = msg.data;
    ROS_INFO("%s", data.c_str());
return;}

int main(int argc, char** argv){
    ros::init(argc, argv, "listener");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("chatter", 10, subCallback);
    ros::Rate loopRate(30);
    while(ros::ok()){
        ros::spinOnce();
        loopRate.sleep();
    }
    
return 0;}
