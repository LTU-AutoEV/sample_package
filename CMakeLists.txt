cmake_minimum_required(VERSION 2.8.3)

## This must match the package name
project(sample_package)

## Add support for C++11, supported in ROS Kinetic and newer
add_definitions(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  std_msgs

  # For Camera Example
  cv_bridge
  image_transport
)

## catkin specific configuration
catkin_package()

# Header files
include_directories(${catkin_INCLUDE_DIRS})

####################
## Your ROS Nodes ##
####################

# Tell ROS that you have a cpp program you want it to compile
# Use the following format:
#    add_executable(FILENAME src/FILENAME.cpp)
add_executable(my_node_sample src/my_node_sample.cpp)

# Link ROS libs
# Use the following format:
#    target_link_libraries(FILENAME ${catkin_LIBRARIES})
target_link_libraries(my_node_sample ${catkin_LIBRARIES})

