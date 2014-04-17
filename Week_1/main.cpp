//
//  main.cpp
//  OpdrachtenWeek1
//
//  Created by Guus Beckett and Julian West on 17-04-14.
//  Copyright (c) 2014 reupload.nl. All rights reserved.
//
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <stdio.h>

void onDisplay(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	printf("test\n");
	glutSwapBuffers();
}

void Display(void)
{
	glutSwapBuffers();
}

void Reshape(GLint width, GLint height)
{
}

void InitGraphics(void)
{
}

void MouseButton(int button, int state, int x, int y)
{
}

void MouseMotion(int x, int y)
{
}

void IdleFunc(void)
{
    glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
        case 27:             // ESCAPE key
            exit (0);
            break;
	}
}


int main(int argc, char * argv[])
{
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutInit(&argc, argv);
    glutCreateWindow("Hello Guus & Julian");
 	glutDisplayFunc(onDisplay);
    glutMainLoop();
}



