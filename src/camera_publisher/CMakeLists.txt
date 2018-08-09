cmake_minimum_required(VERSION 2.8.3)
project(camera_publisher)

add_compile_options(-std=c++11)

find_package(
        catkin REQUIRED COMPONENTS
        usb_cam
)

catkin_package(
        CATKIN_DEPENDS usb_cam
)
