//
// Created by aramist on 8/8/18.
//

#ifndef ROBORIO_RECEIVERS_H
#define ROBORIO_RECEIVERS_H

#include <string>

#include "ros/ros.h"

#include "sensor_msgs/Joy.h"

#include "google/protobuf/any.pb.h"
#include "roborio_msgs/robot_msgs.pb.h"

#include "roborio_msgs/EncoderPair.h"
#include "roborio_msgs/XYTable.h"

namespace receivers {
    void interpretJoystickMsg(const proto::Joy &msg, const std::map<std::string, ros::Publisher> &lookup);

    void interpretEncoderMsg(const proto::EncoderPair &encoderMsg);

    void interpretXYTableMsg(const proto::XYTable &tableMsg);

    void interpretIMUMsg(const proto::IMU &imuMsg);

    void interpretIncomingMsg(const google::protobuf::Any &msg, const std::map<std::string, ros::Publisher> &lookup);
}

#endif //ROBORIO_RECEIVERS_H
