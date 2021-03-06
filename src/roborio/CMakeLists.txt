cmake_minimum_required(VERSION 2.8.3)
project(roborio)

add_compile_options(-std=c++11)

find_package(
        catkin REQUIRED COMPONENTS
        roscpp
        sensor_msgs
        roborio_msgs
)

find_package(
        PkgConfig
)

pkg_check_modules(PC_ZeroMQ QUIET zmq)

find_path(
        zmq_INCLUDE_DIRS
        NAMES zmq.hpp
        PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
)

find_library(
        zmq_LIBRARY
        NAMES zmq
        PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
)

catkin_package(
        INCLUDE_DIRS include
        LIBRARIES ${PROJECT_NAME}
        CATKIN_DEPENDS roscpp
        DEPENDS zmq
)

include_directories(
        include
        ${catkin_INCLUDE_DIRS}
        ${zmq_INCLUDE_DIRS}
)

add_executable(
    rio src/rio.cpp
)

target_link_libraries(
    rio ${catkin_LIBRARIES} ${zmq_LIBRARY}
)