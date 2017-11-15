#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include <stdlib.h> 
#include <iostream>
#include <math.h>

//variables recibidas
double x, y, theta, xd, yd, thetad, L, hz;
//variables internas de control
bool flag1,flag2;

// callback para leer la posicion de la tortuga
void poseMessageReceived (const geometry_msgs::Pose2D& msg1){
	x=msg1.x;
	y=msg1.y;
	theta=msg1.theta;
	flag1=true;
}

// callback para leer la posicion deseada de la tortuga
void poseDMessageReceived (const geometry_msgs::Pose2D& msg2){
	xd=msg2.x;
	yd=msg2.y;
	thetad=msg2.theta;
	flag2=true;
}

int main (int argc, char **argv){
	//variables internas
	double rho, alpha, beta, krho, kalpha, kbeta, w, deltax, deltay;	
	//variables de publicacion
	double v, gamma;

	flag1=false;
	flag2=false;
	
	// Inicializa ROS system y crea un nodo.
	ros::init(argc, argv, "robot_controller");
	ros::NodeHandle nh ;
	// Crea un objeto publicador .
	ros::Publisher pub=nh.advertise<geometry_msgs::Twist>("robot/u",1000);
	// Crea un objeto suscriptor
	ros::Subscriber subP = nh.subscribe("robot/pose", 1000, &poseMessageReceived);
	ros::Subscriber subPD = nh.subscribe("robot/next_pose", 1000, &poseDMessageReceived);
	//Crea el objeto mensaje
	geometry_msgs::Twist msg;

	//Obtener informacion del usuario
	ROS_INFO_STREAM("Indique los Hertz");
	std::cin >> hz;

	// Ciclo a hz Hz
	ros::Rate rate (hz);

	//Constante del auto	
	L=1.0;

	//Valores de control
	krho=5;
	kalpha=5;
	kbeta=5;
	
	//Ángulos alpha y beta se calculan en radianes

	//Ciclo principal
    	while (ros::ok()) {
		if (flag1 && flag2){
			//Calculos para pose deseada
			deltax=(xd-x);
			deltay=(yd-y);

			rho=sqrt(pow(deltax,2)+pow(deltay,2));
			alpha=atan(deltay/deltax)-theta;
			beta=-theta-alpha;

			v=krho*rho;
			gamma=kalpha*alpha-kbeta*beta;
			w=(v/L)*tan(gamma);

			//Publicar control
			msg.linear.x=v;
			msg.angular.z=gamma;
			pub.publish(msg);
			ROS_INFO_STREAM("Velocity: "<< v<< ", Gamma: " << gamma);
			
			flag1=false;
		}else{
			//No se sabe de la ubicacion del auto
			//Publicar detenerse
			msg.linear.x=0;
			msg.angular.z=0;
			pub.publish(msg);
			ROS_INFO_STREAM("Velocity: "<< v<< ", Gamma: " << gamma);

			//Ejemplo para probar el código	
			x=0;
			y=0;
			theta=0;
			xd=10;
			yd=10;
			thetad=90;

			deltax=(xd-x);
			deltay=(yd-y);

			rho=sqrt(pow(deltax,2)+pow(deltay,2));

			alpha=atan(deltay/deltax)-theta;

			beta=-theta-alpha;

			v=krho*rho;
			gamma=kalpha*alpha-kbeta*beta;
			w=(v/L)*tan(gamma);
	
			ROS_INFO_STREAM("Rho: "<< rho<< ", Alpha: " << alpha<< ", Beta: "<<beta);
		}
		
		ros::spinOnce();
		// Espera hasta que es tiempo de la siguiente iteracion
		rate.sleep();
	}	
	
}
