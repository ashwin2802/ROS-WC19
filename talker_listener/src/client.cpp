#include <ros/ros.h>
#include <std_srvs/Trigger.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "client");
    ros::NodeHandle nh;

    ros::ServiceClient client = nh.serviceClient<std_srvs::Trigger>("pause");
    ros::Rate loopRate(0.2);

    std_srvs::Trigger srv;

    while(ros::ok())
    {
        loopRate.sleep();
        client.call(srv);
        std::cout << srv.response.message << std::endl;
    }
}