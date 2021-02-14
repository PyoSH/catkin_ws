cmake_minimum_required(VERSION 3.0.2)
project(control_00)

find_package(catkin REQUIRED COMPONENTS
  genmsg
  roscpp
  std_msgs
  geometry_msgs
  sensor_msgs
)

# <declare ROS messages and services>
#add_messeage_files(	FILES
#			Laserscan.msg
#			cmd_vel.msg
#			Num.msg
#)


# <generate added messages and services>
#generate_messages(
#  DEPENDENCIES
#  std_msgs
#  geometry_msgs
#  sensor_msgs
#)


# <declare a catkin package>
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${control_00}
  CATKIN_DEPENDS roscpp std_msgs geometry_msgs sensor_msgs
  DEPENDS system_lib
)


# <build node>
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(control_node_00 src/control_node_00.cpp)

target_link_libraries(control_node_00 ${catkin_LIBRARIES})
#add_dependencies(control_node_00 control_00_generate_messages_cpp)
