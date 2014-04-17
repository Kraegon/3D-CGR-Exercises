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
float eyeposDepth = 2.0f;
float cameraCenterX = 0.5f;
float cameraCenterY = 0.5f;
float cameraCenterZ = 0.5f;
bool rotating = true;
bool fullScreen = false;

void gfxDrawCube(float posX, float posY, float posZ, float size, int angle){
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
    
	glBegin(GL_QUADS);
		glColor3f(1,1,0);
		glVertex3f(posX,posY,posZ);
		glVertex3f(posX,posY+size,posZ);
		glVertex3f(posX+size,posY+size,posZ);
		glVertex3f(posX+size,posY,posZ);
		
		glColor3f(0,1,0);
		glVertex3f(posX,posY,posZ+size);
		glVertex3f(posX,posY+size,posZ+size);
		glVertex3f(posX+size,posY+size,posZ+size);
		glVertex3f(posX+size,posY,posZ+size);

		glColor3f(0,0,1);
		glVertex3f(posX,posY,posZ);
		glVertex3f(posX,posY,posZ+size);
		glVertex3f(posX,posY+size,posZ+size);
		glVertex3f(posX,posY+size,posZ);

		glColor3f(1,0,0);		
		glVertex3f(posX+size,posY,posZ);
		glVertex3f(posX+size,posY,posZ+size);
		glVertex3f(posX+size,posY+size,posZ+size);
		glVertex3f(posX+size,posY+size,posZ);

		glColor3f(0,1,1);
		glVertex3f(posX,posY,posZ);
		glVertex3f(posX,posY,posZ+size);
		glVertex3f(posX+size,posY,posZ+size);
		glVertex3f(posX+size,posY,posZ);

		glColor3f(1,1,1);
		glVertex3f(posX,posY+size,posZ);
		glVertex3f(posX,posY+size,posZ+size);
		glVertex3f(posX+size,posY+size,posZ+size);
		glVertex3f(posX+size,posY+size,posZ);
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

void IdleFunc(void)
{
    if (rotating) {
        rotation++;
    }
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
        	eyeposHor+=0.1f;        /* Move left */
       		break;
       	case 100:			 //d 
        	eyeposHor-=0.1f;        /* Move right */
       		break;
       	case 119:			 //w
       		eyeposVer+=0.1f;        /* Move up */
       		break;
       	case 115:			 //s
       		eyeposVer-=0.1f;        /* Move down */
			break;
        case 113:            //q
            eyeposDepth+=0.1f;      /* Zoom in */
            break;
        case 101:           //e
            eyeposDepth-=0.1f;      /* Zoom out */
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
		eyeposHor,eyeposVer,eyeposDepth,
			 cameraCenterX,cameraCenterY,cameraCenterZ,
			    0,0.001,0
			      );

    //CUBE_A======================== 
	gfxDrawCube(-2,0,0,1,X_AXIS_ROTATION);
    
    //CUBE_B========================
    gfxDrawCube(0,0,0,1,Y_AXIS_ROTATION);
    
    //CUBE_C========================
    gfxDrawCube(2,0,0,1,Z_AXIS_ROTATION);
    
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

int main(int argc, char * argv[])
{
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInit(&argc, argv);
    glutCreateWindow("Hello Guus & Julian");
	printf("Program started!");
    InitGraphics();
	glutDisplayFunc (onDisplay);
	glutReshapeFunc (Reshape);
	glutKeyboardFunc (Keyboard);
	glutMouseFunc (MouseButton);
	glutMotionFunc (MouseMotion);
	glutIdleFunc (IdleFunc);
    glutMainLoop();
}



