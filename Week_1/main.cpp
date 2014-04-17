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

float rotation = 0.0f;
float eyeposVer = 0.0f;
float eyeposHor = 0.0f;


void onDisplay(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(eyeposHor,eyeposVer,2, 	//Eye
			  0,0,0, 	//Center
			  0,1,0);	//Up

	glRotatef(rotation,0,0,1);
	glBegin(GL_QUADS);
		glVertex3f(0,0,0);
		glVertex3f(0,1,0);
		glVertex3f(1,1,0);
		glVertex3f(1,0,0);

		glVertex3f(0,0,1);
		glVertex3f(0,1,1);
		glVertex3f(1,1,1);
		glVertex3f(1,0,1);

		glVertex3f(0,0,0);
		glVertex3f(0,0,1);
		glVertex3f(0,1,1);
		glVertex3f(0,1,0);

		glVertex3f(1,0,0);
		glVertex3f(1,0,1);
		glVertex3f(1,1,1);
		glVertex3f(1,1,0);

		glVertex3f(0,0,0);
		glVertex3f(0,0,1);
		glVertex3f(1,0,1);
		glVertex3f(1,0,0);

		glVertex3f(0,1,0);
		glVertex3f(0,1,1);
		glVertex3f(1,1,1);
		glVertex3f(1,1,0);
	glEnd();

	glutSwapBuffers();
}

void Display(void)
{
	glutSwapBuffers();
}

void Reshape(GLint width, GLint height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,width/height,1,100);
	glMatrixMode(GL_MODELVIEW);
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
	rotation++;
    glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	printf("%d\n", key);
	switch (key)
	{
        case 27:             // ESCAPE key
            exit (0);
            break;
       	case 97:			 //a 
        	eyeposHor+=0.1f;
       		break;
       	case 100:			 //d 
        	eyeposHor-=0.1f;
       		break;
       	case 119:			 //w
       		eyeposVer+=0.1f;
       		break;
       	case 115:			 //s
       		eyeposVer-=0.1f;
			break;
	}
}


int main(int argc, char * argv[])
{
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutInit(&argc, argv);
    glutCreateWindow("Hello Guus & Julian");	
	glutDisplayFunc (onDisplay);
	glutReshapeFunc (Reshape);
	glutKeyboardFunc (Keyboard);
	glutMouseFunc (MouseButton);
	glutMotionFunc (MouseMotion);
	glutIdleFunc (IdleFunc);
    glutMainLoop();
}



