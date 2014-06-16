//
//  Camera.cpp
//  OpdrachtenWeek1
//
//  Created by Guus Beckett and Julian West on 15/06/14.
//  Copyright (c) 2014 reupload.nl. All rights reserved.
//

#ifdef _WIN32
#include <stdlib.h>
#include <windows.h>
#else
#include <unistd.h>
#endif
#ifdef __APPLE__
#include <GLUT/glut.h>
#elif _WIN32
#include "glut.h"
#elif  __gnu_linux__
#include <GL/glut.h>
#else
#error "Your OS cannot compile this program!"
#endif

#include "Camera.h"

Camera::Camera(void)
{
    
}

float Camera::getEyeposHor(void)
{
    return eyeposHor;
}
float Camera::getEyeposVer(void)
{
    return eyeposVer;
}
float Camera::getCameraCenterX(void)
{
    return cameraCenterX;
}
float Camera::getCameraCenterY(void)
{
    return cameraCenterY;
}
float Camera::getCameraCenterZ(void)
{
    return cameraCenterZ;
}
void Camera::setEyeposHor(float newEyeposHor)
{
    eyeposHor = newEyeposHor;
}
void Camera::setEyeposVer(float newEyeposVer)
{
    eyeposVer = newEyeposVer;
}
void Camera::setCameraCenterX(float newCameraCenterX)
{
    cameraCenterX = newCameraCenterX;
}
void Camera::setCameraCenterY(float newCameraCenterY)
{
    cameraCenterY = newCameraCenterY;
}
void Camera::setCameraCenterZ(float newCameraCenterZ)
{
    cameraCenterZ = newCameraCenterZ;
}




