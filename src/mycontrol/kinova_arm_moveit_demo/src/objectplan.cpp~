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

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#include <object_recognition_msgs/RecognizedObjectArray.h>
#include <object_recognition_msgs/RecognizedObject.h>
#include <object_recognition_core/db/prototypes/object_info.h>
#include <object_recognition_ros/object_info_cache.h>

using namespace std;

struct objectposition
{
	double x;
	double y;
	double z;
	string name;
};
vector<string>	ObjectName;
vector<objectposition> ObjectPositions;



void MyCallback(const object_recognition_msgs::RecognizedObjectArrayConstPtr& msg)
{
	for (size_t i_msg = 0; i_msg < msg->objects.size(); ++i_msg)
	 {
		const object_recognition_msgs::RecognizedObject& object = msg->objects[i_msg];
        object_recognition_core::prototypes::ObjectInfo object_info;  // object information 
        object_recognition_ros::ObjectInfoDiskCache info_cache;       // get information

        info_cache.getInfo(object.type, object_info);
        std::string name = object_info.get_field<std::string>("name");

		vector<string>::iterator result = find(ObjectName.begin(), ObjectName.end(), name);  // find object for recognition
		if (result != ObjectName.end())    //  find or not
		{
			ObjectName.erase(result);     // erase object, only find the object with max confidence
			result = ObjectName.begin();
		    	cout << "object name:          " << name << endl;
			cout << "object key:           " << object.type.key << endl;
			cout << "object confidence:    " << object.confidence << endl;

	        double x = object.pose.pose.pose.position.x;
	        double y = object.pose.pose.pose.position.y;
	        double z = object.pose.pose.pose.position.z;
	        double x_tran = -1*x + 0*y        + 0*z            + 0.25;
	        double y_tran =  0*x + 0.900969*y + 0.433884*z     + (-0.7);
	        double z_tran =  0*x + 0.433884*y + (-0.900969)*z  + 0.8;
			
			struct objectposition objectpos;
			objectpos.x = x_tran;
			objectpos.y = y_tran;
			objectpos.z = z_tran;
			objectpos.name = name;
			ObjectPositions.push_back(objectpos);

          

			//graspaction(x_tran, y_tran, z_tran, name);

			cout << "object pose frame_id: " << object.pose.header.frame_id << endl;
			cout << "object position x in world: " << x_tran << endl;
			cout << "object position y in world: " << y_tran << endl;
			cout << "object position z in world: " << z_tran << endl;
			cout << endl;  
		}
	}
}



int main(int argc, char **argv)
{
	int i=0, j=0;
	ros::init(argc, argv, "objectplan");

	// the object for recognition
	ObjectName.push_back("square_50");
	ObjectName.push_back("cuboid_3");
	ObjectName.push_back("centrum");
	ObjectName.push_back("centrum_5");
	ObjectName.push_back("prisms_6");
/*
	ObjectName.push_back("ball");
	ObjectName.push_back("centrum");
	ObjectName.push_back("cuboid_3");
	ObjectName.push_back("square_50");
	//ObjectName.push_back("cylinder_75");
	//ObjectName.push_back("prisms_6");
	//ObjectName.push_back("centrum_4");
	//ObjectName.push_back("cuboid_4");
	//ObjectName.push_back("centrum_5");
	ObjectName.push_back("centrum_6");
*/
 
	ros::AsyncSpinner spinner(1);
	spinner.start();

	moveit::planning_interface::MoveGroup group("arm");
	moveit::planning_interface::MoveGroup gripper_group("gripper");

	ros::NodeHandle nh;
	ros::Subscriber sub = nh.subscribe("recognized_object_array", 1000, MyCallback);

    sleep(1);

	vector<objectposition>::iterator it=ObjectPositions.begin();
	



	for(it = ObjectPositions.begin();it != ObjectPositions.end();it++)
	{
		geometry_msgs::Pose target_pose1;
		geometry_msgs::Pose target_pose2;
		geometry_msgs::Pose target_pose3;
		geometry_msgs::Pose target_pose4;
		geometry_msgs::Pose target_pose5;
		geometry_msgs::Pose target_pose6;
		geometry_msgs::Pose target_pose7;
		geometry_msgs::Pose target_pose8;

		vector<geometry_msgs::Pose> waypoints;

		moveit::planning_interface::MoveGroup::Plan my_plan;

		gripper_group.setNamedTarget("Open");
		gripper_group.move();

		group.setPlanningTime(8);

		target_pose1.position.x = (*it).x;
		target_pose1.position.y = (*it).y;
		target_pose1.position.z = 0.22;
		target_pose1.orientation.x = 1;
		target_pose1.orientation.y = 0;
		target_pose1.orientation.z = 0;
		target_pose1.orientation.w = 0;

		cout << "object position x in world: " << (*it).x << endl;
		cout << "object position y in world: " << (*it).y << endl;
		cout << "object position z in world: " << (*it).z << endl;

		target_pose2 = target_pose1;

		sleep(1);

		string name=(*it).name;
		cout<<name<<endl;
		if(name.compare("cuboid_3")==0 || name.compare("cuboid_4")==0 || name.compare("prisms_6")==0)
		{
			target_pose2.position.z -= 0.10;
		}
		else
		{
			target_pose2.position.z -= 0.125;
		}


		cout<<target_pose2.position.z<<endl;

		waypoints.push_back(target_pose1);
		waypoints.push_back(target_pose2);

		moveit_msgs::RobotTrajectory trajectory;
		double fraction = group.computeCartesianPath(waypoints,
					                               0.01,  // eef_step
					                               0.0,   // jump_threshold
					                               trajectory);
		my_plan.trajectory_=trajectory;
		group.execute(my_plan);
		ROS_INFO("plan 1");
		waypoints.clear();			//clear exist trajectory,avoid execute again

		sleep(1);

		gripper_group.setNamedTarget("Close");
		gripper_group.move();

		sleep(1);

		target_pose3 = target_pose1;

		waypoints.push_back(target_pose3);
		fraction = group.computeCartesianPath(waypoints,
					                        0.01,  // eef_step
					                        0.0,   // jump_threshold
					                        trajectory);
		my_plan.trajectory_=trajectory;
		group.execute(my_plan);
		ROS_INFO("plan 2");
        waypoints.clear();

		sleep(1);

        target_pose7 = target_pose1;
		target_pose7.position.x = 0.4;
		target_pose7.position.y = -0.3;

		waypoints.push_back(target_pose7);
		fraction = group.computeCartesianPath(waypoints,
					                        0.01,  // eef_step
					                        0.0,   // jump_threshold
					                        trajectory);
		my_plan.trajectory_=trajectory;
		group.execute(my_plan);
		ROS_INFO("plan 3");
        waypoints.clear();

		sleep(1);

		target_pose8 = target_pose1;
		target_pose8.position.x = 0.33;
		target_pose8.position.y = 0.2;

		group.setPoseTarget(target_pose8);
		bool success = group.plan(my_plan);
		ROS_INFO("plan 4 %s",success?"SUCCESS":"FAILED");
		group.execute(my_plan);

		sleep(1);

		target_pose4 = target_pose8;
		target_pose4.position.x = target_pose8.position.x;
		i++;


		target_pose5 = target_pose4;

		target_pose5.position.z -= 0.15;

		waypoints.push_back(target_pose4);
        //waypoints.push_back(target_pose5);
		fraction = group.computeCartesianPath(waypoints,
					                        0.01,  // eef_step
					                        0.0,   // jump_threshold
					                        trajectory);
		my_plan.trajectory_=trajectory;
		group.execute(my_plan);
		ROS_INFO("plan 5");
        waypoints.clear();

		sleep(1);

		
		gripper_group.setNamedTarget("Open");
		gripper_group.move();

		sleep(1);

		target_pose6 = target_pose4;
		waypoints.push_back(target_pose6);
		fraction = group.computeCartesianPath(waypoints,
					                        0.01,  // eef_step
					                        0.0,   // jump_threshold
					                        trajectory);
		my_plan.trajectory_=trajectory;
		group.execute(my_plan);
		ROS_INFO("plan 6");
        waypoints.clear();

		sleep(1);
	}
	ObjectPositions.clear();

	ros::spin();
	ros::waitForShutdown();

	//graspaction();

	//ros::shutdown();  
	return 0;
}
