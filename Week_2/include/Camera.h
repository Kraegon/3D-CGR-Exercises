//
//  Camera.h
//
//  Created by Guus Beckett and Julian West on 15/06/14.
//  Copyright (c) 2014 reupload.nl. All rights reserved.
//

#ifndef CAMERA_H_
#define CAMERA_H_
#define _USE_MATH_DEFINES
#include <cmath>
#define AsRadian(x) ((x)*(M_PI/180.0f))

#define CAM_LEFT 0
#define CAM_RIGHT 1
#define CAM_UP 2
#define CAM_DOWN 3

void cam_getIntrinsics(float&, float&, float&, float&);
void cam_move(const unsigned char&, const double&);
void cam_look(const unsigned char&, const double&);
void cam_zoom(const double&);
void cam_defineLookAt();

#endif
