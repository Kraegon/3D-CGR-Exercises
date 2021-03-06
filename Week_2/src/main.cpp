//
//  main.cpp
//  OpdrachtenWeek1
//
//  Created by Guus Beckett and Julian West on 17-04-14.
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
#define AsRadian(x) ((x)*(M_PI/180.0f))
#define _USE_MATH_DEFINES
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <cstring>
#include <vector>
#include "../include/texture_loader.h"
#include "../include/ObjModel.h"
#include "Keyboard.h"
#include "Camera.h"

#define NO_ROTATION     0
#define X_AXIS_ROTATION 1
#define Y_AXIS_ROTATION 2
#define Z_AXIS_ROTATION 3
#define FOLLOW_CAM      4
#define NO_TEXTURE		5
#define DEFAULT_TEXTURE 6
                                                        //One of these days we gotta split this. This is in progress right now :D
float rotation = 0.0f;                                  //Part of: cubes
int lastTick = 0;                                       //Part of: refreshing

std::string terrain = "terrain.png";
texture_loader texture1(terrain);

std::vector<std::pair<int, ObjModel*> > models;
int currentModel = 0;

void gfxDrawCube(float, float, float, float, int, int);
void Display(void);
void Reshape(GLint, GLint);
void InitGraphics(void);
void MouseButton(int, int, int, int);
void MouseMotion(int, int);
void glutSpecial(int, int, int);
void glutSpecialUp(int, int, int);
//void Keyboard(unsigned char, int, int);
void onDisplay();
void rSleep(int);
void IdleFunc(void);
Camera camera;

int main(int argc, char * argv[])
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInit(&argc, argv);
	glutCreateWindow("Hello Guus & Julian");
	printf("Programme started!\n");
	InitGraphics();
		//Models 'borrowed' from Johan
		//models.push_back(pair<int, ObjModel*>(75, new ObjModel("models/car/honda_jazz.obj")));	//Too large!
		models.push_back(std::pair<int, ObjModel*>(1, new ObjModel("models/bloemetje/PrimroseP.obj")));
		//models.push_back(pair<int, ObjModel*>(1, new ObjModel("models/cube/cube-textures.obj")));
		//models.push_back(pair<int, ObjModel*>(35, new ObjModel("models/ship/shipA_OBJ.obj")));	//Too large!
		//models.push_back(pair<int, ObjModel*>(1, new ObjModel("models/normalstuff/normaltest2.obj")));
	glutDisplayFunc (onDisplay);
	glutReshapeFunc (Reshape);
	glutKeyboardFunc (glutKeyboard);
	glutKeyboardUpFunc(glutKeyboardUp);
	glutMouseFunc (MouseButton);
	glutMotionFunc (MouseMotion);
	glutSpecialFunc (glutSpecial);
	glutSpecialUpFunc (glutSpecialUp);
	glutIdleFunc (IdleFunc);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glEnable(GL_FOG);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    float FogCol[3]={1.0f,1.0f,1.0f};
	glFogfv(GL_FOG_COLOR,FogCol);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 7.f);
	glFogf(GL_FOG_END, 15.f);
	texture1.initTexture();
	glutMainLoop();
}

void gfxDrawCube(float posX, float posY, float posZ, float size, int angle, int texture){
  glPushMatrix();
    glTranslatef((size/2)+posX,(size/2)+posY,(size/2)+posZ);
    switch(angle){
      case 1:
      glRotatef(rotation,1,0,0);
        break;
      case 2:
      glRotatef(rotation,0,1,0);
        break;
      case 3:
      glRotatef(rotation,0,0,1);
        break;
      case 4:
      glRotatef(-camera.getEyeposHor(),0,1,0);
        break;
    }
  glTranslatef(-(size/2)-posX,-(size/2)-posY,-(size/2)-posZ);
	if (texture == DEFAULT_TEXTURE) {
			glColor3f(1, 1, 1);
		glEnable(GL_TEXTURE_2D);
			glBegin(GL_QUADS);
			glNormal3f(0.0f,0.0f,-1.0f);
			texture1.getTexture(0.248, 0.062);
			glVertex3f(posX,posY,posZ);
			texture1.getTexture(0.248, 0.000);
			glVertex3f(posX,posY+size,posZ);
			texture1.getTexture(0.186, 0.000);
			glVertex3f(posX+size,posY+size,posZ);
			texture1.getTexture(0.186, 0.062);
			glVertex3f(posX+size,posY,posZ);
			
			glNormal3f(0.0f,0.0f,1.0f);
			texture1.getTexture(0.186, 0.062);
			glVertex3f(posX,posY,posZ+size);
			texture1.getTexture(0.186, 0.000);
			glVertex3f(posX,posY+size,posZ+size);
			texture1.getTexture(0.248, 0.000);
			glVertex3f(posX+size,posY+size,posZ+size);
			texture1.getTexture(0.248, 0.062);
			glVertex3f(posX+size,posY,posZ+size);

			glNormal3f(-1.0f,0.0f,0.0f);
			texture1.getTexture(0.186, 0.062);
			glVertex3f(posX,posY,posZ);
			texture1.getTexture(0.248, 0.062);
			glVertex3f(posX,posY,posZ+size);
			texture1.getTexture(0.248, 0.000);
			glVertex3f(posX,posY+size,posZ+size);
			texture1.getTexture(0.186, 0.000);
			glVertex3f(posX,posY+size,posZ);
			
			glNormal3f(1.0f,0.0f,0.0f);
			texture1.getTexture(0.248, 0.062);
			glVertex3f(posX+size,posY,posZ);
			texture1.getTexture(0.186, 0.062);
			glVertex3f(posX+size,posY,posZ+size);
			texture1.getTexture(0.186, 0.000);
			glVertex3f(posX+size,posY+size,posZ+size);
			texture1.getTexture(0.248, 0.000);
			glVertex3f(posX+size,posY+size,posZ);

			glNormal3f(0.0f,-1.0f,0.0f);
			texture1.getTexture(0.124, 0.062);
			glVertex3f(posX,posY,posZ);
			texture1.getTexture(0.124, 0.000);
			glVertex3f(posX,posY,posZ+size);
			texture1.getTexture(0.186, 0.000);
			glVertex3f(posX+size,posY,posZ+size);
			texture1.getTexture(0.186, 0.062);
			glVertex3f(posX+size,posY,posZ);
			
			glNormal3f(0.0f,1.0f,0.0f);
			texture1.getTexture(0.000, 0.062);
			glVertex3f(posX,posY+size,posZ);
			texture1.getTexture(0.062, 0.062);
			glVertex3f(posX,posY+size,posZ+size);
			texture1.getTexture(0.062, 0.000);
			glVertex3f(posX+size,posY+size,posZ+size);
			texture1.getTexture(0.000, 0.000);
			glVertex3f(posX+size,posY+size,posZ);
		glEnd();
		texture1.stashTexture();

	}
	else if(texture == NO_TEXTURE)
	{
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		glColor3f(1,1,1);
		glVertex3f(posX,posY,posZ);
		glVertex3f(posX,posY+size,posZ);
		glVertex3f(posX+size,posY+size,posZ);
		glVertex3f(posX+size,posY,posZ);
		
		glColor3f(1, 1, 1);
		glVertex3f(posX,posY,posZ+size);
		glVertex3f(posX,posY+size,posZ+size);
		glVertex3f(posX+size,posY+size,posZ+size);
		glVertex3f(posX+size,posY,posZ+size);
		
		glColor3f(1,0.90,1);
		glVertex3f(posX,posY,posZ);
		glVertex3f(posX,posY,posZ+size);
		glVertex3f(posX,posY+size,posZ+size);
		glVertex3f(posX,posY+size,posZ);
		
		glColor3f(1,0.85,1);
		glVertex3f(posX+size,posY,posZ);
		glVertex3f(posX+size,posY,posZ+size);
		glVertex3f(posX+size,posY+size,posZ+size);
		glVertex3f(posX+size,posY+size,posZ);
		
		glColor3f(1,0.80,1);
		glVertex3f(posX,posY,posZ);
		glVertex3f(posX,posY,posZ+size);
		glVertex3f(posX+size,posY,posZ+size);
		glVertex3f(posX+size,posY,posZ);
		
		glColor3f(1,0.70,1);
		glVertex3f(posX,posY+size,posZ);
		glVertex3f(posX,posY+size,posZ+size);
		glVertex3f(posX+size,posY+size,posZ+size);
		glVertex3f(posX+size,posY+size,posZ);
		glEnd();
	}
	
	  glPopMatrix();
}

void Display(void)
{
  glutSwapBuffers();
}

void Reshape(GLint width, GLint height)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90,width/height,0.1,200);
    glViewport(0, 0, width, height);
  glMatrixMode(GL_MODELVIEW);
}

void InitGraphics(void)
{
  glEnable(GL_DEPTH_TEST);
}

void MouseButton(int button, int state, int x, int y)
{

}

void MouseMotion(int x, int y)
{

}



void onDisplay(){ 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    gluLookAt(
              //Eye
              camera.getCameraCenterX() + (camera.getEyeposVer()*cos(AsRadian(camera.getEyeposHor()))),
              camera.getEyeposVer(),
              camera.getCameraCenterZ() + (camera.getEyeposVer()*sin(AsRadian(camera.getEyeposHor()))),
              //Center
              camera.getCameraCenterX(),
              camera.getCameraCenterY(),
              camera.getCameraCenterZ(),
              //Up
              0,1,0
              );

	//ROOM==========================
	//   gfxDrawCube(-30.5, -1.5, -30.5, 100, NO_ROTATION,NO_TEXTURE);

	//PLAYER==========================
	gfxDrawCube(camera.getCameraCenterX()-0.25, -0.5, camera.getCameraCenterZ()-0.25, 0.5, FOLLOW_CAM,DEFAULT_TEXTURE);

	//CUBE_A========================
	gfxDrawCube(-2.5,-0.5,-0.5,1,X_AXIS_ROTATION,DEFAULT_TEXTURE);
	gfxDrawCube(-2.5,2.5,-0.5,1,X_AXIS_ROTATION,DEFAULT_TEXTURE);

	//CUBE_B========================
	gfxDrawCube(-0.5,-0.5,-0.5,1,Y_AXIS_ROTATION,DEFAULT_TEXTURE);

	//CUBE_C========================
	gfxDrawCube(1.5,-0.5,-0.5,1,Z_AXIS_ROTATION,DEFAULT_TEXTURE);

	//ETC_CUBES=====================
	gfxDrawCube(-4,-0.5,-6.5,1,Y_AXIS_ROTATION,DEFAULT_TEXTURE);
	gfxDrawCube(6,-0.5,-7,1,Z_AXIS_ROTATION,DEFAULT_TEXTURE);
	gfxDrawCube(7,-0.5,4,1,X_AXIS_ROTATION,DEFAULT_TEXTURE);
	gfxDrawCube(-8,-0.5,-4,1,Y_AXIS_ROTATION,DEFAULT_TEXTURE);
	gfxDrawCube(-4,3.5,-6.5,1,Y_AXIS_ROTATION,DEFAULT_TEXTURE);
	gfxDrawCube(6,3.5,-7,1,Z_AXIS_ROTATION,DEFAULT_TEXTURE);
	gfxDrawCube(7,3.5,4,1,X_AXIS_ROTATION,DEFAULT_TEXTURE);
	gfxDrawCube(-8,3.5,-4,1,Y_AXIS_ROTATION,DEFAULT_TEXTURE);
	
	
	
	//THE_SUN!!=====================
	glPushMatrix();
	glTranslatef(0.75, 10.0, -1.0);
	glColor3f(1.0,1.0,0.0);
	glutSolidSphere(1.0, 30, 30);
	glColor3f(1, 1, 1);
	glPopMatrix();
	GLfloat sunpos[] = {0.75, 10.0, -1.0,1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, sunpos);
	//SORRY, this is very hacky :(

	//Ground=======================
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-1000.0,-1.0,-1000.0);
	glVertex3f(1000,-1.0,-1000.0);
	glVertex3f(1000.0,-1.0,1000.0);
	glVertex3f(-1000.0,-1.0,1000.0);
	glColor3f(1.0, 1.0, 1.0);
	glEnd();
	glPopMatrix();
	//End of Ground================

	//Loaded complex mesh object===
	glPushMatrix();
	glTranslatef(5,0,5);
	models[currentModel].second->draw();
	glPopMatrix();
	//End of loaded object=========

	glLoadIdentity();
	glOrtho(0,glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT), -1, 200);
	glBegin(GL_LINE_LOOP);
	glVertex2f(5, 5);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)-5, 5);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)-5, glutGet(GLUT_WINDOW_HEIGHT)-5);
	glVertex2f(5, glutGet(GLUT_WINDOW_HEIGHT)-5);
	glEnd();

	glutSwapBuffers();
}

//Meaning: redefined sleep
void rSleep(int millisec){
#ifdef _WIN32
	Sleep(millisec);
#else
	usleep(millisec);
#endif
}

void IdleFunc(void)
{
  int timeNow = glutGet(GLUT_ELAPSED_TIME);
  double ticks = (timeNow - lastTick);
    rotation += ticks/10;
  KeyboardIdle(ticks, camera);
  lastTick = timeNow;
  rSleep(ticks/10);
  glutPostRedisplay();
}

