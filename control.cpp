#include <ros/ros.h>
//#include <geometry_msgs/Twist.h> 
//#include <stdlib.h> 
#include <iostream>
#include <math.h>


int main (int argc, char **argv){

	double rho, alpha, beta, x, y, theta, xd, yd, thetad, v, gamma, L, krho, kalpha, kbeta, w, deltax, deltay;

	//Ángulos alpha y beta se calculan en radianes

	L=1.0;
	
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




