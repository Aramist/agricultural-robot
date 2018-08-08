//
// Created by aramist on 8/8/18.
//

#include "roborio/senders.h"


using namespace roborio_msgs;

namespace senders {
    void sendDiffDriveLead(const DifferentialDrive::ConstPtr &msg, zmq::socket_t *sock) {
        proto::DifferentialDrive message;
        message.set_left(msg->left);
        message.set_right(msg->right);
        const std::string frame{"lead"};
        message.set_name(frame);

        std::string contents;
        message.SerializeToString(&contents);

        zmq::message_t socketMessage(contents.size());
        memcpy(socketMessage.data(), contents.c_str(), sizeof(contents.c_str()));
        sock->send(socketMessage);
    }

    void sendDiffDriveTrail(const DifferentialDrive::ConstPtr &msg, zmq::socket_t *sock) {
        proto::DifferentialDrive message;
        message.set_left(msg->left);
        message.set_right(msg->right);
        const std::string frame{"trail"};
        message.set_name(frame);

        std::string contents;
        message.SerializeToString(&contents);

        zmq::message_t socketMessage(contents.size());
        memcpy(socketMessage.data(), contents.c_str(), sizeof(contents.c_str()));
        sock->send(socketMessage);
    }

    void sendXYTable(const XYTable::ConstPtr &msg, zmq::socket_t *sock) {
        proto::XYTable message;
        message.set_x(msg->x);
        message.set_y(msg->y);

        std::string contents;
        message.SerializeToString(&contents);

        zmq::message_t socketMessage(contents.size());
        memcpy(socketMessage.data(), contents.c_str(), sizeof(contents.c_str()));
        sock->send(socketMessage);
    }
}

