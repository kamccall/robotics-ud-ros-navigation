#!/bin/sh
xterm -e "cd ~/catkin_ws; source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 5
xterm -e "cd ~/catkin_ws; source devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 5
xterm -e "cd ~/catkin_ws; source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch"
