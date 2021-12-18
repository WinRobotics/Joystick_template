#include "ros/ros.h"
#include "std_msgs/String.h"

#include "geometry_msgs/Twist.h"
#include "sensor_msgs/Joy.h"
#include <sstream>

//link to OOP C++  https://roboticsbackend.com/oop-with-ros-in-cpp/

class controller{

public:

   controller(ros::NodeHandle *nh);
   ~controller();
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
  void sendCmdVelMsg(const sensor_msgs::Joy::ConstPtr& joy_msg);

private:
//Declaration of all publisher and Subscriber 
ros::Subscriber joy_sub;
ros::Publisher cmd_vel_pub;

};



controller::controller(ros::NodeHandle *nh)
{
  //Assigning publisher and subsriber to std message types, declaring callbacks 
  //controller_pub = nh.advertise<std_msgs::String>("chatter", 1000);
  cmd_vel_pub = nh->advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  joy_sub = nh->subscribe("joy",1000,&controller::joyCallback,this);


}

controller::~controller()
{

}


void controller::joyCallback (const sensor_msgs::Joy::ConstPtr& msg)
{

  geometry_msgs::Twist cmd_vel_msg;
  cmd_vel_msg.linear.x = msg->axes[4];
  cmd_vel_pub.publish(cmd_vel_msg);

}








int main(int argc, char **argv)
{

    ros::init(argc, argv, "controller");
    ros::NodeHandle nh;
    controller controller_base = controller(&nh);

  while (true)
  {

    ros::spinOnce();
  }


  return 0;
}
