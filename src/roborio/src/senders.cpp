//
// Created by aramist on 8/8/18.
//

#include <networktables/NetworkTableEntry.h>
#include "roborio/senders.h"
#include "roborio/json.hpp"


using namespace roborio_msgs;
using namespace nlohmann;

namespace senders {
    void sendDiffDriveLead(const DifferentialDrive::ConstPtr &msg, nt::NetworkTableEntry& entry) {
//        json message;
//        message["left"] = msg->left;
//        message["right"] = msg->right;
//        message["name"] = "lead_drive";
//
//        std::string contents = message.dump();
//
//        zmq::message_t socketMessage(contents.size());
//        memcpy(socketMessage.data(), contents.c_str(), sizeof(contents.c_str()));
//        sock->send(socketMessage);

//        return message;

        nt::ArrayRef<double> values{msg->left, msg->right};
        entry.SetDoubleArray(values);
    }


    void sendDiffDriveTrail(const DifferentialDrive::ConstPtr &msg, nt::NetworkTableEntry& entry) {
//        json message;
//
//        message["left"] = msg->left;
//        message["right"] = msg->right;
//        message["name"] = "trail_drive";
//
//        std::string contents = message.dump();
//
//        zmq::message_t socketMessage(contents.size());
//        memcpy(socketMessage.data(), contents.c_str(), sizeof(contents.c_str()));
//        sock->send(socketMessage);

//        return message;

        nt::ArrayRef<double> values{msg->left, msg->right};
        entry.SetDoubleArray(values);
    }

    void sendXYTable(const XYTable::ConstPtr &msg, nt::NetworkTableEntry& entry) {
//        json message;
//
//        message["name"] = "table";
//        message["x"] = msg->x;
//        message["y"] = msg->y;
//
//        std::string contents = message.dump();
//
//        zmq::message_t socketMessage(contents.size());
//        memcpy(socketMessage.data(), contents.c_str(), sizeof(contents.c_str()));
//        sock->send(socketMessage);

//        return message;
    }
}

