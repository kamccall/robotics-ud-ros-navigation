# robotics-ud-ros-navigation
udacity robotics project5 using slam to map and localize robot inside custom gazebo building

## phase 1 efforts
i have been able to configure all the software and successfully execute `test_slam_turtlebot.sh` and `test_navigation_turtelbot.sh` with my custom `gazebo` world and a custom generated `map` using the `gmapping` utility that used that custom world as input.  i translated and rotated the location of the turtlebot based on the (well documented) 90 degree difference between the `gazebo` map and the `gmapping` generated `map.pgm` file.  when doing the manual 2D navigation in `rviz` everything works fine in that world. 

however, when i try to use the same (starting) coordinates in the `pick_objects` node, and then define the first goal location as three clicks west of there - in a completely open, unobstructed area in both the `map` and the `world` files - it continually fails to find a valid path, and ends up Aborting the attempt.  

![image](https://user-images.githubusercontent.com/19736497/209744428-c8ae37a0-9f80-4748-b79b-12af90ebdc2b.png)

