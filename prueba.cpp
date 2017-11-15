#include <ros/ros.h>
#include <geometry_msgs/Pose2D.h>
#include <stdlib.h> 
#include <iostream>
#include <math.h>

int main (int argc, char **argv){
	int x, y, theta;
	// Inicializa ROS system y crea un nodo.
	ros::init(argc, argv, "robot_simulator");
	ros::NodeHandle nh2 ;
	// Crea un objeto publicador .
	ros::Publisher pub=nh2.advertise<geometry_msgs::Pose2D>("robot/pose",1000);
	ros::Publisher pub2=nh2.advertise<geometry_msgs::Pose2D>("robot/next_pose",1000);
	//Crea el objeto mensaje
	geometry_msgs::Pose2D msg;

	// Ciclo a 10 Hz
	ros::Rate rate (10);

	x=0;
	y=0;
	theta=0;

	//Ciclo principal
    	while (ros::ok()) {
		//Publica posicion deseada
		msg.x=200;
		msg.y=0;
		msg.theta=0;
		pub2.publish(msg);

		x=x+1;
		//Publicar posicion
		msg.x=x;
		msg.y=y;
		msg.theta=theta;
		pub.publish(msg);
			
		ros::spinOnce();
		// Espera hasta que es tiempo de la siguiente iteracion
		rate.sleep();
	}	
	
}
