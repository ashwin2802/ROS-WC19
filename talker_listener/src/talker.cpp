#include <ros/ros.h>
#include <talker_listener/Data.h>
#include <std_srvs/Trigger.h>

bool talk = true;

bool serverCallback(std_srvs::Trigger::Request& req, std_srvs::Trigger::Response& resp)
{
    talk = !talk;
    resp.success = true;
    resp.message = "Trigger successful";
    std::cout << "Service called" << std::endl;
    return true;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "talker");
    ros::NodeHandle nh;

    std::string topic_name; double rate_val;

    nh.getParam("topic", topic_name);
    nh.getParam("rate", rate_val);

    ros::Publisher pub = nh.advertise<talker_listener::Data>(topic_name,10);
    ros::ServiceServer server = nh.advertiseService("pause", serverCallback);
    
    ros::Rate loopRate(rate_val);
    int count1 = 0, count2 = 1, count3 = 2;
    
    while(ros::ok())
    {
        talker_listener::Data msg;
        msg.message.data = "Hello World " + std::to_string(count1);
        msg.a = count2; msg.b = count3;

        if(talk) pub.publish(msg);
        ros::spinOnce();
        loopRate.sleep();
        
        count1++; count2+=2; count3+=2;
    } 

    return 0;
}
