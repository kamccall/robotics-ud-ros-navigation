#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
using namespace std;

enum ROBOT_MODE
{
  MARK_AUTO,      // _param:=mark_auto      when run from script
  MARK_FROM_ODOM  // _param:=mark_from_odom when run from script
};

enum ROBOT_STATE
{
  A_PICKUP_MOVING,
  B_PICKUP_ARRIVED,
  C_DROPOFF_MOVING,
  D_DROPOFF_ARRIVED, 
  E_DONE
};

int const NUM_MARKERS     = 2;                               // code can be adapted to arbitrary number of markers
int const WAIT_TIME       = 5;                               // modify time for screen captures!
double const DISTANCE_EPS = 0.2;                             
float const START_LOC[2]            = { -8.3, 0.5 };         // start location for robot in map
float const MARKERS[NUM_MARKERS][3] = {{ -8.3, 4.5, 1.0 },   // 0 index item pickup zone
                                       { -5.0, 4.5, 1.0 }};  // 1 index item dropoff zone

ROBOT_MODE robot_mode;
ROBOT_STATE robot_state;
float distance_pickup;
float distance_dropoff;

ros::Publisher marker_pub;
visualization_msgs::Marker marker;

// callback function to process odometry if marking map from pick_objects node (in MARK_FROM_ODOM mode)
void process_odom_data(const nav_msgs::Odometry::ConstPtr &msg)
{
  double robot_x = msg->pose.pose.position.x + START_LOC[0];
  double robot_y = msg->pose.pose.position.y + START_LOC[1];

  switch(robot_state)
  {
    case A_PICKUP_MOVING:
    {
      distance_pickup = sqrt(pow(robot_x - MARKERS[0][0], 2) + pow(robot_y - MARKERS[0][1], 2));
      if(distance_pickup <= DISTANCE_EPS)
      {
        cout << "reached pickup zone" << flush;
        robot_state = B_PICKUP_ARRIVED;
      }
      break;
    }
    case B_PICKUP_ARRIVED:
    {
      cout << " --> picking up item\n";
      sleep(WAIT_TIME);
      marker.action = visualization_msgs::Marker::DELETE; 
      marker_pub.publish(marker);                        // delete blue marker at pickup zone
      robot_state = C_DROPOFF_MOVING;
      break;
    }
    case C_DROPOFF_MOVING:
    {
      distance_dropoff = sqrt(pow(robot_x - MARKERS[1][0], 2) + pow(robot_y - MARKERS[1][1], 2));
      if(distance_dropoff <= DISTANCE_EPS)
      {
        cout << "reached dropoff zone" << flush;
        robot_state = D_DROPOFF_ARRIVED;
      }
      break;
    }
    case D_DROPOFF_ARRIVED:
    {
      cout << " --> dropping off item\n";
      marker.pose.position.x = MARKERS[1][0];
      marker.pose.position.y = MARKERS[1][1];
      marker.pose.orientation.w = MARKERS[1][2];
      marker.color.g = 1.0f;                            // dropoff location marker is green
      marker.color.b = 0.0f;
      marker.action = visualization_msgs::Marker::ADD;  
      marker_pub.publish(marker);                       // add green marker at dropoff zone
      
      sleep(WAIT_TIME);  
      robot_state = E_DONE;
      cout << "MARKERS COMPLETE...\n";
      break;
    }
    case E_DONE:
    {
      ros::shutdown();
    }
  }
}

int main(int argc, char** argv)
{
  // set mode variable and process execution parameter
  string mode_param;

  ros::init(argc, argv, "add_markers");
  ros::NodeHandle nh("~");
  nh.getParam("param", mode_param);
  marker_pub = nh.advertise<visualization_msgs::Marker>("/visualization_marker", 1);

  // determine mark_auto mode (in add_marker.sh) or mark_from_odom (in home_service.sh)
  if(mode_param.compare("mark_from_odom") == 0)
  {
    robot_mode = MARK_FROM_ODOM;
    cout << "MARK_FROM_ODOM mode enabled...\n";
  }
  else
  {
    robot_mode = MARK_AUTO;
    cout << "MARK_AUTO mode enabled...\n";
  }
 
  // output state and set pickup location attributes independent of mode 
  robot_state = A_PICKUP_MOVING;
  cout << "MARKERS INITIALIZED...\n";
  sleep(WAIT_TIME);

  uint32_t shape = visualization_msgs::Marker::CYLINDER;

  marker.header.frame_id = "map";
  marker.header.stamp    = ros::Time::now();
  marker.ns   = "add_markers";
  marker.id   = 0;
  marker.type = shape; 
  
  marker.scale.x = .3;
  marker.scale.y = .3;
  marker.scale.z = .3;

  // set pickup marker location and attributes
  marker.pose.position.x = MARKERS[0][0];
  marker.pose.position.y = MARKERS[0][1];
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0.0; 
  marker.pose.orientation.y = 0.0; 
  marker.pose.orientation.z = 0.0; 
  marker.pose.orientation.w = MARKERS[0][2];
  marker.color.r = 0.0f;
  marker.color.g = 0.0f;
  marker.color.b = 1.0f;                           // pickup location marker is blue
  marker.color.a = 1.0;
  marker.lifetime = ros::Duration();              
  
  marker.action = visualization_msgs::Marker::ADD; // add blue marker at pickup zone
  marker_pub.publish(marker);
  cout << "adding pickup zone marker...\n";
  sleep(WAIT_TIME);
 
  // robot_mode set from command line based on _param to parameter server 
  if(robot_mode == MARK_FROM_ODOM)  // marking pickup and dropoff zones from odometry feed
  {
    ros::Subscriber sub = nh.subscribe("/odom", 1000, process_odom_data);

    while(ros::ok())
    {
      ros::spinOnce();  // ros.shutdown() will come from process_odom_data callback function
    }
  }
  else                  // auto-marking both pickup and dropoff zones
  {
    sleep(WAIT_TIME);  
  
    marker.action = visualization_msgs::Marker::DELETE; 
    marker_pub.publish(marker);                         // delete blue marker at pickup zone
    cout << "deleting pickup zone marker...\n";
    sleep(WAIT_TIME);
  
    // set dropoff marker location and attributes
    marker.pose.position.x = MARKERS[1][0];
    marker.pose.position.y = MARKERS[1][1];
    marker.pose.orientation.w = MARKERS[1][2];
    marker.color.g = 1.0f;                              // dropoff location marker is green
    marker.color.b = 0.0f;

    marker.action = visualization_msgs::Marker::ADD; 
    marker_pub.publish(marker);                         // add green marker at dropoff zone
    cout << "adding dropoff zone marker...\n";
    sleep(WAIT_TIME);  
  
    marker.action = visualization_msgs::Marker::DELETE; 
    marker_pub.publish(marker);                         // delete green marker at dropoff zone
    cout << "deleting dropoff zone marker...\n";
    sleep(WAIT_TIME);

    cout << "MARKERS COMPLETE...\n"; 
    sleep(WAIT_TIME);
  }
  return 0;
}

