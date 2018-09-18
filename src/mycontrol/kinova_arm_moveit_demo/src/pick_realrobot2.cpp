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
#define basket_x 0;
#define basket_y -0.65;
#define basket_z 0;


#define Z_LIMIT_MAX 0.1
#define Z_LIMIT_MIN -0.1
#define X_LIMIT_MAX -0.1
#define X_LIMIT_MIN -0.56
#define Y_LIMIT_MAX 0
#define Y_LIMIT_MIN -0.7

/*
#define Z_LIMIT_MAX 0.2
#define Z_LIMIT_MIN -0.2
#define X_LIMIT_MAX 0.1
#define X_LIMIT_MIN -0.66
#define Y_LIMIT_MAX 0.1
#define Y_LIMIT_MIN -0.8
*/
struct objectposition
{
	double x;
	double y;
	double z;
	string name;
};
vector<string>	ObjectName;
vector<objectposition> ObjectPositions;

bool isrecognized = false;
bool stop_pick	= false;
void MyCallback(const object_recognition_msgs::RecognizedObjectArrayConstPtr& msg)
{
	for (size_t i_msg = 0; i_msg < msg->objects.size(); ++i_msg)
	{
		const object_recognition_msgs::RecognizedObject& object = msg->objects[i_msg];    //get the first recognized object
        	object_recognition_core::prototypes::ObjectInfo object_info;  // object information 
        	object_recognition_ros::ObjectInfoDiskCache info_cache;       // get information

        	info_cache.getInfo(object.type, object_info);
        	std::string name = object_info.get_field<std::string>("name");                    // get its name

        	double x = object.pose.pose.pose.position.x;
        	double y = object.pose.pose.pose.position.y;
        	double z = object.pose.pose.pose.position.z;
        	double x_tran = 0*x + (-1.0)*y + 0*z  - 0.46;
        	double y_tran =  (-1)*x + 0*y + 0*z   + (-0.57);
        	double z_tran =  0*x + 0*y + (-1)*z   + 0.7;

		if ((z_tran > Z_LIMIT_MAX) || (z_tran < Z_LIMIT_MIN) || (x_tran > X_LIMIT_MAX) || 
			(x_tran < X_LIMIT_MIN) || (y_tran > Y_LIMIT_MAX) || (y_tran < Y_LIMIT_MIN))
		{
			continue;
		}
		else
		{
			struct objectposition objectpos1;
			objectpos1.x = x_tran;
			objectpos1.y = y_tran;
			objectpos1.z = z_tran;
			objectpos1.name = name;
			ObjectPositions.push_back(objectpos1);

			//graspaction(x_tran, y_tran, z_tran, name);

			cout << "object pose frame_id: " << object.pose.header.frame_id << endl;
			cout << "raw position x in world: " << x << endl;
			cout << "raw position y in world: " << y << endl;
			cout << "raw position z in world: " << z << endl;
			cout << "object position x in world: " << x_tran << endl;
			cout << "object position y in world: " << y_tran << endl;
			cout << "object position z in world: " << z_tran << endl;
			cout << endl; 
		} 
	}
}



int main(int argc, char **argv)
{
	int i=0;
	int pickcount = 0;
	ros::init(argc, argv, "objectplan");

	// the object for recognition
	//ObjectName.push_back("cball");
	//ObjectName.push_back("bag");
	//ObjectName.push_back("bear");
	//ObjectName.push_back("sausage");
	//ObjectName.push_back("cake");
	//ObjectName.push_back("lemon");
	//ObjectName.push_back("milk");
	//ObjectName.push_back("cosmetic");
	//ObjectName.push_back("hippo");
	//ObjectName.push_back("orange");

	ObjectName.push_back("ball");
	ObjectName.push_back("centrum");
	ObjectName.push_back("cuboid_3");
	ObjectName.push_back("square_50");
	ObjectName.push_back("cylinder_75");
	ObjectName.push_back("prisms_6");
	ObjectName.push_back("centrum_4");
	ObjectName.push_back("cuboid_4");
	ObjectName.push_back("centrum_5");
	ObjectName.push_back("centrum_6");

 	double plan_time = 10;
	ros::AsyncSpinner spinner(1);
	spinner.start();

	moveit::planning_interface::MoveGroup group("arm");
	moveit::planning_interface::MoveGroup gripper_group("gripper");

	ros::NodeHandle nh;
	ros::Subscriber sub = nh.subscribe("recognized_object_array", 1000, MyCallback);
	sleep(5);
	
	
	vector<geometry_msgs::Pose> waypoints;
	moveit::planning_interface::MoveGroup::Plan my_plan;
	moveit_msgs::RobotTrajectory trajectory;
	waypoints.clear();
	sleep(1);
	bool success = false;
	double fraction = 0;

	while(!stop_pick)
	{
		vector<objectposition>::iterator it=ObjectPositions.begin();
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
			move_place_above.position.x = basket_x - 0.01 * i;
			move_place_above.position.y = basket_y;
			i++;

			move_place_down = move_place_above;
			move_place_down.position.z -= 0.1;

			waypoints.push_back(move_place_above);
			//waypoints.push_back(move_place_down);
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

			pickcount += 1;
			if(pickcount >= 5)
			{
				stop_pick = true;
				break;
			}
		}
		ObjectPositions.clear();
	}
	

	ros::spin();
	ros::waitForShutdown();

	//graspaction();

	//ros::shutdown();  
	return 0;
}
