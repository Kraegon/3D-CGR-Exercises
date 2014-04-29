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
#include <unistd.h> //Test compatibility of unistd.h's sleep with Apple systems
#endif
#ifdef __APPLE__
#include <GLUT/glut.h>
#elif _WIN32
#include <glut.h>
#elif  __gnu_linux__
#include <GL/glut.h>
#else
#error "Your OS cannot compile this program!"
#endif

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cstring>
#include "texture_loader.h"

#define X_AXIS_ROTATION 1
#define Y_AXIS_ROTATION 2
#define Z_AXIS_ROTATION 3

#define AsRadian(x) (x*(M_PI/180))

float rotation = 0.0f;
float eyeposVer = 1.2f; //In vertical plane: y
float eyeposHor = 0.0f; //In horizontal plane: x and z
float cameraCenterX = 0.0f;
float cameraCenterY = 0.0f;
float cameraCenterZ = 0.0f;
int lastTick = 0;
bool keys[256];//Because we have 256 keys, ofcourse.
bool rotating = true;
bool fullScreen = false;
const char* terrain = "terrain.png";

void gfxDrawCube(float, float, float, float, int);
void Display(void);
void Reshape(GLint, GLint);
void InitGraphics(void);
void MouseButton(int, int, int, int);
void MouseMotion(int, int);
void glutSpecial(int, int, int);
void glutSpecialUp(int, int, int);
void Keyboard(unsigned char, int, int);
void onDisplay();
void rSleep(int);
void IdleFunc(void);

int main(int argc, char * argv[])
{
	memset(keys,0,256);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInit(&argc, argv);
	glutCreateWindow("Hello Guus & Julian");
	printf("Program started!\n");
	InitGraphics();
	glutDisplayFunc (onDisplay);
	glutReshapeFunc (Reshape);
	glutKeyboardFunc (Keyboard);
	glutMouseFunc (MouseButton);
	glutMotionFunc (MouseMotion);
	glutSpecialFunc (glutSpecial);
	glutSpecialUpFunc (glutSpecialUp);
	glutIdleFunc (IdleFunc);
	glutMainLoop();
}

void gfxDrawCube(float posX, float posY, float posZ, float size, int angle){
	texture_loader texture1(terrain);
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
    }
  glTranslatef(-(size/2)-posX,-(size/2)-posY,-(size/2)-posZ);
	texture1.initTexture();
  glBegin(GL_QUADS);
		texture1.getTexture(0,0);
    glVertex3f(posX,posY,posZ);
		texture1.getTexture(1,0);
    glVertex3f(posX,posY+size,posZ);
		texture1.getTexture(0,1);
    glVertex3f(posX+size,posY+size,posZ);
		texture1.getTexture(1,1);
    glVertex3f(posX+size,posY,posZ);

		texture1.getTexture(0,0);
    glVertex3f(posX,posY,posZ);
		texture1.getTexture(1,0);
    glVertex3f(posX,posY+size,posZ);
		texture1.getTexture(0,1);
    glVertex3f(posX+size,posY+size,posZ);
		texture1.getTexture(1,1);
    glVertex3f(posX+size,posY,posZ);
	
		texture1.getTexture(0,0);
    glVertex3f(posX,posY,posZ);
		texture1.getTexture(1,0);
    glVertex3f(posX,posY+size,posZ);
		texture1.getTexture(0,1);
    glVertex3f(posX+size,posY+size,posZ);
		texture1.getTexture(1,1);
    glVertex3f(posX+size,posY,posZ);
	
		texture1.getTexture(0,0);
    glVertex3f(posX,posY,posZ);
		texture1.getTexture(1,0);
    glVertex3f(posX,posY+size,posZ);
		texture1.getTexture(0,1);
    glVertex3f(posX+size,posY+size,posZ);
		texture1.getTexture(1,1);
    glVertex3f(posX+size,posY,posZ);
	
		texture1.getTexture(0,0);
    glVertex3f(posX,posY,posZ);
		texture1.getTexture(1,0);
    glVertex3f(posX,posY+size,posZ);
		texture1.getTexture(0,1);
    glVertex3f(posX+size,posY+size,posZ);
		texture1.getTexture(1,1);
    glVertex3f(posX+size,posY,posZ);
	
		texture1.getTexture(0,0);
    glVertex3f(posX,posY,posZ);
		texture1.getTexture(1,0);
    glVertex3f(posX,posY+size,posZ);
		texture1.getTexture(0,1);
    glVertex3f(posX+size,posY+size,posZ);
		texture1.getTexture(1,1);
    glVertex3f(posX+size,posY,posZ);
	
  glEnd();
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

void glutSpecial(int key, int x, int y){
  keys[key] = true;
}

void glutSpecialUp(int key, int x, int y){
  keys[key] = false;
}


void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
        case 27:             // ESCAPE key
            exit (0);
            break;
       	case 97:			 //a
        	//cameraCenterX-=0.1f;       /* Move center left, camera will stay in place */ 
       		//Kinda broke it. Sorry Guus. Temporary functions the same as q & e
       		eyeposHor+=1.0f;	
        	if(eyeposHor>=180.0f)
       			eyeposHor = -180.0f; /* Turn left */
            printf("eyeposHor: %f\n",eyeposHor);
       		break;
       	case 100:			 //d 
        	//cameraCenterX+=0.1f;		/* Move center right, camera will stay in place */   
            eyeposHor-=1.0f;
        	if(eyeposHor<=-180.0f)
       			eyeposHor = 180.0f;     /* Turn left */
            printf("eyeposHor: %f\n",eyeposHor);
       		break;
       	case 119:			 //w
       		eyeposVer-=0.1f;            /* Move up */
       		if(eyeposVer <= 0.1)
       			eyeposVer = 0.1;        //Stops invert
       		break;
       	case 115:			 //s
       		eyeposVer+=0.1f;            /* Move down */
			break;
        case 113:            //q
            eyeposHor-=1.0f;	
        	if(eyeposHor<=-180.0f)
       			eyeposHor = 180.0f;     /* Turn left */
            break;
        case 101:           //e
       		eyeposHor+=1.0f;
        	if(eyeposHor>=180.0f)
       			eyeposHor = -180.0f; /* Turn left */
            printf("eyeposHor: %f\n",eyeposHor);
       		break;
        case 6:              //Control + f
            if (fullScreen) {
                glutReshapeWindow(800, 600);            /* Restore to window */
                glutPositionWindow(0,0);
                fullScreen = !fullScreen;
            }
            else
            {
                glutFullScreen();                       /* FullScreen glory */
                fullScreen = !fullScreen;
            }
            break;
        case 112:           //p
            rotating = !rotating;
            break;
	}
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

    //CUBE_A======================== 
    gfxDrawCube(-2.5,-0.5,-0.5,1,X_AXIS_ROTATION);
    
    //CUBE_B========================
    gfxDrawCube(-0.5,-0.5,-0.5,1,Y_AXIS_ROTATION);
    
    //CUBE_C========================
    gfxDrawCube(1.5,-0.5,-0.5,1,Z_AXIS_ROTATION);
    
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
    if (rotating) {
        rotation += ticks/10;
    }
    if(keys[GLUT_KEY_RIGHT])
    {
      eyeposHor-=ticks/10;  
      if(eyeposHor==-180.0f)
        eyeposHor = 180.0f;
    }
    if(keys[GLUT_KEY_LEFT])
    {
      eyeposHor+=ticks/10;  
      if(eyeposHor==180.0f)
        eyeposHor = -180.0f;
    }
    if(keys[GLUT_KEY_UP]){
      eyeposVer-=ticks/100;            
      if(eyeposVer <= 0.1)
        eyeposVer = 0.1;
    }
    if(keys[GLUT_KEY_DOWN]){
      eyeposVer+=ticks/100;
    }
    lastTick = timeNow;
    rSleep(ticks/10);
    glutPostRedisplay();
}



