/**
 * Creates a node that listens for ros_control messages and performs
 * the appropriate action by communicating with the RoboRIO
 */

#include <boost/bind.hpp>
#include <zmq.hpp>

#include "ros/ros.h"
#include "geometry_msgs/Point.h"
#include "sensor_msgs/Joy.h"
#include "sensor_msgs/Imu.h"

#include "roborio_msgs/DifferentialDrive.h"
#include "roborio_msgs/EncoderPair.h"
#include "roborio_msgs/XYTable.h"

#include "roborio/json.hpp"


using json = nlohmann::json;
using namespace roborio_msgs;


//  TODO: move all of these to parameter server
//  Subscribed topics
const std::string DIFFDRIVE_LEAD_TOPIC = "/robot/control/lead_diffdrive";
const std::string DIFFDRIVE_TRAIL_TOPIC = "/robot/control/trail_diffdrive";
const std::string XY_TABLE_TOPIC = "/robot/control/xy_table";

//  Published topics
const std::string JOYSTICK_TOPIC = "/robot/sensors/joystick";
const std::string LEAD_ENCODERS_TOPIC = "/robot/sensors/lead_encoders";
const std::string TRAIL_ENCODERS_TOPIC = "/robot/sensors/trail_encoders";
const std::string XY_TABLE_POSITION_TOPIC = "/robot/sensors/xy_table_position";
const std::string TRAIL_IMU_TOPIC = "/robot/sensors/trail_imu";


void sendDiffDriveLead(const DifferentialDrive::ConstPtr &msg, zmq::socket_t *sock){
    json diffMsg;
    diffMsg["type"] = "diffdrive_lead";
    diffMsg["left"] = msg->left;
    diffMsg["right"] = msg->right;
    const std::string serialized{diffMsg.dump()};
    size_t messageLength = serialized.size();
    zmq::message_t toSend(messageLength);
    memcpy(toSend.data(), serialized.c_str(), messageLength);
    sock->send(toSend);
}

void sendDiffDriveTrail(const DifferentialDrive::ConstPtr &msg, zmq::socket_t *sock){
    json diffMsg;
    diffMsg["type"] = "diffdrive_trail";
    diffMsg["left"] = msg->left;
    diffMsg["right"] = msg->right;
    const std::string serialized{diffMsg.dump()};
    size_t messageLength = serialized.size();
    zmq::message_t toSend(messageLength);
    memcpy(toSend.data(), serialized.c_str(), messageLength);
    sock->send(toSend);
}
void sendXYTable(const XYTable::ConstPtr &msg, zmq::socket_t *sock){
    json tableMsg;
    tableMsg["type"] = "xy_table";
    tableMsg["x"] = msg->x;
    tableMsg["y"] = msg->y;
    const std::string serialized{tableMsg.dump()};
    size_t messageLength = serialized.size();
    zmq::message_t toSend{messageLength};
    memcpy(toSend.data(), serialized.c_str(), messageLength);
    sock->send(toSend);
}


void interpretJoystickMsg(const json &msg, const std::map<std::string, ros::Publisher> &lookup){
//    int id = msg["id"];
    std::vector<float> axes = msg["axes"];
    std::vector<bool> buttons = msg["buttons"];

    sensor_msgs::Joy joystick;
    joystick.header.frame_id = "";
    joystick.header.stamp = ros::Time::now();

    joystick.axes = axes;

    for(const auto &button : buttons)
        joystick.buttons.push_back(button ? 1 : 0);

    lookup.at("joystick").publish(joystick);
}

void interpretEncoderMsg(const json &encoderMsg){}
void interpretXYTableMsg(const json &tableMsg){}
void interpretIMUMsg(const json &imuMsg){}

void interpretJsonMsg(const json &msg, const std::map<std::string, ros::Publisher> &lookup){
    if(msg["type"] == "joystick")
        interpretJoystickMsg(msg, lookup);
}

int main(int argc, char **argv){
    ros::init(argc, argv, "roborio");
    
    ros::NodeHandle handle;

    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_DEALER);
    socket.connect("tcp://10.54.72.2:5002"); //  TODO: Move this to parameter server

    ros::Subscriber diffDriveLeadControl = handle.subscribe<DifferentialDrive>(
            DIFFDRIVE_LEAD_TOPIC,
            2,
            boost::bind(sendDiffDriveLead, _1, &socket)
            );
    ros::Subscriber diffDriveTrailControl = handle.subscribe<DifferentialDrive>(
            DIFFDRIVE_TRAIL_TOPIC,
            2,
            boost::bind(sendDiffDriveTrail, _1, &socket)
            );
    ros::Subscriber xyTableControl = handle.subscribe<XYTable>(
            XY_TABLE_TOPIC,
            1,
            boost::bind(sendXYTable, _1, &socket)
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

    while(ros::ok()){
        zmq::message_t received;
        socket.recv(&received);
        std::string serializedJSON{reinterpret_cast<const char *>(received.data())};
        const json toJSON{serializedJSON};
        interpretJsonMsg(toJSON, publisherLookup);
    }
}