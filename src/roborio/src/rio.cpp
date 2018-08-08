/**
 * Creates a node that listens for ros_control messages and performs
 * the appropriate action by communicating with the RoboRIO
 */

#include <boost/bind.hpp>
#include <google/protobuf/any.pb.h>
#include <zmq.hpp>

#include "ros/ros.h"
#include "ros/console.h"
#include "geometry_msgs/Point.h"
#include "sensor_msgs/Joy.h"
#include "sensor_msgs/Imu.h"

#include "roborio_msgs/DifferentialDrive.h"
#include "roborio_msgs/EncoderPair.h"
#include "roborio_msgs/XYTable.h"

#include "roborio/senders.h"
#include "roborio/receivers.h"

using namespace roborio_msgs;


int main(int argc, char **argv) {
    ros::init(argc, argv, "roborio");

    ros::NodeHandle handle;

    const std::string ROBORIO_IP;
    const std::string DIFFDRIVE_LEAD_TOPIC;
    const std::string DIFFDRIVE_TRAIL_TOPIC;
    const std::string XY_TABLE_TOPIC;
    const std::string JOYSTICK_TOPIC;
    const std::string LEAD_ENCODERS_TOPIC;
    const std::string TRAIL_ENCODERS_TOPIC;
    const std::string XY_TABLE_POSITION_TOPIC;
    const std::string TRAIL_IMU_TOPIC;

    handle.param("/robot/params/roborio_ip", ROBORIO_IP);
    handle.param("/robot/params/lead_diffdrive", DIFFDRIVE_LEAD_TOPIC);
    handle.param("/robot/params/trail_diffdrive", DIFFDRIVE_TRAIL_TOPIC);
    handle.param("/robot/params/xy_table", XY_TABLE_TOPIC);
    handle.param("/robot/params/joystick", JOYSTICK_TOPIC);
    handle.param("/robot/params/lead_encoders", LEAD_ENCODERS_TOPIC);
    handle.param("/robot/params/trail_encoders", TRAIL_ENCODERS_TOPIC);
    handle.param("/robot/params/xy_table_position", XY_TABLE_POSITION_TOPIC);
    handle.param("/robot/params/trail_imu", TRAIL_IMU_TOPIC);


    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_DEALER);
    socket.connect(ROBORIO_IP);

    ros::Subscriber diffDriveLeadControl = handle.subscribe<DifferentialDrive>(
            DIFFDRIVE_LEAD_TOPIC,
            2,
            boost::bind(senders::sendDiffDriveLead, _1, &socket)
    );
    ros::Subscriber diffDriveTrailControl = handle.subscribe<DifferentialDrive>(
            DIFFDRIVE_TRAIL_TOPIC,
            2,
            boost::bind(senders::sendDiffDriveTrail, _1, &socket)
    );
    ros::Subscriber xyTableControl = handle.subscribe<XYTable>(
            XY_TABLE_TOPIC,
            1,
            boost::bind(senders::sendXYTable, _1, &socket)
    );

    ros::Publisher joystickPublisher = handle.advertise<sensor_msgs::Joy>(
            JOYSTICK_TOPIC,
            5
    );
    ros::Publisher leadEncoderPublisher = handle.advertise<EncoderPair>(
            LEAD_ENCODERS_TOPIC,
            5
    );
    ros::Publisher trailEncoderPublisher = handle.advertise<EncoderPair>(
            TRAIL_ENCODERS_TOPIC,
            5
    );
    ros::Publisher xyTablePositionPublisher = handle.advertise<geometry_msgs::Point>(
            XY_TABLE_POSITION_TOPIC,
            5
    );
    ros::Publisher trailIMUPublisher = handle.advertise<sensor_msgs::Imu>(
            TRAIL_IMU_TOPIC,
            5
    );

    std::map<std::string, ros::Publisher> publisherLookup;
    publisherLookup.insert(std::make_pair(
            "joystick",
            joystickPublisher
    ));

    publisherLookup.insert(std::make_pair(
            "lead_encoder",
            leadEncoderPublisher
    ));

    publisherLookup.insert(std::make_pair(
            "trail_encoder",
            trailEncoderPublisher
    ));

    publisherLookup.insert(std::make_pair(
            "xy_position",
            xyTablePositionPublisher
    ));

    publisherLookup.insert(std::make_pair(
            "trail_imu",
            trailIMUPublisher
    ));

    while (ros::ok()) {
        ros::spinOnce();
//        zmq::message_t received;
//        socket.recv(&received);
//        std::string serializedJSON{reinterpret_cast<const char *>(received.data())};
//        const json toJSON{serializedJSON};
//        interpretJsonMsg(toJSON, publisherLookup);
    }
}