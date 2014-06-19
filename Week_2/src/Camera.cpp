//
//  Camera.cpp
//
//  Created by Guus Beckett and Julian West on 15/06/14.
//  Copyright (c) 2014 reupload.nl. All rights reserved.
//
#ifdef __APPLE__
#include <GLUT/glut.h>
#elif _WIN32
#include "glut.h"
#elif  __gnu_linux__
#include <GL/glut.h>
#else
#error "Your OS cannot compile this program!"
#endif

#include "../include/Camera.h"

float cam_eyeposVer; //In vertical plane: y
float cam_eyeposHor; //In horizontal plane: x and z
float cam_cameraCenterX;
float cam_cameraCenterY;
float cam_cameraCenterZ;

void cam_getIntrinsics(float &centerX, float &centerY, float &centerZ, float &rotation){
	centerX = cam_cameraCenterX;
	centerY = cam_cameraCenterY;
	centerZ = cam_cameraCenterZ;
	rotation = cam_eyeposHor;
}

void cam_defineLookAt(){
	if(!cam_eyeposVer){
		cam_eyeposVer=3.2f;
	}
	gluLookAt(
		//Eye
		cam_cameraCenterX + (cam_eyeposVer*cos(AsRadian(cam_eyeposHor))),
		cam_eyeposVer,
		cam_cameraCenterZ + (cam_eyeposVer*sin(AsRadian(cam_eyeposHor))),
		//Center
		cam_cameraCenterX,
		cam_cameraCenterY,
		cam_cameraCenterZ,
		//Up
		0,1,0
	);
}

void cam_move(const unsigned char &direction, const double &factor){
	switch(direction){
	case CAM_LEFT:
		cam_cameraCenterX -= factor * cos(AsRadian(cam_eyeposHor - 90));       // Move left
		cam_cameraCenterZ -= factor * sin(AsRadian(cam_eyeposHor - 90));
		break;
	case CAM_RIGHT:
		cam_cameraCenterX -= factor * cos(AsRadian(cam_eyeposHor + 90));       // Move right
		cam_cameraCenterZ -= factor * sin(AsRadian(cam_eyeposHor + 90));
		break;
	case CAM_UP:
		cam_cameraCenterX -= factor * cos(AsRadian(cam_eyeposHor));       // Move forward
		cam_cameraCenterZ -= factor * sin(AsRadian(cam_eyeposHor));
		break;
	case CAM_DOWN:
		cam_cameraCenterX += factor * cos(AsRadian(cam_eyeposHor));       // Move backwards
		cam_cameraCenterZ += factor * sin(AsRadian(cam_eyeposHor));
		break;
	}
}

void cam_look(const unsigned char &direction, const double &factor){
	switch(direction){
		case CAM_LEFT:
			cam_eyeposHor-=factor/10;  //Rotate around center, left
			break;
		case CAM_RIGHT:
			cam_eyeposHor+=factor/10;  //Rotate around center, right
			break;
		case CAM_UP:
			cam_cameraCenterY += factor; //Lookup
			    if(cam_cameraCenterY > 10)
			    	cam_cameraCenterY = 10;
			break;
		case CAM_DOWN:
			cam_cameraCenterY -= factor; //Lookdown
			    if(cam_cameraCenterY < -10)
			    	cam_cameraCenterY = -10;
			break;
		}
	cam_eyeposHor = fmod(cam_eyeposHor, 360.0f);
}

void cam_zoom(const double &factor){
	cam_eyeposVer+=factor/100; //Zoom out
	if(cam_eyeposVer <= 1.0)
		 cam_eyeposVer = 1.0;  //Zoom in
}
