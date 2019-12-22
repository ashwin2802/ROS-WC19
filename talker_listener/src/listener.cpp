#include <ros/ros.h>
#include <talker_listener/Data.h>

std::string data;
int num1; int num2;

void subCallback(talker_listener::Data msg)
{
    data = msg.message.data;
    num1 = msg.a; num2 = msg.b;
    ROS_INFO("%s %d %d", data.c_str(), num1, num2);
    return;
}

int main(int argc, char** argv)
{    
    ros::init(argc, argv, "listener");
    ros::NodeHandle nh;

    std::string topic_name; double rate_val;

    nh.getParam("topic", topic_name);
    nh.getParam("rate", rate_val);

    ros::Subscriber sub = nh.subscribe(topic_name, 10, subCallback);
    ros::Rate loopRate(rate_val);

    while(ros::ok())
    {
        ros::spinOnce();
        loopRate.sleep();
    }
    
    return 0;
}
