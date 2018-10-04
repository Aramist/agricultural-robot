cmake_minimum_required(VERSION 2.8.3)
project(roborio_msgs)

include(FindProtobuf)

find_package(catkin REQUIRED COMPONENTS
        message_generation
        message_runtime
        std_msgs
)

find_package(Protobuf REQUIRED)

add_message_files(
        FILES
        DifferentialDrive.msg
        EncoderPair.msg
        XYTable.msg
)

generate_messages(
        DEPENDENCIES
        std_msgs
)

catkin_package(
        CATKIN_DEPENDS message_runtime message_generation std_msgs
        INCLUDE_DIRS include
)
