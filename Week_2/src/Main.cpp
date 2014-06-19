//
//  main.cpp
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

#include <iostream>
#include "../include/texture_loader.h"
#include "../include/ObjModel.h"
#include "../include/Keyboard.h"
#include "../include/Camera.h"
#include "../include/Cubes.h"

int lastTick = 0;
texture_loader skyTex("sky.jpeg");   //Should be moved to Skybox file

std::vector<ObjModel*> models;

void Display(void);
void Reshape(GLint, GLint);
void InitGraphics(void);
void MouseButton(int, int, int, int);
void MouseMotion(int, int);
//void Keyboard(unsigned char, int, int);
void onDisplay();
void rSleep(int);
void IdleFunc(void);
void initCubes();

int main(int argc, char * argv[])
{
	std::cout<<"Control scheme:"<<std::endl;
	std::cout<<"W forward"<<std::endl;
	std::cout<<"A strafe left"<<std::endl;
	std::cout<<"S backwards"<<std::endl;
	std::cout<<"D strage right"<<std::endl;
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInit(&argc, argv);
	glutCreateWindow("Project Finale");
	printf("Programme started!\n");
	InitGraphics();
	kb_init();
	cubes_initCubes(); //Load cube models into cube vector
		//Models 'borrowed' from models-resource.com
		ObjModel *terrain = new ObjModel("models/Mountain/mountain_link.obj");
		terrain->scaleModel(25);
		models.push_back(terrain);
		ObjModel *kirby = new ObjModel("models/Kirby/kirby.obj");
		kirby->scaleModel(200);
		models.push_back(kirby);
		ObjModel *dedede = new ObjModel("models/King_Dedede/kingdedede.obj");
		dedede->scaleModel(200);
		models.push_back(dedede);
		ObjModel *ice_cream = new ObjModel("models/Food/Ice_Cream/TopL.obj");
		ice_cream->scaleModel(1);
		models.push_back(ice_cream);
		//Models 'borrowed' from Johan
		//ObjModel *car = new ObjModel("models/car/honda_jazz.obj");
		//car->scaleModel(75);
		//models.push_back(car));
		//models.push_back(new ObjModel("models/bloemetje/PrimroseP.obj"));
		//models.push_back(new ObjModel("models/cube/cube-textures.obj"));
		//models.push_back(new ObjModel("models/ship/shipA_OBJ.obj")); scale me(35)
		//models.push_back(new ObjModel("models/normalstuff/normaltest2.obj"));
	glutDisplayFunc (onDisplay);
	glutReshapeFunc (Reshape);
	glutIdleFunc (IdleFunc);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    skyTex.initTexture();
    /*glEnable(GL_FOG);
    float FogCol[3]={1.0f,1.0f,1.0f};
	glFogfv(GL_FOG_COLOR,FogCol);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 7.f);
	glFogf(GL_FOG_END, 15.f);*/
	glutMainLoop();
}

void gfxSkyBox(){ //Should be moved to Skybox file
	float posX = -100, posY=-100, posZ=-100, size = 200;
    skyTex.bindTexture();
  	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
				glBegin(GL_QUADS);
				glNormal3f(0.0f,0.0f,1.0f);
				skyTex.getTexture(1.0, 1.0);
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
				skyTex.getTexture(0.5, 1.0);
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

	cam_defineLookAt();
	for(Cube *c : cubes_getCubes()){
		c->draw();
	}

	float playerX,playerY,playerZ,playerRotation;
	cam_getIntrinsics(playerX,playerY,playerZ,playerRotation);

	models[1]->draw(Vec3f(playerX, 0, playerZ),Vec3f(0,1,0),-playerRotation-90);
	models[2]->draw(Vec3f(-1.1,0,-4.4),Vec3f(0,1,0),30);
	
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

	gfxSkyBox();
    glEnable(GL_TEXTURE_2D);
	//Obj ground, seemed like fun.
	models[0]->draw(Vec3f(0,-0.5,0),Vec3f(0,0,0),0);

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
  for(Cube *c : cubes_getCubes()){
	if(c->isRotating)
		c->rotation_current += ticks/10;
  }
  kb_idle(ticks);
  lastTick = timeNow;
//  rSleep(ticks/10);
  glutPostRedisplay();
}

