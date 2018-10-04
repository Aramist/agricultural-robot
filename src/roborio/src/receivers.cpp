//
// Created by aramist on 8/8/18.
//

#include "roborio/receivers.h"


using json = nlohmann::json;

namespace receivers {
    void interpretJoystickMsg(const json &msg, const std::map<std::string, ros::Publisher> &lookup) {
        sensor_msgs::Joy joystick;
        joystick.header.frame_id = "";
        joystick.header.stamp = ros::Time::now();

        for (const auto &axis : msg["axes"])
            joystick.axes.push_back(axis);

        for (const auto &button : msg["buttons"])
            joystick.buttons.push_back(button);

        lookup.at("joystick").publish(joystick);
    }

    void interpretEncoderMsg(const json &encoderMsg,
                             const std::map<std::string, ros::Publisher> &lookup) {
        roborio_msgs::EncoderPair pair;
        pair.left = encoderMsg["left"];
        pair.right = encoderMsg["right"];
        const std::string frame = encoderMsg["name"];
        const std::string front("lead");
        if (frame == front)
            lookup.at("lead_encoder").publish(pair);
        else
            lookup.at("trail_encoder").publish(pair);
    }

    void interpretXYTableMsg(const json &tableMsg,
                             const std::map<std::string, ros::Publisher> &lookup) {
        roborio_msgs::XYTable table;
        table.x = tableMsg["x"];
        table.y = tableMsg["y"];
        lookup.at("xy_position").publish(table);
    }

    void interpretIMUMsg(const json &imuMsg,
                         const std::map<std::string, ros::Publisher> &lookup) {
        sensor_msgs::Imu imu;

        imu.header.frame_id = "";
        imu.header.stamp = ros::Time::now();

        imu.orientation_covariance[0] = -1;
        imu.angular_velocity_covariance[0] = -1;
        imu.linear_acceleration_covariance[0] = -1;
        imu.angular_velocity.x = imuMsg["gyro_x"];
        imu.angular_velocity.y = imuMsg["gyro_y"];
        imu.angular_velocity.z = imuMsg["gyro_z"];
        imu.linear_acceleration.x = imuMsg["accel_x"];
        imu.linear_acceleration.y = imuMsg["accel_y"];
        imu.linear_acceleration.z = imuMsg["accel_z"];
        lookup.at("trail_imu").publish(imu);
    }

    void interpretIncomingMsg(const json &msg, const std::map<std::string, ros::Publisher> &lookup) {
        if (msg["name"] == "trail_imu") {
            interpretIMUMsg(msg, lookup);
        }
    }
}
