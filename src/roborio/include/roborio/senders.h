//
// Created by aramist on 8/8/18.
//

#ifndef ROBORIO_SENDERS_H
#define ROBORIO_SENDERS_H

//#include <zmq.hpp>

#include <networktables/NetworkTableEntry.h>

#include "roborio_msgs/DifferentialDrive.h"
#include "roborio_msgs/XYTable.h"

namespace senders {
    void sendDiffDriveLead(const roborio_msgs::DifferentialDrive::ConstPtr&, nt::NetworkTableEntry&);

    void sendDiffDriveTrail(const roborio_msgs::DifferentialDrive::ConstPtr&, nt::NetworkTableEntry&);

    void sendXYTable(const roborio_msgs::XYTable::ConstPtr&, nt::NetworkTableEntry&);
}

#endif //ROBORIO_SENDERS_H
