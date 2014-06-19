//
//  Keyboard.cpp
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
#include <iostream>
#include "../include/Keyboard.h"
#include "../include/Camera.h"
#include "../include/Cubes.h"

bool kb_fullScreen = false;
bool kb_specKeys[256]; //Looks at special keys
bool kb_keys[256];     //Looks at regular keys
bool kb_keysHeld[256];     //Looks at regular keys

void kb_init(){
	glutKeyboardFunc (kb_glutKeyboard);
	glutKeyboardUpFunc(kb_glutKeyboardUp);
	glutSpecialFunc (kb_glutSpecial);
	glutSpecialUpFunc (kb_glutSpecialUp);
}

void kb_glutSpecial(int key, int x, int y)
{
	kb_specKeys[key] = true;
}

void kb_glutSpecialUp(int key, int x, int y)
{
	kb_specKeys[key] = false;
}

void kb_glutKeyboardUp(unsigned char key, int x, int y)
{
	kb_keys[key] = false;
}

void kb_glutKeyboard(unsigned char key, int x, int y)
{
	kb_keys[key] = true;
}

void kb_idle(double const &ticks){
  double factor = 0.1;
  if(kb_specKeys[GLUT_KEY_RIGHT])
  {
	  cam_look(CAM_RIGHT,ticks);  //Rotate around center, right
  }
  if(kb_specKeys[GLUT_KEY_LEFT])
  {
	  cam_look(CAM_LEFT,ticks);  //Rotate around center, left
  }
  if(kb_specKeys[GLUT_KEY_UP]){
	  cam_look(CAM_UP,factor);
  }
  if(kb_specKeys[GLUT_KEY_DOWN]){
	  cam_look(CAM_DOWN,factor);
  }
  if(kb_keys['a']){ //a
	  cam_move(CAM_LEFT, factor);
  }
  if(kb_keys['d']){ //d
	  cam_move(CAM_RIGHT, factor);
  }
  if(kb_keys['w']){ //w
	  cam_move(CAM_UP, factor);
  }
  if(kb_keys['s']){ //s
	  cam_move(CAM_DOWN, factor);
  }
  if(kb_keys['q']){ //q
	  cam_zoom(-ticks);
  }
  if(kb_keys['e']){ //e
	  cam_zoom(ticks);
  }
  if(kb_keys[6]){  //ctrl+f
    if(!kb_keysHeld[6]){
		if(kb_fullScreen){
		  glutReshapeWindow(800, 600);            // Restore to window
		  glutPositionWindow(0,0);
		  kb_fullScreen = !kb_fullScreen;
		}
		else
		{
		  glutFullScreen();                       // FullScreen glory
		  kb_fullScreen = !kb_fullScreen;
		}
    }
    kb_keysHeld[6] = true;
  }else{
	  kb_keysHeld[6] = false;
  }
  if(kb_keys['p']){ //p
	  if(!kb_keysHeld['p']){
		for(Cube *c : cubes_getCubes()){
			c->isRotating = !c->isRotating;
		}
	  }
    kb_keysHeld['p'] = true;
  }else{
	kb_keysHeld['p'] = false;
  }
  if(kb_keys['f']){
	  if(!kb_keysHeld['f']){
		  float blockX,blockY,blockZ,blockRotation,blockSize;
		  double radius = 1.4;
		  cam_getIntrinsics(blockX,blockY,blockZ,blockRotation);
		  blockSize = 1;
		  blockX-=radius*(cos(AsRadian(blockRotation))-(0.5*blockSize)) + radius;
		  blockY = -0.5f;
		  blockZ-=radius*(sin(AsRadian(blockRotation))-(0.5*blockSize)) + radius;
		  if(cubes_getCubes().size() < 500){
			  srand(time(NULL));
			  cubes_editCubes()->push_back(new Cube(blockX,blockY,blockZ,blockSize,rand()%4));
		  }
	  }
	  kb_keysHeld['f'] = true;
  }else{
	  kb_keysHeld['f'] = false;
  }
  if(kb_keys['c']){
	  if(!kb_keysHeld['c']){
		  cubes_editCubes()->clear();
	  }
	  kb_keysHeld['c'] = true;
  }else{
	  kb_keysHeld['c'] = false;
  }
  if(kb_keys[27]){ //ESCAPE
    exit(0);
  }
}
