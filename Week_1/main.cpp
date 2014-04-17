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

void gfxDrawCube(int posX, int posY, int posZ){
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
	glPushMatrix();
    glTranslatef(0.5,0.5,0.5);
	glRotatef(rotation,1,0,0);
	glTranslatef(-0.5,-0.5,-0.5);
    
    
	gfxDrawCube(-2,0,0);
    glPopMatrix();
    //============================
    glPushMatrix();
    glTranslatef(0.5,0.5,0.5);
	glRotatef(rotation,0,1,0);
	glTranslatef(-0.5,-0.5,-0.5);
    
    gfxDrawCube(0,0,0);
    glPopMatrix();
    //============================
    glPushMatrix();
    glTranslatef(2.5,0.5,0.5);
	glRotatef(rotation,0,0,1);
	glTranslatef(-2.5,-0.5,-0.5);
    
    gfxDrawCube(2,0,0);
    glPopMatrix();
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



