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
#include <unistd.h> //Test compatibility of unistd.h's sleep with Apple systems
#endif
#ifdef __APPLE__
#include <GLUT/glut.h>
#elif _WIN32
#include <glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <stdio.h>
#include <math.h>

#define X_AXIS_ROTATION 1
#define Y_AXIS_ROTATION 2
#define Z_AXIS_ROTATION 3

#define AsRadian(x) (x*(M_PI/180))

float rotation = 0.0f;
float eyeposVer = 1.2f; //In vertical plane: y
float eyeposHor = 0.0f; //In horizontal plane: x and z
float cameraCenterX = 0.0f;
float cameraCenterY = 0.0f;
float cameraCenterZ = 0.0f;
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
	switch (key)
	{
        case 27:             // ESCAPE key
            exit (0);
            break;
       	case 97:			 //a
        	//cameraCenterX-=0.1f;       /* Move center left, camera will stay in place */ 
       		//Kinda broke it. Sorry Guus. Temporary functions the same as q & e
       		eyeposHor+=1.0f;	
        	if(eyeposHor==180.0f)
       			eyeposHor = 180.0f; /* Turn left */
       		break;
       	case 100:			 //d 
        	//cameraCenterX+=0.1f;		/* Move center right, camera will stay in place */   
        	eyeposHor-=1.0f;	
        	if(eyeposHor==180.0f)
       			eyeposHor = -180.0f; /* Turn right */
       		break;
       	case 119:			 //w
       		eyeposVer-=0.1f;        /* Move up */
       		if(eyeposVer <= 0.1)
       			eyeposVer = 0.1; //Stops invert
       		break;
       	case 115:			 //s
       		eyeposVer+=0.1f;        /* Move down */
			break;
        case 113:            //q
            eyeposHor-=1.0f;	
        	if(eyeposHor==180.0f)
       			eyeposHor = -180.0f;     /* Turn left */
            break;
        case 101:           //e
            eyeposHor+=1.0f;	
        	if(eyeposHor==180.0f)
       			eyeposHor = 180.0f;       /* Turn right */
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
	eyeposVer*cos(AsRadian(eyeposHor)),eyeposVer,eyeposVer*sin(AsRadian(eyeposHor)),   //Assumes camera center == 0
		    	     cameraCenterX,cameraCenterY,cameraCenterZ,
						              0,1,0
						                );

	                       //Lookat art ^
    //CUBE_A======================== 
	gfxDrawCube(-2.5,-0.5,-0.5,1,X_AXIS_ROTATION);
    
    //CUBE_B========================
    gfxDrawCube(-0.5,-0.5,-0.5,1,Y_AXIS_ROTATION);
    
    //CUBE_C========================
    gfxDrawCube(1.5,-0.5,-0.5,1,Z_AXIS_ROTATION);
    
    glLoadIdentity();
    glOrtho(0,glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT), -1, 200);
    glBegin(GL_LINE_LOOP);
    glVertex2f(5, 5);
    glVertex2f(glutGet(GLUT_WINDOW_WIDTH)-5, 5);
    glVertex2f(glutGet(GLUT_WINDOW_WIDTH)-5, glutGet(GLUT_WINDOW_HEIGHT)-5);
    glVertex2f(5, glutGet(GLUT_WINDOW_HEIGHT)-5);
    glEnd();
    
	glutSwapBuffers();
#ifdef _WIN32
	Sleep(10);
#else
	usleep(10);
#endif
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



