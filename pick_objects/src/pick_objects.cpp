#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
using namespace std;

int const NUM_LOCATIONS = 2;
float const LOCATIONS[NUM_LOCATIONS][3] = {{ -8.3, 4.5, 1.0 },  // starting at -0.5, -8.3 in map
                                           { -5.0, 4.5, 1.0 }}; 

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "pick_objects");   // initiatlize ROS node

  MoveBaseClient ac("move_base", true);    // tell action client to create new thread

  while(!ac.waitForServer(ros::Duration(5.0)))  // wait 5 seconds for action server
  {
    ROS_INFO("waiting for move_base action server to initialize...");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set attribute info for pickup location
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp    = ros::Time::now();

  cout << "BEGINNING NAVIGATION...\n";

  for(int i=0; i<NUM_LOCATIONS; i++)
  {
    cout << "sending coordinates of location " << i << ": " << LOCATIONS[i][0] << " " << LOCATIONS[i][1] << flush;
    
    goal.target_pose.pose.position.x    = LOCATIONS[i][0];  
    goal.target_pose.pose.position.y    = LOCATIONS[i][1];  
    goal.target_pose.pose.orientation.w = LOCATIONS[i][2];  

    ac.sendGoal(goal);
    ac.waitForResult();

    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      cout << " --> SUCCESS: reached target location" << endl;
    else
      cout << " --> FAILURE: robot failed to reach goal" << endl;

    sleep(5); 
  }

  cout << "COMPLETED NAVIGATION...\n";
  sleep(5);
  return(0);
}


