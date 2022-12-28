#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
using namespace std;

int const NUM_MARKERS = 2;
float const MARKERS[NUM_MARKERS][3] = {{ -8.3, 4.5, 1.0 },
                                       { -5.0, 4.5, 1.0 }};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle nh;
  // ros::Rate r(3);                
  ros::Publisher marker_pub = nh.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  cout << "MARKERS INITIALIZED...\n";   // KM DEBUG
  sleep(5);                             // KM DEBUG

  uint32_t shape = visualization_msgs::Marker::CYLINDER;

  visualization_msgs::Marker marker;
  marker.header.frame_id = "map";
  marker.header.stamp    = ros::Time::now();
  marker.ns = "add_markers";
  marker.id = 0;
  marker.type = shape; 

  marker.scale.x = .3;
  marker.scale.y = .3;
  marker.scale.z = .3;

  // waypoint marker(s) will be blue, goal marker green
  marker.color.r = 0.0f;
  marker.color.g = 0.0f;
  marker.color.b = 1.0f;
  marker.color.a = 1.0;

  for(int i=0; i<NUM_MARKERS; i++)
  {
    // set all marker attributes
    marker.pose.position.x = MARKERS[i][0];
    marker.pose.position.y = MARKERS[i][1];
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0; 
    marker.pose.orientation.y = 0.0; 
    marker.pose.orientation.z = 0.0; 
    marker.pose.orientation.w = MARKERS[i][2];

    if(i == NUM_MARKERS - 1)
    {
      marker.color.r = 0.0f;
      marker.color.g = 1.0f;
      marker.color.b = 0.0f;
    }
    // ADD marker to map
    // cout << "ADDing marker " << i << endl;   // KM DEBUG
    marker.lifetime = ros::Duration(); // KM do i need this?
    marker.action   = visualization_msgs::Marker::ADD;
    marker_pub.publish(marker);

    // wait 5 seconds
    sleep(5);

    // DELETE marker
    // cout << "DELETing marker " << i << endl; // KM DEBUG
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);

    // wait 5 seconds and loop
    sleep(5); 
  }
  cout << "MARKERS COMPLETE...\n"; 
  return 0;
}

