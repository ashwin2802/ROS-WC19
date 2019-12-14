#include <ros/ros.h>
#include <std_msgs/String.h>

int main(int argc, char** argv){
    ros::init(argc, argv, "talker");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<std_msgs::String>("chatter",10);
ros::Rate loopRate(30);
    int count = 0;
while(ros::ok()){
    std_msgs::String msg;
    msg.data = "Hello World " + std::to_string(count);
    pub.publish(msg);
    loopRate.sleep();
    count++;} 
return 0;}
