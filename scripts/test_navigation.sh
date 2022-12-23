#!/bin/sh
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch" &
#xterm -e "export ROBOT_INITIAL_POSE='-x 3 -y -8'; export TURTLEBOT_GAZEBO_WORLD_FILE="~/catkin_ws/src/world/enso_condo_building_simplified_bots.world"; roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 5
xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch" &
#xterm -e "export TURTLEBOT_GAZEBO_MAP_FILE="~/catkin_ws/src/robotics-ud-ros-mapping/my_robot/maps/map.yaml"; roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 5
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch"
