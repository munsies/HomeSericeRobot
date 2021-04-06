	#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"

// Define global vector of joints last position, moving state of the arm, and the client that can request services
// std::vector<double> position{ 0, 0, 0 };
double pos_x = 0;
double pos_y = 0;
double rot_w = 0;
int count = 0;
bool pick_up = false;
bool drop_off = false;

visualization_msgs::Marker marker;

void position_callack(const nav_msgs::Odometry::ConstPtr& msg)
{
  // ROS_INFO("Seq: [%d]", msg->header.seq);
  // // ROS_INFO("Position-> x: [%f], y: [%f]", msg->pose.pose.position.x,msg->pose.pose.position.y);
  // ROS_INFO("Orientation-> w: [%f]", msg->pose.pose.orientation.w);

  pos_x = msg->pose.pose.position.x;
  pos_y = msg->pose.pose.position.y;
  rot_w = msg->pose.pose.orientation.w;

    // Define a tolerance threshold to compare double values
    double tolerance = 0.5;

    // ROS_INFO("Position-> x: [%f], y: [%f]", pos_x,pos_y);
    // ROS_INFO("Orientation-> w: [%f]", msg->pose.pose.orientation.w);

    // if (fabs(pos_x - -1.3) < tolerance && fabs(pos_y - -4.0) < tolerance && fabs(rot_w - 1.0) < tolerance) {
    if (fabs(pos_x - -1.3) < tolerance && fabs(pos_y - -4.0) < tolerance) {  
        // ROS_INFO("Position-> x: [%f], y: [%f]", pos_x,pos_y);
        pick_up = true;

    }  

    // else if (fabs(pos_x - -3.0) < tolerance && fabs(pos_y - -3.0) < tolerance && fabs(rot_w - 1.0) < tolerance) {
    else if (fabs(pos_x - 3.0) < tolerance && fabs(pos_y - 3.25) < tolerance) {  
        // ROS_INFO("Position-> x: [%f], y: [%f]", pos_x,pos_y);
        drop_off = true;
    } 
    else {
      pick_up = false;
      drop_off = false;
    }

}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::NodeHandle n2;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  ros::Subscriber sub1 = n2.subscribe("odom", 1000,position_callack);
  if(count < 1) {
  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "add_markers";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = -3.0;
    marker.pose.position.y = -7.5;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.5;
    marker.scale.y = 0.5;
    marker.scale.z = 0.5;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 0.0f;
    marker.color.b = 1.0f;
    marker.color.a = 1.0;

    // marker.lifetime = ros::Duration(5);

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }

    marker_pub.publish(marker);
    ros::Duration(1).sleep();
    // ROS_INFO("count %d\n",count);
    }
    count++;
 
   while (ros::ok())

  //  ROS_INFO("pick value %d\n",pick_up);
    {
      if(pick_up) {

        visualization_msgs::Marker marker;
        // Set the frame ID and timestamp.  See the TF tutorials for information on these.
        marker.header.frame_id = "map";
        marker.header.stamp = ros::Time::now();

        marker.ns = "add_markers";
        marker.id = 0;
        marker.action = visualization_msgs::Marker::DELETE;

        //  Publish the marker
        while (marker_pub.getNumSubscribers() < 1)
          {
          if (!ros::ok())
            {
              return 0;
            }
            ROS_WARN_ONCE("Please create a subscriber to the marker");
            sleep(1);
          }
        marker_pub.publish(marker);
        ros::Duration(1).sleep();

      } 

      else if(drop_off) {

        uint32_t shape = visualization_msgs::Marker::CUBE;  
    
        // ROS_INFO("drop off %d\n",drop_off);

        visualization_msgs::Marker marker;
        // Set the frame ID and timestamp.  See the TF tutorials for information on these.
        marker.header.frame_id = "map";
        marker.header.stamp = ros::Time::now();

        // Set the namespace and id for this marker.  This serves to create a unique ID
        // Any marker sent with the same namespace and id will overwrite the old one
        marker.ns = "add_markers";
        marker.id = 0;

        // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
        marker.type = shape;

        marker.action = visualization_msgs::Marker::ADD;
        // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
        marker.pose.position.x = 0.25;
        marker.pose.position.y = 0.0;
        marker.pose.position.z = 0;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = 1.0; 

        // Set the scale of the marker -- 1x1x1 here means 1m on a side
        marker.scale.x = 0.5;
        marker.scale.y = 0.5;
        marker.scale.z = 0.5;

        // Set the color -- be sure to set alpha to something non-zero!
        marker.color.r = 0.0f;
        marker.color.g = 0.0f;
        marker.color.b = 1.0f;
        marker.color.a = 1.0;

              // Publish the marker
        while (marker_pub.getNumSubscribers() < 1)
        {
          if (!ros::ok())
          {
            return 0;
          }
          ROS_WARN_ONCE("Please create a subscriber to the marker");
          sleep(1);
        }
        marker_pub.publish(marker);
        ros::Duration(1).sleep();

        // ros::shutdown();

      }

      ros::spinOnce();
      r.sleep();
  }

}
