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

#define _USE_MATH_DEFINES
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <cstring>
#include <vector>
#include "../include/texture_loader.h"
#include "../include/ObjModel.h"

#define NO_ROTATION     0
#define X_AXIS_ROTATION 1
#define Y_AXIS_ROTATION 2
#define Z_AXIS_ROTATION 3
#define FOLLOW_CAM      4
#define NO_TEXTURE		5
#define DEFAULT_TEXTURE 6


#define AsRadian(x) ((x)*(M_PI/180.0f))
                                                        //One of these days we gotta split this.
float rotation = 0.0f;                                  //Part of: cubes
float eyeposVer = 1.2f; //In vertical plane: y          //Part of: camera
float eyeposHor = 0.0f; //In horizontal plane: x and z  //Part of: camera
float cameraCenterX = 0.0f;                             //Part of: camera
float cameraCenterY = 0.0f;                             //Part of: camera
float cameraCenterZ = 0.0f;                             //Part of: camera
int lastTick = 0;                                       //Part of: refreshing
bool specKeys[256]; //Looks at special keys             //Part of: keyboard
bool keys[256];     //Looks at regular keys             //Part of: keyboard
bool rotating = true;                                   //Part of: cubes
bool fullScreen = false;                                //Part of: keyboard?
texture_loader texture1("terrain.png");
texture_loader skyTex("sky.jpeg");

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
void glutKeyboardUp(unsigned char, int, int);
void glutKeyboard(unsigned char, int, int);


int main(int argc, char * argv[])
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInit(&argc, argv);
	glutCreateWindow("Hello Guus & Julian");
	printf("Programme started!\n");
	InitGraphics();
		//Models 'borrowed' from Johan
		ObjModel *terrain = new ObjModel("models/Mountain/mountain_link.obj");
		terrain->scaleModel(25);
		models.push_back(pair<int, ObjModel*>(1, terrain));
		ObjModel *kirby = new ObjModel("models/Kirby/kirby.obj");
		kirby->scaleModel(200);
		models.push_back(pair<int, ObjModel*>(130, kirby));
		ObjModel *dedede = new ObjModel("models/King_Dedede/kingdedede.obj");
		dedede->scaleModel(200);
		models.push_back(pair<int, ObjModel*>(130, dedede));
		//ObjModel *car = new ObjModel("models/car/honda_jazz.obj");
		//car->scaleModel(75);
		//models.push_back(pair<int, ObjModel*>(75, car));
		//models.push_back(std::pair<int, ObjModel*>(1, new ObjModel("models/bloemetje/PrimroseP.obj")));
		//models.push_back(pair<int, ObjModel*>(1, new ObjModel("models/cube/cube-textures.obj")));
		//models.push_back(pair<int, ObjModel*>(35, new ObjModel("models/ship/shipA_OBJ.obj")));
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
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    texture1.initTexture();
    skyTex.initTexture();
    /*glEnable(GL_FOG);
    float FogCol[3]={1.0f,1.0f,1.0f};
	glFogfv(GL_FOG_COLOR,FogCol);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 7.f);
	glFogf(GL_FOG_END, 15.f);*/

	glutMainLoop();
}

void gfxSkyBox(){ //COPY PASTE COPY PASTE IT IS THE ONLY WAY
	float posX = -125, posY=-125, posZ=-125, size = 250;
    skyTex.bindTexture();
  	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
				glBegin(GL_QUADS);
				glNormal3f(0.0f,0.0f,1.0f);
				skyTex.getTexture(1.0, 0.062);
				glVertex3f(posX,posY,posZ);
				skyTex.getTexture(1.0, 0.000);
				glVertex3f(posX,posY+size,posZ);
				skyTex.getTexture(0.5, 0.000);
				glVertex3f(posX+size,posY+size,posZ);
				skyTex.getTexture(0.5, 1.0);
				glVertex3f(posX+size,posY,posZ);

				glNormal3f(0.0f,0.0f,-1.0f);
				skyTex.getTexture(0.5, 1.0);
				glVertex3f(posX,posY,posZ+size);
				skyTex.getTexture(0.5, 0.000);
				glVertex3f(posX,posY+size,posZ+size);
				skyTex.getTexture(1.0, 0.000);
				glVertex3f(posX+size,posY+size,posZ+size);
				skyTex.getTexture(1.0, 1.0);
				glVertex3f(posX+size,posY,posZ+size);

				glNormal3f(1.0f,0.0f,0.0f);
				skyTex.getTexture(0.5, 1.0);
				glVertex3f(posX,posY,posZ);
				skyTex.getTexture(1.0, 1.0);
				glVertex3f(posX,posY,posZ+size);
				skyTex.getTexture(1.0, 0.000);
				glVertex3f(posX,posY+size,posZ+size);
				skyTex.getTexture(0.5, 0.000);
				glVertex3f(posX,posY+size,posZ);

				glNormal3f(-1.0f,0.0f,0.0f);
				skyTex.getTexture(1.0, 1.0);
				glVertex3f(posX+size,posY,posZ);
				skyTex.getTexture(0.5, 1.0);
				glVertex3f(posX+size,posY,posZ+size);
				skyTex.getTexture(0.5, 0.000);
				glVertex3f(posX+size,posY+size,posZ+size);
				skyTex.getTexture(1.0, 0.000);
				glVertex3f(posX+size,posY+size,posZ);

				glNormal3f(0.0f,1.0f,0.0f);
				skyTex.getTexture(0.5, 0.062);
				glVertex3f(posX,posY,posZ);
				skyTex.getTexture(0.5, 0.000);
				glVertex3f(posX,posY,posZ+size);
				skyTex.getTexture(0.5, 0.000);
				glVertex3f(posX+size,posY,posZ+size);
				skyTex.getTexture(0.5, 1.0);
				glVertex3f(posX+size,posY,posZ);

				glNormal3f(0.0f,-1.0f,0.0f);
				skyTex.getTexture(0.000, 1.0);
				glVertex3f(posX,posY+size,posZ);
				skyTex.getTexture(1.0, 1.0);
				glVertex3f(posX,posY+size,posZ+size);
				skyTex.getTexture(1.0, 0.000);
				glVertex3f(posX+size,posY+size,posZ+size);
				skyTex.getTexture(0.000, 0.000);
				glVertex3f(posX+size,posY+size,posZ);
			glEnd();
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
      glRotatef(-eyeposHor,0,1,0);
        break;
    }
    glTranslatef(-(size/2)-posX,-(size/2)-posY,-(size/2)-posZ);
	if (texture == DEFAULT_TEXTURE) {
		glColor3f(1, 1, 1);
		texture1.bindTexture();
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
		//texture1.stashTexture();
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

void glutSpecial(int key, int x, int y)
{
  specKeys[key] = true;
}

void glutSpecialUp(int key, int x, int y)
{
  specKeys[key] = false;
}

void glutKeyboardUp(unsigned char key, int x, int y)
{
  keys[key] = false;
}

void glutKeyboard(unsigned char key, int x, int y)
{
  keys[key] = true;  
}

void onDisplay(){ 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(
	//Eye
	cameraCenterX + (eyeposVer*cos(AsRadian(eyeposHor))),
	eyeposVer,
	cameraCenterZ + (eyeposVer*sin(AsRadian(eyeposHor))),
	//Center
	cameraCenterX,
	cameraCenterY,
	cameraCenterZ,
	//Up
	0,1,0
	);

	//ROOM==========================
	//   gfxDrawCube(-30.5, -1.5, -30.5, 100, NO_ROTATION,NO_TEXTURE);

	//PLAYER==========================
	//gfxDrawCube(cameraCenterX-0.25, -0.5, cameraCenterZ-0.25, 0.5, FOLLOW_CAM,DEFAULT_TEXTURE);
	//Loaded complex mesh object===
	glPushMatrix();
	glTranslatef(cameraCenterX, 0, cameraCenterZ);
	glRotatef(-eyeposHor-90,0,1,0);
	models[1].second->draw();
	glPopMatrix();
	//End of loaded object=========

	//CUBE_A========================
	gfxDrawCube(-2.5,-0.5,-0.5,1,X_AXIS_ROTATION,DEFAULT_TEXTURE);
	gfxDrawCube(-2.5,2.5,-0.5,1,X_AXIS_ROTATION,DEFAULT_TEXTURE);

//	//CUBE_B========================
	gfxDrawCube(-0.5,-0.5,-0.5,1,Y_AXIS_ROTATION,DEFAULT_TEXTURE);
//
//	//CUBE_C========================
	gfxDrawCube(1.5,-0.5,-0.5,1,Z_AXIS_ROTATION,DEFAULT_TEXTURE);
//
//	//ETC_CUBES=====================
	gfxDrawCube(-4,-0.5,-6.5,1,Y_AXIS_ROTATION,DEFAULT_TEXTURE);
	gfxDrawCube(6,-0.5,-7,1,Z_AXIS_ROTATION,DEFAULT_TEXTURE);
	gfxDrawCube(7,-0.5,4,1,X_AXIS_ROTATION,DEFAULT_TEXTURE);
	gfxDrawCube(-8,-0.5,-4,1,Y_AXIS_ROTATION,DEFAULT_TEXTURE);
	gfxDrawCube(-4,3.5,-6.5,1,Y_AXIS_ROTATION,DEFAULT_TEXTURE);
	gfxDrawCube(6,3.5,-7,1,Z_AXIS_ROTATION,DEFAULT_TEXTURE);
	gfxDrawCube(7,3.5,4,1,X_AXIS_ROTATION,DEFAULT_TEXTURE);
	gfxDrawCube(-8,3.5,-4,1,Y_AXIS_ROTATION,DEFAULT_TEXTURE);
	
	glPushMatrix();
	glTranslatef(-1.1,0,-4.4);
	glRotatef(rotation,0,1,0);
	models[2].second->draw();
	glPopMatrix();
	
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

	/*Sky=======================
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

	//Sky================*/
	gfxSkyBox();
    glEnable(GL_TEXTURE_2D);
	//Obj ground, seemed like fun.
	glPushMatrix();
	glTranslatef(0,-0.5,0);
	models[0].second->draw();
	glPopMatrix();

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

void KeyboardIdle(double const &ticks){
  double factor = 0.1;
  eyeposHor = fmod(eyeposHor, 360.0f);
  if(specKeys[GLUT_KEY_RIGHT])
  {      
    eyeposHor+=ticks/10;  //Rotate around center, right
  }
  if(specKeys[GLUT_KEY_LEFT])
  {
    eyeposHor-=ticks/10;  //Rotate around center, left
  }
  if(specKeys[GLUT_KEY_UP]){
    cameraCenterY += 0.1f; //Lookup
    if(cameraCenterY > 10)
      cameraCenterY = 10;
  }
  if(specKeys[GLUT_KEY_DOWN]){
    cameraCenterY -= 0.1f; //Lookdown
    if(cameraCenterY < -10)
      cameraCenterY = -10;
  }
  if(keys[97]){ //a
	  cameraCenterX -= factor * cos(AsRadian(eyeposHor - 90));       // Move left
	  cameraCenterZ -= factor * sin(AsRadian(eyeposHor - 90));
  }
  if(keys[100]){ //d
	  cameraCenterX -= factor * cos(AsRadian(eyeposHor + 90));       // Move right
	  cameraCenterZ -= factor * sin(AsRadian(eyeposHor + 90));
  }
  if(keys[119]){ //w
    cameraCenterX -= factor * cos(AsRadian(eyeposHor));       // Move forward
    cameraCenterZ -= factor * sin(AsRadian(eyeposHor));
  }
  if(keys[115]){ //s
    cameraCenterX += factor * cos(AsRadian(eyeposHor));       // Move backwards
    cameraCenterZ += factor * sin(AsRadian(eyeposHor));
  }
  if(keys[113]){ //q
    eyeposVer+=ticks/100; //Zoom out
  }
  if(keys[101]){ //e
    eyeposVer-=ticks/100;
    if(eyeposVer <= 0.5)
      eyeposVer = 0.5;  //Zoom in
  }
  if(keys[6]){  //ctrl+f
    if(fullScreen){
      glutReshapeWindow(800, 600);            // Restore to window
      glutPositionWindow(0,0);
      fullScreen = !fullScreen;
    }
    else
    {
      glutFullScreen();                       // FullScreen glory
      fullScreen = !fullScreen;
    }
  }
  if(keys[112]){ //p
    rotating = !rotating;
  }  
  if(keys[27]){ //ESCAPE
    exit(0);
  }
}   

void IdleFunc(void)
{
  int timeNow = glutGet(GLUT_ELAPSED_TIME);
  double ticks = (timeNow - lastTick);
  if (rotating) {
    rotation += ticks/10;
  }
  KeyboardIdle(ticks);
  lastTick = timeNow;
//  rSleep(ticks/10);
  glutPostRedisplay();
}

