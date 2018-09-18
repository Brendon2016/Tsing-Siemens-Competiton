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

#define base_x -0.4;
#define base_y -0.3;
#define base_z 0.03;
#define basket_x 0;
#define basket_y -0.65;
#define basket_z 0;
const int istest = 1; 

void preparepos(void)
{
	struct objectposition objectpos;
	objectpos.x = base_x;
	objectpos.y = base_y;
	objectpos.z = base_z;
	objectpos.name = ObjectName[0];
	ObjectPositions.push_back(objectpos);

	struct objectposition objectpos1;
	objectpos1.x = base_x;
	objectpos1.y = base_y + 0.05;
	objectpos1.z = base_z;
	objectpos1.name = ObjectName[1];
	ObjectPositions.push_back(objectpos1);

	struct objectposition objectpos2;
	objectpos2.x = base_x + 0.04;
	objectpos2.y = base_y - 0.05;
	objectpos2.z = base_z;
	objectpos2.name = ObjectName[2];
	ObjectPositions.push_back(objectpos2);

	struct objectposition objectpos3;
	objectpos3.x = base_x - 0.05;
	objectpos3.y = base_y - 0.05;
	objectpos3.z = base_z;
	objectpos3.name = ObjectName[3];
	ObjectPositions.push_back(objectpos3);

	struct objectposition objectpos4;
	objectpos4.x = base_x + 0.07;
	objectpos4.y = base_y + 0.07;
	objectpos4.z = base_z;
	objectpos4.name = ObjectName[4];
	ObjectPositions.push_back(objectpos4);
	
}
void MyCallback(const object_recognition_msgs::RecognizedObjectArrayConstPtr& msg)
{
/*
	if (istest == 0)
	{
	for (size_t i_msg = 0; i_msg < msg->objects.size(); ++i_msg)
	{
		const object_recognition_msgs::RecognizedObject& object = msg->objects[i_msg];    //get the first recognized object
        	object_recognition_core::prototypes::ObjectInfo object_info;  // object information 
        	object_recognition_ros::ObjectInfoDiskCache info_cache;       // get information

        	info_cache.getInfo(object.type, object_info);
        	std::string name = object_info.get_field<std::string>("name");                    // get its name

		vector<string>::iterator result = find(ObjectName.begin(), ObjectName.end(), name);  // match it by name with object which 													     // need to pick up
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
*/
}



int main(int argc, char **argv)
{
	int i=0, j=0;
	int count  = 0;
        double plan_time = 20 ;
	ros::init(argc, argv, "objectplan");

	// the object for recognition
	ObjectName.push_back("cball");
	ObjectName.push_back("bag");
	ObjectName.push_back("bear");
	ObjectName.push_back("sausage");
	//ObjectName.push_back("cake");
	//ObjectName.push_back("lemon");
	//ObjectName.push_back("milk");
	//ObjectName.push_back("cosmetic");
	//ObjectName.push_back("hippo");
	ObjectName.push_back("orange");

 
	ros::AsyncSpinner spinner(1);
	spinner.start();

	moveit::planning_interface::MoveGroup group("arm");
	moveit::planning_interface::MoveGroup gripper_group("gripper");

	ros::NodeHandle nh;
	ros::Subscriber sub = nh.subscribe("recognized_object_array", 1000, MyCallback);
	sleep(1);
	preparepos();
	sleep(1);
	vector<objectposition>::iterator it=ObjectPositions.begin();
	
	vector<geometry_msgs::Pose> waypoints;
	moveit::planning_interface::MoveGroup::Plan my_plan;
	moveit_msgs::RobotTrajectory trajectory;
	waypoints.clear();
	sleep(1);
	bool success = false;
	double fraction = 0;
	for(it = ObjectPositions.begin();it != ObjectPositions.end();it++)
	{
		cout << "object position x in world: " << (*it).x << endl;
		cout << "object position y in world: " << (*it).y << endl;
		cout << "object position z in world: " << (*it).z << endl;
		string name=(*it).name;
		cout<<name<<endl;

		geometry_msgs::Pose move_pick_above;
		geometry_msgs::Pose move_pick_down;
		geometry_msgs::Pose move_place_above;
		geometry_msgs::Pose move_place_down;
		
		//pick step 1 : open then finger
		gripper_group.setNamedTarget("Open");
		gripper_group.move();

		//pick step 2 & 3 :move to above the object & down to the tabletop
		move_pick_above.position.x = (*it).x;				
		move_pick_above.position.y = (*it).y;
		move_pick_above.position.z = 0.2;
		move_pick_above.orientation.x = 1;
		move_pick_above.orientation.y = 0;
		move_pick_above.orientation.z = 0;
		move_pick_above.orientation.w = 0;
		cout << "target position x in world: " << move_pick_above.position.x << endl;
		cout << "target position y in world: " << move_pick_above.position.y << endl;
		cout << "target position z in world: " << move_pick_above.position.z << endl;

		waypoints.push_back(move_pick_above);
		group.setPlanningTime(plan_time);			
		fraction = group.computeCartesianPath(waypoints,
					                               0.01,  // eef_step
					                               0.0,   // jump_threshold
					                               trajectory);
		my_plan.trajectory_=trajectory;
		//group.plan(my_plan);
		ROS_INFO("pick step1 : get object");
		group.execute(my_plan);
		waypoints.clear();			//clear exist trajectory,avoid execute again
		sleep(1);
		/*
		group.setPoseTarget(move_pick_above);
		success = group.plan(my_plan);
		ROS_INFO("Visualizing plan 1 (pose goal) %s",success?"":"FAILED");
		group.execute(my_plan);
		sleep(3);
		*/
		move_pick_down = move_pick_above;
		move_pick_down.position.z -= 0.15;
		cout << "target position x in world: " << move_pick_down.position.x << endl;
		cout << "target position y in world: " << move_pick_down.position.y << endl;
		cout << "target position z in world: " << move_pick_down.position.z << endl;

		waypoints.push_back(move_pick_down);	
		group.setPlanningTime(plan_time);		
		fraction = group.computeCartesianPath(waypoints,
					                               0.01,  // eef_step
					                               0.0,   // jump_threshold
					                               trajectory);
		my_plan.trajectory_=trajectory;
		//group.plan(my_plan);
		ROS_INFO("pick step1 : get object");
		group.execute(my_plan);
		waypoints.clear();			//clear exist trajectory,avoid execute again
		sleep(1);


		//pick step 4 : close the finger and pick up target object
		gripper_group.setNamedTarget("Close");					// close the finger
		gripper_group.move();
		sleep(1);

		//pick step 5 : move back to above the object
		waypoints.push_back(move_pick_above);					// return to pos1
		group.setPlanningTime(plan_time);
		fraction = group.computeCartesianPath(waypoints,
					                        0.01,  // eef_step
					                        0.0,   // jump_threshold
					                        trajectory);
		my_plan.trajectory_=trajectory;
		//group.plan(my_plan);
		group.execute(my_plan);
		ROS_INFO("pick step 2 : back to above the table");
        	waypoints.clear();
		sleep(1);






		//place step 1 & 2 : move to above the place location & down to the tabletop
		move_place_above = move_pick_above;
		move_place_above.position.x = basket_x - 0.08 * i;
		move_place_above.position.y = basket_y;
		i++;

		move_place_down = move_place_above;
		move_place_down.position.z -= 0.1;

		waypoints.push_back(move_place_above);
        	waypoints.push_back(move_place_down);
		group.setPlanningTime(plan_time);
		fraction = group.computeCartesianPath(waypoints,
					                        0.01,  // eef_step
					                        0.0,   // jump_threshold
					                        trajectory);
		my_plan.trajectory_=trajectory;
		group.execute(my_plan);
		ROS_INFO("place step 1 : place object to basket");
        	waypoints.clear();
		sleep(1);

		//place step 3 : open the finger and place the object
		gripper_group.setNamedTarget("Open");
		gripper_group.move();
		sleep(1);

		//place step 4 : move back to above the basket
		waypoints.push_back(move_place_above);
		group.setPlanningTime(plan_time);
		fraction = group.computeCartesianPath(waypoints,
					                        0.01,  // eef_step
					                        0.0,   // jump_threshold
					                        trajectory);
		my_plan.trajectory_=trajectory;
		group.execute(my_plan);
		ROS_INFO("place step 2 : back to above the table");
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
