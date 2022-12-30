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
git clone https://github.com/turtlebot/turtlebot
git clone https://github.com/turtlebot/turtlebot_interactions
git clone https://github.com/turtlebot/turtlebot_simulator
git clone https://github.com/kamccall/robotics-ud-ros-navigation
cd ~/catkin_ws/
source devel/setup.bash
rosdep -i install gmapping
rosdep -i install turtlebot_teleop
rosdep -i install turtlebot_rviz_launchers
rosdep -i install turtlebot_gazebo
catkin_make
source devel/setup.bash
cd ~/catkin_ws/src
mkdir map
mkdir scripts
mkdir rvizConfig
mkdir world
mkdir pick_objects
mkdir add_markers
cp -r robotics-ud-ros-navigation/pick_objects/* pick_objects
cp -r robotics-ud-ros-navigation/add_markers/* add_markers
cp robotics-ud-ros-navigation/world/enso_condo_building_simplified_bots.world world
cp robotics-ud-ros-navigation/map/enso.* map
cp robotics-ud-ros-navigation/scripts/*.sh scripts
cp -f robotics-ud-ros-navigation/launch/amcl_demo.launch turtlebot_simulator/turtlebot_gazebo/launch
cd ~/catkin_ws
git config --global user.name kamccall
git config --global user.email kevin@kevinmccall.net
#need to run these AFTER setting up env (so that catkin_make works)
cd ~/catkin_ws/src/robotics-ud-ros-navigation
rm -rf pick_objects
rm -rf add_markers
cd ~/catkin_ws
catkin_make
