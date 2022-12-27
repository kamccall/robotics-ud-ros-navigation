#!/bin/sh
xterm -e "cd ~/catkin_ws; source devel/setup.bash; export ROBOT_INITIAL_POSE='-x 2.8 -y -8.3 -Y 1.57'; export TURTLEBOT_GAZEBO_WORLD_FILE="~/catkin_ws/src/world/enso_condo_building_simplified_bots.world"; roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 5
xterm -e "cd ~/catkin_ws; source devel/setup.bash; export TURTLEBOT_GAZEBO_MAP_FILE="~/catkin_ws/src/map/enso.yaml"; roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 5
xterm -e "cd ~/catkin_ws; source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch"
