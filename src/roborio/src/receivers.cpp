//
// Created by aramist on 8/8/18.
//

#include "roborio/receivers.h"


using namespace google::protobuf;

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

    void interpretEncoderMsg(const proto::EncoderPair &encoderMsg,
                             const std::map<std::string, ros::Publisher> &lookup) {
        roborio_msgs::EncoderPair pair;
        pair.left = encoderMsg.left();
        pair.right = encoderMsg.right();
        const std::string frame = encoderMsg.name();
        const std::string front("lead");
        if (frame == front)
            lookup.at("lead_encoder").publish(pair);
        else
            lookup.at("trail_encoder").publish(pair);
    }

    void interpretXYTableMsg(const proto::XYTable &tableMsg,
                             const std::map<std::string, ros::Publisher> &lookup) {
        roborio_msgs::XYTable table;
        table.x = tableMsg.x();
        table.y = tableMsg.y();
        lookup.at("xy_position").publish(table);
    }

    void interpretIMUMsg(const proto::IMU &imuMsg,
                         const std::map<std::string, ros::Publisher> &lookup) {
        sensor_msgs::Imu imu;

        imu.header.frame_id = "";
        imu.header.stamp = ros::Time::now();

        imu.orientation_covariance[0] = -1;
        imu.angular_velocity_covariance[0] = -1;
        imu.linear_acceleration_covariance[0] = -1;
        imu.angular_velocity.x = imuMsg.rawgyrox();
        imu.angular_velocity.y = imuMsg.rawgyroy();
        imu.angular_velocity.z = imuMsg.rawgyroz();
        imu.linear_acceleration.x = imuMsg.rawaccelx();
        imu.linear_acceleration.y = imuMsg.rawaccely();
        imu.linear_acceleration.z = imuMsg.rawaccelz();
        lookup.at("trail_imu").publish(imu);
    }

    void interpretIncomingMsg(std::shared_ptr<Any> msg, const std::map<std::string, ros::Publisher> &lookup) {
        ROS_WARN("Interpreting");
        if (msg->Is<proto::Joy>()) {
            ROS_WARN("Joystick");
            proto::Joy joyMsg;
            msg->UnpackTo(&joyMsg);
            interpretJoystickMsg(joyMsg, lookup);
        } else if (msg->Is<proto::EncoderPair>()) {
            ROS_WARN("encoder");
            proto::EncoderPair encMsg;
            msg->UnpackTo(&encMsg);
            interpretEncoderMsg(encMsg, lookup);
        } else if (msg->Is<proto::XYTable>()) {
            ROS_WARN("xy");
            proto::XYTable tableMsg;
            msg->UnpackTo(&tableMsg);
            interpretXYTableMsg(tableMsg, lookup);
//        } else if (msg->Is<proto::IMU>()) {
        } else {
            ROS_WARN("IMU");
            proto::IMU imuMsg;
            msg->UnpackTo(&imuMsg);
            interpretIMUMsg(imuMsg, lookup);
        }
    }
}
