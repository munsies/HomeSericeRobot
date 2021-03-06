#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the pick_bjects node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal pick_up;

  // set up the frame parameters
  pick_up.target_pose.header.frame_id = "map";
  pick_up.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  pick_up.target_pose.pose.position.x = -3.0;
  pick_up.target_pose.pose.position.y = -7.5;
  pick_up.target_pose.pose.orientation.w = 0.1;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending pick up location");
  ac.sendGoal(pick_up);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, robot has successfully picked up the object!");
  else
    ROS_INFO("robot could not reach pick up location!");

  // Wait 5 seconds for robot to pick up the object
  ros::Duration(2).sleep();

  move_base_msgs::MoveBaseGoal drop_off;

  // set up the frame parameters
  drop_off.target_pose.header.frame_id = "map";
  drop_off.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  drop_off.target_pose.pose.position.x = 0;
  drop_off.target_pose.pose.position.y = 0;
  drop_off.target_pose.pose.orientation.w = 0.1;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending drop off location");
  ac.sendGoal(drop_off);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, robot has successfully dropped the object!");
  else
    ROS_INFO("robot could not reach drop off location!");  

  // Wait 5 seconds for robot to drop off the object
  ros::Duration(2).sleep();

  return 0;
}