cmake_minimum_required(VERSION 2.8.3)
project(joystick_control)

add_compile_options(-std=c++11)

find_package(
        catkin REQUIRED COMPONENTS
        roscpp
        sensor_msgs
        roborio_msgs
)

catkin_package(
        CATKIN_DEPENDS roscpp sensor_msgs roborio_msgs
)

include_directories(
        ${catkin_INCLUDE_DIRS}
)

add_executable(
        teleop src/teleoperated.cpp
)

target_link_libraries(
        teleop ${catkin_LIBRARIES}
)
