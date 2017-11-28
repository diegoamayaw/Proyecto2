#include <ros/ros.h>
#include <geometry_msgs/Pose2D.h>
#include <std_msgs/Float32.h>
#include <stdlib.h> 
#include <iostream>
#include <math.h>

//variables recibidas
double x, y, theta, xd, yd, thetad, L, hz, e;
//variables internas de control
bool flag1,flag2;

// callback para leer la posicion del movil
void poseMessageReceived (const geometry_msgs::Pose2D& msg1){
	x=msg1.x;
	y=msg1.y;
	theta=msg1.theta;
	flag1=true;
}

// callback para leer la posicion deseada del movil
void poseDMessageReceived (const geometry_msgs::Pose2D& msg2){
	xd=msg2.x;
	yd=msg2.y;
	thetad=msg2.theta;
	flag2=true;
}

int main (int argc, char **argv){
	//variables internas
	double rho, alpha, beta, krho, kalpha, kbeta, w, deltax, deltay, error;	
	//variables de publicacion
	double v, gamma;

	flag1=false;
	flag2=false;
	
	// Inicializa ROS system y crea un nodo.
	ros::init(argc, argv, "robot_controller");
	ros::NodeHandle nh ;
	// Crea un objeto publicador .
	ros::Publisher pubS=nh.advertise<std_msgs::Float32>("/AutoNOMOS_mini/manual_control/steering",1000);
	ros::Publisher pubV=nh.advertise<std_msgs::Float32>("/AutoNOMOS_mini/manual_control/velocity",1000);
	// Crea un objeto suscriptor
	ros::Subscriber subP = nh.subscribe("robot/pose", 1000, &poseMessageReceived);
	ros::Subscriber subPD = nh.subscribe("robot/next_pose", 1000, &poseDMessageReceived);
	//Crea el objeto mensaje
	std_msgs::Float32 msgSteering;
	std_msgs::Float32 msgVelocity;


	//Obtener informacion del usuario
	ROS_INFO_STREAM("Indique los Hertz");
	std::cin >> hz;

	// Ciclo a hz Hz
	ros::Rate rate (hz);

	//Constante del auto	
	L=0.32;

	//Valores de control
	krho=1;
	kalpha=8;
	kbeta=-2;
	e=0.10;
	
	//Ángulos alpha y beta se calculan en radianes

	//Ciclo principal
    	while (ros::ok()) {
		if (flag1 && flag2){
			//Calculos para pose deseada
			deltax=(xd-x);
			deltay=(yd-y);
			//Detener si la distancia es tolerable
			error=sqrt(deltax*deltax+deltay*deltay);
			if(e>error){
				gamma=0;
				v=0;	
			}else{
				rho=error;
				alpha=atan(deltay/deltax)-theta;
				beta=-theta-alpha;

				v=krho*rho;
				gamma=kalpha*alpha+kbeta*beta;
			}
			//Si el punto deseado esta detras del movil, avanza de reversa
			if(deltax<0 || deltay<0){
				v=-v;
				gamma=-gamma;
				ROS_INFO_STREAM("De reversa mami");
			}

			//Publicar control
			msgSteering.data=gamma;
			msgVelocity.data=v;
			pubS.publish(msgSteering);
			pubV.publish(msgVelocity);
			ROS_INFO_STREAM("Velocity: "<< v<< ", Gamma: " << gamma);
			
			flag1=false;
		}else{
			//No se sabe de la ubicacion del auto
			//Publicar detenerse
			msgSteering.data=0;
			msgVelocity.data=0;
			pubS.publish(msgSteering);
			pubV.publish(msgVelocity);
			ROS_INFO_STREAM("Velocity: 0" << ", Gamma: 0");

		}
		
		ros::spinOnce();
		// Espera hasta que es tiempo de la siguiente iteracion
		rate.sleep();
	}	
	
}
