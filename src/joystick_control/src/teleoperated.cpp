//
// Created by aramist on 9/8/18.
//

#include <string>

#include <boost/bind.hpp>
#include "ros/ros.h"
#include "sensor_msgs/Joy.h"

#include "roborio_msgs/DifferentialDrive.h"


void joystickDrive(const sensor_msgs::Joy::ConstPtr &joystick,
                   const ros::Publisher &leadPub,
                   const ros::Publisher &trailPub) {
    double t = joystick->axes[3];
    double y = joystick->axes[1];

    double left = y + t;
    double right = y - t;

    double trail = y - abs(t) * 0.5;

    roborio_msgs::DifferentialDrive leading;
    leading.left = left;
    leading.right = right;

    roborio_msgs::DifferentialDrive trailing;
    trailing.left = trail;
    trailing.right = trail;

    leadPub.publish(leading);
    trailPub.publish(trailing);
}


int main(int argc, char **argv) {
    ros::init(argc, argv, "joystick_control");
    ros::NodeHandle handle;

    std::string joystickTopic;
    std::string leadDriveTopic;
    std::string trailDriveTopic;

    handle.getParam("/robot/params/joystick", joystickTopic);
    handle.getParam("/robot/params/lead_diffdrive", leadDriveTopic);
    handle.getParam("/robot/params/trail_diffdrive", trailDriveTopic);

    ros::Publisher leading = handle.advertise<roborio_msgs::DifferentialDrive>(
            leadDriveTopic,
            1
    );

    ros::Publisher trailing = handle.advertise<roborio_msgs::DifferentialDrive>(
            trailDriveTopic,
            1
    );

    ros::Subscriber joySubscriber = handle.subscribe<sensor_msgs::Joy>(
            joystickTopic,
            5,
            boost::bind(joystickDrive, _1, leading, trailing));

    ros::spin();
}