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

#define X_AXIS_ROTATION 1
#define Y_AXIS_ROTATION 2
#define Z_AXIS_ROTATION 3

float rotation = 0.0f;
float eyeposVer = 0.0f;
float eyeposHor = 0.0f;

void gfxDrawCube(int posX, int posY, int posZ, int angle){
	glPushMatrix();
    glTranslatef(0.5+posX,0.5+posY,0.5+posZ);
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
	glTranslatef(-0.5-posX,-0.5-posY,-0.5-posZ);
    
	glBegin(GL_QUADS);
		glColor3f(1,1,0);
		glVertex3f(posX,posY,posZ);
		glVertex3f(posX,posY+1,posZ);
		glVertex3f(posX+1,posY+1,posZ);
		glVertex3f(posX+1,posY,posZ);
		
		glColor3f(0,1,0);
		glVertex3f(posX,posY,posZ+1);
		glVertex3f(posX,posY+1,posZ+1);
		glVertex3f(posX+1,posY+1,posZ+1);
		glVertex3f(posX+1,posY,posZ+1);

		glColor3f(0,0,1);
		glVertex3f(posX,posY,posZ);
		glVertex3f(posX,posY,posZ+1);
		glVertex3f(posX,posY+1,posZ+1);
		glVertex3f(posX,posY+1,posZ);

		glColor3f(1,0,0);		
		glVertex3f(posX+1,posY,posZ);
		glVertex3f(posX+1,posY,posZ+1);
		glVertex3f(posX+1,posY+1,posZ+1);
		glVertex3f(posX+1,posY+1,posZ);

		glColor3f(0,1,1);
		glVertex3f(posX,posY,posZ);
		glVertex3f(posX,posY,posZ+1);
		glVertex3f(posX+1,posY,posZ+1);
		glVertex3f(posX+1,posY,posZ);

		glColor3f(1,1,1);
		glVertex3f(posX,posY+1,posZ);
		glVertex3f(posX,posY+1,posZ+1);
		glVertex3f(posX+1,posY+1,posZ+1);
		glVertex3f(posX+1,posY+1,posZ);
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

void IdleFunc(void)
{
	rotation++;
	//rotation%=360.0f;
    glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	printf("Key %d pressed!\n", key);
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

void onDisplay(){	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	         gluLookAt(
		eyeposHor,eyeposVer,2, 	
			 0.5,0.5,0.5, 	
			    0,1,0
			      );

    //CUBE_A======================== 
	gfxDrawCube(-2,0,0,X_AXIS_ROTATION);
    //CUBE_B========================
    gfxDrawCube(0,0,0,Y_AXIS_ROTATION);
    //CUBE_C========================
    gfxDrawCube(2,0,0,Z_AXIS_ROTATION);

	glutSwapBuffers();
}

int main(int argc, char * argv[])
{
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInit(&argc, argv);
    glutCreateWindow("Hello Guus & Julian");
	printf("Programme started!");
    InitGraphics();
	glutDisplayFunc (onDisplay);
	glutReshapeFunc (Reshape);
	glutKeyboardFunc (Keyboard);
	glutMouseFunc (MouseButton);
	glutMotionFunc (MouseMotion);
	glutIdleFunc (IdleFunc);
    glutMainLoop();
}



