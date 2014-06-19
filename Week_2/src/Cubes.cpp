/*
 * cubes.cpp
 *
 *  Created on: Jun 19, 2014
 *      Author:  Julian G. West
 */
#ifdef __APPLE__
#include <GLUT/glut.h>
#elif _WIN32
#include "glut.h"
#elif  __gnu_linux__
#include <GL/glut.h>
#else
#error "Your OS cannot compile this program!"
#endif
#include <vector>
#include "../include/Cubes.h"
#include "../include/texture_loader.h"

bool isTextureRdy = false;

texture_loader cubes_texture = texture_loader("terrain.png"); //One texture, all cubes
std::vector<Cube*> cubes;

void cubes_initCubes(){
	//cubes.push_back(new Cube(-2.5,2.5,-0.5,1,X_AXIS_ROTATION));
	cubes.push_back(new Cube(-0.5,-0.5,-0.5,1,Y_AXIS_ROTATION));
	//cubes.push_back(new Cube(1.5,-0.5,-0.5,1,Z_AXIS_ROTATION));
	//cubes.push_back(new Cube(-4,-0.5,-6.5,1,Y_AXIS_ROTATION));
	//cubes.push_back(new Cube(6,-0.5,-7,1,Z_AXIS_ROTATION));
	//cubes.push_back(new Cube(7,-0.5,4,1,X_AXIS_ROTATION));
	//cubes.push_back(new Cube(-8,-0.5,-4,1,Y_AXIS_ROTATION));
	//cubes.push_back(new Cube(-4,3.5,-6.5,1,Y_AXIS_ROTATION));
	//cubes.push_back(new Cube(6,3.5,-7,1,Z_AXIS_ROTATION));
	//cubes.push_back(new Cube(7,3.5,4,1,X_AXIS_ROTATION));
	//cubes.push_back(new Cube(-8,3.5,-4,1,Y_AXIS_ROTATION));
}

Cube::Cube(float posX,float posY,float posZ,float size=1,float rotation_angle = NO_ROTATION) :
	posX(posX), posY(posY), posZ(posZ),size(size), rotation_angle(rotation_angle)
{
	isRotating = true;
	rotation_current = 0;
 	if(!isTextureRdy)
 		cubes_texture.initTexture();
}

Cube::Cube(const Cube &other){
	posX = other.posX; posY = other.posY; posZ = other.posZ;
	size = other.size; rotation_angle = other.rotation_angle;
	isRotating = true, rotation_current = 0;
}

Cube::~Cube(){
	//Do a fancy remove dance.
}

void Cube::toggleRotation(){
	isRotating = !isRotating;
}

void Cube::draw(){
	glPushMatrix();
	rotation_current %= 360;
	if(isRotating){
		glTranslatef((size/2)+posX,(size/2)+posY,(size/2)+posZ);
		switch(rotation_angle){
		case NO_ROTATION:
			break;
		case X_AXIS_ROTATION:
			glRotatef(rotation_current,1,0,0);
			break;
		case Y_AXIS_ROTATION:
			glRotatef(rotation_current,0,1,0);
			break;
		case Z_AXIS_ROTATION:
			glRotatef(rotation_current,0,0,1);
			break;
		}
		glTranslatef(-(size/2)-posX,-(size/2)-posY,-(size/2)-posZ);
	}
	glColor3f(1, 1, 1);
	cubes_texture.bindTexture();
	//Texture coordinates assume terrain.png, though the texture image is variable
	glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glNormal3f(0.0f,0.0f,-1.0f);
		cubes_texture.getTexture(0.248, 0.062);
		glVertex3f(posX,posY,posZ);
		cubes_texture.getTexture(0.248, 0.000);
		glVertex3f(posX,posY+size,posZ);
		cubes_texture.getTexture(0.186, 0.000);
		glVertex3f(posX+size,posY+size,posZ);
		cubes_texture.getTexture(0.186, 0.062);
		glVertex3f(posX+size,posY,posZ);

		glNormal3f(0.0f,0.0f,1.0f);
		cubes_texture.getTexture(0.186, 0.062);
		glVertex3f(posX,posY,posZ+size);
		cubes_texture.getTexture(0.186, 0.000);
		glVertex3f(posX,posY+size,posZ+size);
		cubes_texture.getTexture(0.248, 0.000);
		glVertex3f(posX+size,posY+size,posZ+size);
		cubes_texture.getTexture(0.248, 0.062);
		glVertex3f(posX+size,posY,posZ+size);

		glNormal3f(-1.0f,0.0f,0.0f);
		cubes_texture.getTexture(0.186, 0.062);
		glVertex3f(posX,posY,posZ);
		cubes_texture.getTexture(0.248, 0.062);
		glVertex3f(posX,posY,posZ+size);
		cubes_texture.getTexture(0.248, 0.000);
		glVertex3f(posX,posY+size,posZ+size);
		cubes_texture.getTexture(0.186, 0.000);
		glVertex3f(posX,posY+size,posZ);

		glNormal3f(1.0f,0.0f,0.0f);
		cubes_texture.getTexture(0.248, 0.062);
		glVertex3f(posX+size,posY,posZ);
		cubes_texture.getTexture(0.186, 0.062);
		glVertex3f(posX+size,posY,posZ+size);
		cubes_texture.getTexture(0.186, 0.000);
		glVertex3f(posX+size,posY+size,posZ+size);
		cubes_texture.getTexture(0.248, 0.000);
		glVertex3f(posX+size,posY+size,posZ);

		glNormal3f(0.0f,-1.0f,0.0f);
		cubes_texture.getTexture(0.124, 0.062);
		glVertex3f(posX,posY,posZ);
		cubes_texture.getTexture(0.124, 0.000);
		glVertex3f(posX,posY,posZ+size);
		cubes_texture.getTexture(0.186, 0.000);
		glVertex3f(posX+size,posY,posZ+size);
		cubes_texture.getTexture(0.186, 0.062);
		glVertex3f(posX+size,posY,posZ);

		glNormal3f(0.0f,1.0f,0.0f);
		cubes_texture.getTexture(0.000, 0.062);
		glVertex3f(posX,posY+size,posZ);
		cubes_texture.getTexture(0.062, 0.062);
		glVertex3f(posX,posY+size,posZ+size);
		cubes_texture.getTexture(0.062, 0.000);
		glVertex3f(posX+size,posY+size,posZ+size);
		cubes_texture.getTexture(0.000, 0.000);
		glVertex3f(posX+size,posY+size,posZ);
	glEnd();
	glPopMatrix();
}

std::vector<Cube*> cubes_getCubes(){
	return cubes;
}
std::vector<Cube*>* cubes_editCubes(){
	return &cubes;
}
