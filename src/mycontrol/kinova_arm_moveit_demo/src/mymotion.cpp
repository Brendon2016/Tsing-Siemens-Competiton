#include <moveit/move_group_interface/move_group.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

#include <kinova_driver/kinova_ros_types.h>
#include <kinova_msgs/SetFingersPositionAction.h>
#include <actionlib/client/simple_action_client.h>
#include <ros/ros.h>
#include <ros/console.h>

const double FINGER_MAX=6400;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "mymotion");
  ros::NodeHandle node_handle;  
  ros::AsyncSpinner spinner(1);
  spinner.start();

  sleep(1);

  moveit::planning_interface::MoveGroup group("arm");
  moveit::planning_interface::MoveGroup gripper_group("gripper");

  actionlib::SimpleActionClient<kinova_msgs::SetFingersPositionAction>* finger_client = new    actionlib::SimpleActionClient<kinova_msgs::SetFingersPositionAction>
            ("j2s7s300_driver/fingers_action/finger_positions", false);

  gripper_group.setNamedTarget("Open");
  gripper_group.move();

  group.setPlanningTime(8);
  geometry_msgs::Pose target_pose1;

  target_pose1.position.x = -0.1;
  target_pose1.position.y = -0.5;
  target_pose1.position.z = 0.4;
  target_pose1.orientation.x = 1;
  target_pose1.orientation.y = 0;
  target_pose1.orientation.z = 0;
  target_pose1.orientation.w = 0;

  moveit::planning_interface::MoveGroup::Plan my_plan;


  std::vector<geometry_msgs::Pose> waypoints;


  geometry_msgs::Pose target_pose2 = target_pose1;
  target_pose2.position.z -= 0.225;

  waypoints.push_back(target_pose1);
  waypoints.push_back(target_pose2);
  // We want the cartesian path to be interpolated at a resolution of 1 cm
  // which is why we will specify 0.01 as the max step in cartesian
  // translation.  We will specify the jump threshold as 0.0, effectively
  // disabling it.
  moveit_msgs::RobotTrajectory trajectory;
  double fraction = group.computeCartesianPath(waypoints,
                                               0.01,  // eef_step
                                               0.0,   // jump_threshold
                                               trajectory);
  my_plan.trajectory_=trajectory;
  group.execute(my_plan);
  ROS_INFO("plan 1");

  waypoints.clear();//clear exist trajectory,avoid execute again

  sleep(1);
/*
  kinova_msgs::SetFingersPositionGoal start_goal;
  start_goal.fingers.finger1 = 1*FINGER_MAX;
  start_goal.fingers.finger2 = start_goal.fingers.finger1;
  start_goal.fingers.finger3 = start_goal.fingers.finger1;

  finger_client->sendGoal(start_goal);
  finger_client->getResult();
  //sleep(2);
*/

  gripper_group.setNamedTarget("Close");
  gripper_group.move();

  sleep(1);

  geometry_msgs::Pose target_pose3 = target_pose2;
  target_pose3.position.z += 0.1;

  waypoints.push_back(target_pose3);
  // We want the cartesian path to be interpolated at a resolution of 1 cm
  // which is why we will specify 0.01 as the max step in cartesian
  // translation.  We will specify the jump threshold as 0.0, effectively
  // disabling it.
  fraction = group.computeCartesianPath(waypoints,
                                        0.01,  // eef_step
                                        0.0,   // jump_threshold
                                        trajectory);
  my_plan.trajectory_=trajectory;
  group.execute(my_plan);
  ROS_INFO("plan 2");

  sleep(1);

  geometry_msgs::Pose target_pose4;

  target_pose4.position.x = -0.5;
  target_pose4.position.y = 0.3;
  target_pose4.position.z = 0.05;
  target_pose4.orientation = target_pose1.orientation;

 
  group.setPoseTarget(target_pose4);
  bool success = group.plan(my_plan);
  ROS_INFO("plan 3 %s",success?"SUCCESS":"FAILED");
  group.execute(my_plan);

  sleep(1);
/*
  kinova_msgs::SetFingersPositionGoal end_goal;
  end_goal.fingers.finger1 = 0*FINGER_MAX;
  end_goal.fingers.finger2 = end_goal.fingers.finger1;
  end_goal.fingers.finger3 = end_goal.fingers.finger1;

  finger_client->sendGoal(end_goal);
  finger_client->getResult();
  //sleep(2);
*/
  gripper_group.setNamedTarget("Open");
  gripper_group.move();

  sleep(1);

  ros::shutdown();  
  return 0;
}
