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
        #DEPENDS Protobuf
        LIBRARIES robot_protos
)

include_directories(
        include
        ${catkin_INCLUDE_DIRS}
        ${Protobuf_INCLUDE_DIRS}
)

add_library(
        robot_protos src/robot_msgs.pb.cc
)

target_link_libraries(robot_protos ${catkin_LIBRARIES} ${Protobuf_LIBRARIES})

install(TARGETS robot_protos
        ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})

install(DIRECTORY include/${PROJECT_NAME}/
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
        FILES_MATCHING PATTERN "*.h"
        PATTERN ".svn" EXCLUDE)