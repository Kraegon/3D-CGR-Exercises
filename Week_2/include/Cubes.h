/*
 * cubes.h
 *
 *  Created on: Jun 19, 2014
 *      Author: Julian G. West
 */

#ifndef CUBES_H_
#define CUBES_H_

#include <vector>

#define NO_ROTATION     0
#define X_AXIS_ROTATION 1
#define Y_AXIS_ROTATION 2
#define Z_AXIS_ROTATION 3

void cubes_initCubes();

class Cube{
public:
	float posX,posY,posZ,size;
	int rotation_angle,rotation_current;
	bool isRotating;

	Cube(float,float,float, float,float); //YOU FLOATING YET?
	Cube(const Cube&);
	~Cube();

	void draw();
};

std::vector<Cube*> cubes_getCubes();
std::vector<Cube*>* cubes_editCubes();

#endif /* CUBES_H_ */
