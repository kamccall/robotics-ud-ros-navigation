#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
using namespace std;

int const NUM_MARKERS = 2;
float const MARKERS[NUM_MARKERS][3] = {{ -8.3, 4.5, 1.0 },   // 0 index item pickup zone
                                       { -5.0, 4.5, 1.0 }};  // 1 index item dropoff zone

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
  D_DROPOFF_ARRIVED
};

/*
// callback function to process odometry if marking map from pick_objects node (in MARK_FROM_ODOM mode)
void process_odom_data(const nav_msgs::Odometry::ConstPtr &msg)
{
  // 
  float robot_x_loc = msg->pose.pose.position.x;
  float robot_y_loc = msg->pose.pose.position.y;
  
  switch(ROBOT_STATE)
  {
    case A_PICKUP_MOVING:
      // STUFF
      break;
    case B_PICKUP_ARRIVED:
      // STUFF
      break;
    case C_DROPOFF_MOVING:
      // STUFF
      break;
    case D_DROPOFF_ARRIVED:
      // STUFF
      break;
  }
}
*/

int main(int argc, char** argv)
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle nh;
  ros::Publisher marker_pub = nh.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  cout << "MARKERS INITIALIZED...\n";   // KM DEBUG

  uint32_t shape = visualization_msgs::Marker::CYLINDER;

  visualization_msgs::Marker marker;
  marker.header.frame_id = "map";
  marker.header.stamp    = ros::Time::now();
  marker.ns   = "add_markers";
  marker.id   = 0;
  marker.type = shape; 
  marker.lifetime = ros::Duration(); // KM do i need this?
  
  marker.scale.x = .2;
  marker.scale.y = .2;
  marker.scale.z = .2;

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
  marker.color.b = 1.0f;  // pickup location marker is blue
  marker.color.a = 1.0;
  
  // if(cmdparam.compare("mark_auto") == 0)
  marker.action   = visualization_msgs::Marker::ADD;  // add blue marker at pickup zone
  marker_pub.publish(marker);
  cout << "adding pickup zone marker...\n";
  sleep(5);  
  
  marker.action = visualization_msgs::Marker::DELETE; // delete blue marker at pickup zone
  marker_pub.publish(marker);
  cout << "deleting pickup zone marker...\n";
  sleep(5);
  
  // set dropoff marker location and attributes
  marker.pose.position.x = MARKERS[1][0];
  marker.pose.position.y = MARKERS[1][1];
  marker.pose.orientation.w = MARKERS[1][2];
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;  // dropoff location marker is green
  marker.color.b = 0.0f;

  marker.action = visualization_msgs::Marker::ADD;    // add green marker at dropoff zone
  marker_pub.publish(marker);
  cout << "adding dropoff zone marker...\n";
  sleep(5);  
  
  marker.action = visualization_msgs::Marker::DELETE; // delete green marker at dropoff zone
  marker_pub.publish(marker);
  cout << "deleting dropoff zone marker...\n";
  sleep(5);

  cout << "MARKERS COMPLETE...\n";  // KM DEBUG
  sleep(5);
  return 0;
}

