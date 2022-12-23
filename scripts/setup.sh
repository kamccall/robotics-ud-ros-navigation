#!/bin/sh
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/src
catkin_init_workspace
cd ..
catkin_make
sudo apt-get update
sudo apt-get upgrade
cd ~/catkin_ws/src
git clone https://github.com/ros-perception/slam_gmapping
#git clone https://github.com/turtlebot/turtlebot
#git clone https://github.com/turtlebot/turtlebot_interactions
#git clone https://github.com/turtlebot/turtlebot_simulator
git clone https://github.com/kamccall/robotics-ud-ros-mapping
git clone https://github.com/kamccall/robotics-ud-ros-navigation
cd robotics-ud-ros-mapping
git clone https://github.com/ros-teleop/teleop_twist_keyboard
cd ~/catkin_ws/
source devel/setup.bash
rosdep -i install gmapping
#rosdep -i install turtlebot_teleop
#rosdep -i install turtlebot_rviz_launchers
#rosdep -i install turtlebot_gazebo
catkin_make
source devel/setup.bash
cd ~/catkin_ws/src
mkdir map
mkdir scripts
mkdir rvizConfig
mkdir pick_objects
mkdir add_markers
mkdir world
cp robotics-ud-ros-mapping/my_robot/worlds/enso_condo_building_simplified_bots.world world
cd robotics-ud-ros-navigation
git config --global user.name kamccall
git config --global user.email kevin@kevinmccall.net
