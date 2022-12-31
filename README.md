# robotics-ud-ros-navigation
udacity robotics project5 to define a home service robot that uses various packages such as `AMCL` and `gmapping`, visualized representations of a custom world in `gazebo` and its generated map in `rviz`, and custom `ROS` packages called `pick_objects` and `add_markers` in order to create an autonomou robot that navigates a condo environment in a manner similar to a roomba or similar home device. 

## part 0: setup files
while i completed most of the deliverables in this project using the `turtlebot` included with `ROS`, i reproduced similar behaviors for most of the challenges using my own custom robot that was created in prior assignments.  since the packages and supporting code are very different, both `setup_myrobot.sh` and `setup_turtlebot.sh` scripts are included in the repo.  after doing both SLAM and navigation tests using my custom robot, all of the assignments were then done using the `turtlebot`, so the `setup_turtlebot.sh` was the script most often used. 

## part 1: test SLAM
this focused on launching the `turtlebot` included with `gazebo` inside the default turtlebot world and visualizing it both within `gazebo` as well as within `rviz`.  this comes together in the `test_slam_turtlebot.sh` shell script which runs `turtlebot_launch.launch`, `gmapping_demo.launch`, and `view_navigation.launch` to observe the output in `rviz`, and `keyboard_teleop.launch` in order to manually navigate the robot through the `gazebo` world as well as the map simultaneously.  

below is an image of the `turtlebot` running in that environment after executing the `test_slam_turtlebot.sh` script. 

![image](https://user-images.githubusercontent.com/19736497/210157423-c38c8d02-35b3-4d96-bbe9-bc287c67ed91.png)![image](https://user-images.githubusercontent.com/19736497/210157605-cefbf39a-8c90-454b-9d43-fa680b3673e2.png)

## part 2: test localization and navigation
this task focused on moving to multiple locations within the map, demonstrating the ability of the robot to reach the location(s) and orient itself inside the map. this uses the `AMCL` package, and simultaneously shows moving within my custom `gazebo` world as well as the custom map as displayed in `rviz`.  destination locations for robot are provided manually using the 2D navigation button within `rviz`. i created two versions of this script to show the turtleboth in different worlds, but the output below is from `test_navigation_enso_world.sh` script which launches all the services, include the `turtlebot_world.launch`, `amcl_demo.launch` and `view_navigation.launch` files and shows the `turtlebot` runnning within my custom `gazebo` world and the corresponding `rviz` map generated from the `gmapping` utility. 

below are images of the `turtlebot` running in that environment after executing the `test_navigation_enso_world.sh` script and manually defining successive target locations using 2d navigation within `rviz`. 

![image](https://user-images.githubusercontent.com/19736497/210157539-512741a2-8929-4fc5-9561-ebb7a7a692e4.png)![image](https://user-images.githubusercontent.com/19736497/210157635-d94168ae-7664-4078-acc1-e269b9f3a3c6.png)
![image](https://user-images.githubusercontent.com/19736497/210157566-1b95a6c5-cc8b-4e75-8b78-f000a335ed25.png)![image](https://user-images.githubusercontent.com/19736497/210157638-5be6dda4-616c-4f82-b543-b2479184adc2.png)
![image](https://user-images.githubusercontent.com/19736497/210157575-956f60a1-5eb1-4e67-ba6d-4bb5ac080806.png)![image](https://user-images.githubusercontent.com/19736497/210157645-7a43e338-8f2d-4744-b4dc-da6212c8ceff.png)
![image](https://user-images.githubusercontent.com/19736497/210157583-ecda317e-662c-45d7-82a7-1365c600406e.png)![image](https://user-images.githubusercontent.com/19736497/210157648-13533e40-4ddb-46b6-b9e6-bfbcbc5ee19c.png)

## part 3: auto-pilot navigation to waypoint(s) and destination
this focused on defining a list of locations to which the robot would autonomously navigate, and then observing the robot's successful movement to each of them in turn within the `pick_objects` custom `ROS` node.  this leveraged similar `turtlebot`, `AMCL` and `rviz` services, but also required creating a custom `ROS` node that used `MoveBaseClient` object and a `MoveBaseAction` message from the `move_base_msgs` library in order to define a target location and orientation for the robot and then observe the robot's autonomous movement.  this also requires a logical rotation in the coordinate systems of `gazebo` and the resulting map, given the (well documented) 90 degree offset between those environments.  this required the use of rotated `initial_pose_x`, `initial_pose_y`, and `initial_pose_a` arguments defined in the `amcl_demo.launch` file, and the appropriate translation in the `ROBOT_INITIAL_POSE` environment variable set in the shell script `pick_objects.sh`.  the `pick_objects.sh` script launches `turtlebot`, `AMCL` and `rviz` as usual, but also runs the custom `pick_objects` `ROS` node as well, using those aforementioned coordinates to localize the robot in the exact same location in the respective `gazebo` and `rviz` views. 

below are several successive images of the robot navigating from the initial point to a (single) waypoint due west in the map, and then to the destination point due north.  

INSERT

## part 4: displaying markers on environment map
the final (independent) task was to put a geometric object on the `rviz` map to mark locations to show the robot's path.  i published a (cylindrical) marker in the map that represented the first waypoint (the 'pick up' zone, per the project instructions), displayed it for 5 seconds, then published another cylinder (in the color green, representing the 'drop off' zone) to be displayed for 5 seconds.  the second marker is then removed from the map, and the marker test concludes.  

below are several successive images that show the markers appearing at first the pickup zone, then the drop off zone. 

INSERT

## part 5: simulating autonomous home service robot

