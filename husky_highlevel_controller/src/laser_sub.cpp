#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Float64.h>

double min_dist = 0;

void laserCallback(const sensor_msgs::LaserScan& msg)
{
    min_dist = DBL_MAX;
    for(int i = 0; i < msg.ranges.size(); i++)
    {
        if(min_dist > msg.ranges[i])
        {
            min_dist = msg.ranges[i];
        }
    }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "laser");
    ros::NodeHandle nh;

    std::string pub_topic, sub_topic;
    int pub_queue, sub_queue; double rate;

    nh.getParam("sub_topic", sub_topic);
    nh.getParam("pub_topic", pub_topic);
    nh.getParam("pub_queue", pub_queue);
    nh.getParam("sub_queue", sub_queue);
    nh.getParam("rate", rate);

    ros::Subscriber laserSub = nh.subscribe(sub_topic, sub_queue, laserCallback);
    ros::Publisher debugPub = nh.advertise<std_msgs::Float64>(pub_topic, pub_queue);

    ros::Rate loopRate(rate);
    std_msgs::Float64 float_msg;

    while(ros::ok())
    {
        ros::spinOnce();
        float_msg.data = min_dist;
        debugPub.publish(float_msg);
        loopRate.sleep();
    }

    return 0;
}