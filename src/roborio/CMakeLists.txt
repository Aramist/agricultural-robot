cmake_minimum_required(VERSION 2.8.3)
project(roborio)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED)
catkin_package()

include_directories(
    include
    ${catkin_INCLUDE_DIRS}
)

add_executable(
    rio src/rio.cpp
)

target_link_libraries(
    rio ${catkin_LIBRARIES}
)