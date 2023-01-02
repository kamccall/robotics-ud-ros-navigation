#!/bin/sh
cd ../..
xterm -e "source devel/setup.bash; export ROBOT_INITIAL_POSE='-x -0.5 -y -8.3 -Y 1.57'; export TURTLEBOT_GAZEBO_WORLD_FILE="$(pwd)/src/world/enso_condo_building_simplified_bots.world"; roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 5
xterm -e "devel/setup.bash; export TURTLEBOT_GAZEBO_MAP_FILE="$(pwd)/src/map/enso.yaml"; roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 5
xterm -e "source devel/setup.bash; rosrun rviz rviz -d "$(pwd)/src/rvizConfig/home_service_rviz_markers.rviz"" &
sleep 5
xterm -e "source devel/setup.bash; rosrun add_markers add_markers _param:=mark_from_odom" &
sleep 5
xterm -e "source devel/setup.bash; rosrun pick_objects pick_objects"
