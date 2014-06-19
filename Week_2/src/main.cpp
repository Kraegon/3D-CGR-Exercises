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
float cameraCenterX = -2.0f;                             //Part of: camera
float cameraCenterY = 0.0f;                             //Part of: camera
float cameraCenterZ = 0.0f;                             //Part of: camera
float cameraCenterHeight = 1.0f;                        //Part of: camera
int lastTick = 0;                                       //Part of: refreshing
bool specKeys[256]; //Looks at special keys             //Part of: keyboard
bool keys[256];     //Looks at regular keys             //Part of: keyboard
bool rotating = false;                                  //Part of: cubes
bool fullScreen = false;                                //Part of: keyboard?
texture_loader texture1("terrain.png");
texture_loader skyTex("Cosmos03.jpg");
float xZubat = 0;
float yZubat = 0;
float zZubat = 0;
float cZubat = 0;
bool ZubatXLowering = true;
bool ZubatYLowering = true;
bool ZubatZLowering = true;
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
	glutInitWindowSize(1600, 1000);
	glutInit(&argc, argv);
	glutCreateWindow("Hello Guus & Julian");
	printf("Programme started!\n");
	InitGraphics();
        ObjModel *chari = new ObjModel("models/Charizard/charizard.obj");
        chari->scaleModel(100);
        models.push_back(pair<int, ObjModel*>(130, chari));
		ObjModel *terrain = new ObjModel("models/Mountain/mountain_link.obj");
		terrain->scaleModel(10);
		models.push_back(pair<int, ObjModel*>(130, terrain));
		ObjModel *zubat = new ObjModel("models/Zubat/zubat.obj");
		zubat->scaleModel(200);
		models.push_back(pair<int, ObjModel*>(130, zubat));
        ObjModel *pica = new ObjModel("models/Pikachu/pikachu.obj");
        pica->scaleModel(400);
        models.push_back(pair<int, ObjModel*>(130, pica));
        ObjModel *bulba = new ObjModel("models/Bulbasaur/bulbasaur.obj");
        bulba->scaleModel(400);
        models.push_back(pair<int, ObjModel*>(130, bulba));
        ObjModel *squirtle = new ObjModel("models/Squirtle/squirtle.obj");
        squirtle->scaleModel(400);
        models.push_back(pair<int, ObjModel*>(130, squirtle));
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
				skyTex.getTexture(1.0, 0.5);
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
				skyTex.getTexture(0.0, 1.0);
				glVertex3f(posX,posY,posZ);
				skyTex.getTexture(0.0, 0.0);
				glVertex3f(posX,posY,posZ+size);
				skyTex.getTexture(1.0, 1.000);
				glVertex3f(posX+size,posY,posZ+size);
				skyTex.getTexture(1.0, 0.0);
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
    skyTex.stashTexture();
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
	cameraCenterHeight,
	cameraCenterZ + (eyeposVer*sin(AsRadian(eyeposHor))),
	//Center
	cameraCenterX,
	cameraCenterY,
	cameraCenterZ,
	//Up
	0,cameraCenterHeight,0
	);

	//Loaded complex mesh object===
    if (rotation) {
        glPushMatrix();
        glTranslatef(cameraCenterX, 0.05, cameraCenterZ);
        glRotatef(rotation,0,1,0);
        models[0].second->draw();
        glPopMatrix();
    }
    else
    {
        glPushMatrix();
        glTranslatef(cameraCenterX, 0.05, cameraCenterZ);
        glRotatef(-eyeposHor-90,0,1,0);
        models[0].second->draw();
        glPopMatrix();
    }
	//End of loaded object=========
    //Load more complex mech objects :D
    cZubat += 0.001;
    xZubat = sin(cZubat)*20;
    zZubat = cos(cZubat)*20;
	glPushMatrix();
	glTranslatef(-1.1+xZubat,8+yZubat,-4.4+zZubat);
	glRotatef(0,0,1,0);
	models[2].second->draw();
	glPopMatrix();
    
	glPushMatrix();
	glTranslatef(11.1-xZubat,8+yZubat,14.4-zZubat);
	glRotatef(0,0,1,0);
	models[2].second->draw();
	glPopMatrix();

    glPushMatrix();
	glTranslatef(-3.1,0,-2.0);
	glRotatef(rotation,0,1,0);
	models[3].second->draw();
	glPopMatrix();
    
    glPushMatrix();
	glTranslatef(-2.1,0,-2.0);
	glRotatef(rotation,0,1,0);
	models[4].second->draw();
	glPopMatrix();
    
    glPushMatrix();
	glTranslatef(-1.1,0,-2.0);
	glRotatef(rotation,0,1,0);
	models[5].second->draw();
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

	gfxSkyBox();
    glEnable(GL_TEXTURE_2D);
	//Obj ground, seemed like fun, and it is :D
	glPushMatrix();
	glTranslatef(-2,-1.5,0);
	models[1].second->draw();
	glPopMatrix();
    //More complex mech objects loaded
	glLoadIdentity();
	glOrtho(0,glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT), -1, 200);

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
  if(keys[114]){
    cameraCenterHeight += 0.1f; //Move up
    if(cameraCenterHeight > 20)
      cameraCenterHeight = 20;
  }
  if(keys[102]){
    cameraCenterHeight -= 0.1f; //Move down
    if(cameraCenterHeight < 1)
      cameraCenterHeight = 1;
  }
  if(keys[97]){ //a
      float tempCameraCenterX = cameraCenterX;
      float tempCameraCenterZ = cameraCenterZ;
	  cameraCenterX -= factor * cos(AsRadian(eyeposHor - 90));       // Move left
	  cameraCenterZ -= factor * sin(AsRadian(eyeposHor - 90));
      if (cameraCenterX > -1.3)
      {
          cameraCenterX = tempCameraCenterX;
      }
      if (cameraCenterX < -3.1)
      {
          cameraCenterX = tempCameraCenterX;
      }
      if (cameraCenterZ > 1)
      {
          cameraCenterZ = tempCameraCenterZ;
      }
      if (cameraCenterZ < -14.6)
      {
          cameraCenterZ = tempCameraCenterZ;
      }
  }
  if(keys[121]){ //y
      std::cout << "YOur location (format x y) : " << cameraCenterX << " " << cameraCenterZ << std::endl;
  }
  if(keys[100]){ //d
      float tempCameraCenterX = cameraCenterX;
      float tempCameraCenterZ = cameraCenterZ;
	  cameraCenterX -= factor * cos(AsRadian(eyeposHor + 90));       // Move right
	  cameraCenterZ -= factor * sin(AsRadian(eyeposHor + 90));
      if (cameraCenterX > -1.3)
      {
          cameraCenterX = tempCameraCenterX;
      }
      if (cameraCenterX < -3.1)
      {
          cameraCenterX = tempCameraCenterX;
      }
      if (cameraCenterZ > 1)
      {
          cameraCenterZ = tempCameraCenterZ;
      }
      if (cameraCenterZ < -14.6)
      {
          cameraCenterZ = tempCameraCenterZ;
      }

  }
  if(keys[119]){ //w
      float tempCameraCenterX = cameraCenterX;
      float tempCameraCenterZ = cameraCenterZ;
    cameraCenterX -= factor * cos(AsRadian(eyeposHor));       // Move forward
    cameraCenterZ -= factor * sin(AsRadian(eyeposHor));
      if (cameraCenterX > -1.3)
      {
          cameraCenterX = tempCameraCenterX;
      }
      if (cameraCenterX < -3.1)
      {
          cameraCenterX = tempCameraCenterX;
      }
      if (cameraCenterZ > 1)
      {
          cameraCenterZ = tempCameraCenterZ;
      }
      if (cameraCenterZ < -14.6)
      {
          cameraCenterZ = tempCameraCenterZ;
      }
  }
  if(keys[115]){ //s
      float tempCameraCenterX = cameraCenterX;
      float tempCameraCenterZ = cameraCenterZ;
    cameraCenterX += factor * cos(AsRadian(eyeposHor));       // Move backwards
    cameraCenterZ += factor * sin(AsRadian(eyeposHor));
      if (cameraCenterX > -1.3)
      {
          cameraCenterX = tempCameraCenterX;
      }
      if (cameraCenterX < -3.1)
      {
          cameraCenterX = tempCameraCenterX;
      }
      if (cameraCenterZ > 1)
      {
          cameraCenterZ = tempCameraCenterZ;
      }
      if (cameraCenterZ < -14.6)
      {
          cameraCenterZ = tempCameraCenterZ;
      }
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
    rotating = false;
  }
  if(keys[111]){ //o
    rotating = true;
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

//England - World Cup 2014
//When you walk through the storm
//Hold your head up high
//And don't be afraid of the dark
//At the end of the storm
//There's a golden sky
//And the sweet silver song of the lark
//
//Walk on, through the wind
//Walk on, through the rain
//Though your dreams be tossed and blown
//Walk on, walk on, with hope in your heart
//And you'll never walk alone
//You'll never walk alone
//
//Walk on, walk on, with hope in your heart
//And you'll never walk alone
//You'll never walk alone

