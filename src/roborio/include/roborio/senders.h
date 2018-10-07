//
// Created by aramist on 8/8/18.
//

#ifndef ROBORIO_SENDERS_H
#define ROBORIO_SENDERS_H

//#include <zmq.hpp>

#include "roborio/json.hpp"

#include "roborio_msgs/DifferentialDrive.h"
#include "roborio_msgs/XYTable.h"

namespace senders {
    nlohmann::json sendDiffDriveLead(const roborio_msgs::DifferentialDrive::ConstPtr &msg, zmq::socket_t *sock);

    nlohmann::json sendDiffDriveTrail(const roborio_msgs::DifferentialDrive::ConstPtr &msg, zmq::socket_t *sock);

    nlohmann::json sendXYTable(const roborio_msgs::XYTable::ConstPtr &msg, zmq::socket_t *sock);
}

#endif //ROBORIO_SENDERS_H
