//
// Created by aramist on 8/8/18.
//

#include "roborio/receivers.h"


namespace receivers {
    void interpretJoystickMsg(const proto::Joy &msg, const std::map<std::string, ros::Publisher> &lookup) {
        sensor_msgs::Joy joystick;
        joystick.header.frame_id = "";
        joystick.header.stamp = ros::Time::now();

        for (const auto &axis : msg.axes())
            joystick.axes.push_back(axis);

        for (const auto &button : msg.buttons())
            joystick.buttons.push_back(button);

        lookup.at("joystick").publish(joystick);
    }

    void interpretEncoderMsg(const proto::EncoderPair &encoderMsg) {}

    void interpretXYTableMsg(const proto::XYTable &tableMsg) {}

    void interpretIMUMsg(const proto::IMU &imuMsg) {}

    void interpretIncomingMsg(const google::protobuf::Any &msg, const std::map<std::string, ros::Publisher> &lookup) {}
}
