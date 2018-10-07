//
// Created by aramist on 8/8/18.
//

#ifndef ROBORIO_RECEIVERS_H
#define ROBORIO_RECEIVERS_H

#include <string>

#include "ros/ros.h"

#include "sensor_msgs/Imu.h"
#include "sensor_msgs/Joy.h"

#include "roborio/json.hpp"

#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableEntry.h>

#include "roborio_msgs/EncoderPair.h"
#include "roborio_msgs/XYTable.h"

namespace receivers {
    void interpretJoystickMsg(const std::shared_ptr<nt::NetworkTable> table, const std::map<std::string, ros::Publisher> &lookup);

    void interpretEncoderMsg(const nlohmann::json &encoderMsg, const std::map<std::string, ros::Publisher> &lookup);

    void interpretXYTableMsg(const nlohmann::json &tableMsg, const std::map<std::string, ros::Publisher> &lookup);

    void interpretIMUMsg(const nlohmann::json &imuMsg, const std::map<std::string, ros::Publisher> &lookup);

    void interpretIncomingMsg(const nlohmann::json &msg, const std::map<std::string, ros::Publisher> &lookup);
}

#endif //ROBORIO_RECEIVERS_H
