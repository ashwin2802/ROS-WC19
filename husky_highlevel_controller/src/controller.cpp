#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Twist.h>
#include <husky_highlevel_controller/Control.h>
#include <std_srvs/SetBool.h>

double e_prev = 0, e = -1, v = 0, kp = 1, kd = 1;
bool publish = true; double max_stop_dist;

void distCallback(const std_msgs::Float64& msg)
{
    e = msg.data;
    v = kp*e + kd*(e - e_prev);
    e_prev = e;
}

bool serverCallback(std_srvs::SetBool::Request& req, std_srvs::SetBool::Response &rep)
{
    publish = req.data;
    rep.success = true;
    return true;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "controller");
    ros::NodeHandle nh;

    nh.getParam("kP", kp);
    nh.getParam("kD", kd);
    nh.getParam("max_dist", max_stop_dist);

    ros::Subscriber distSub = nh.subscribe("min_dist", 10, distCallback);
    ros::Publisher velPub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    ros::Publisher feedPub = nh.advertise<husky_highlevel_controller::Control>("/feedback", 10);

    ros::ServiceServer server = nh.advertiseService("/state", serverCallback);
    ros::ServiceClient client = nh.serviceClient<std_srvs::SetBool>("/state");

    ros::Rate loopRate(30);
    std_srvs::SetBool srv; srv.request.data = false;
    
    while(ros::ok())
    {
        if(e == -1) { while(e == -1) ros::spinOnce();}
        ros::spinOnce();
        geometry_msgs::Twist vel_msg;
        husky_highlevel_controller::Control msg;
        msg.header.stamp = ros::Time::now();
        msg.error = e;
        msg.vel_x = v;
        vel_msg.linear.x = v;
        if(publish) velPub.publish(vel_msg);
        if(e < max_stop_dist && v > 0) client.call(srv);
        feedPub.publish(msg);
        loopRate.sleep();
    }

    return 0;
}
