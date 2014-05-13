//
//  main.cpp
//  VoronoiDiagram
//
//  Created by Olivier Godin on 2013-05-11.
//
//

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/glut.h>
#endif

#include <iostream>
#include <math.h>
#include <algorithm>
#include <time.h>

#include "DCEL.h"

#define GLUT_DISABLE_ATEXIT_HACK

GLint windowWidth = 500;
GLint windowHeight = 500;

void init();
void display();
void reshape(int width, int height);
void mouseButton(int button, int state, int x, int y);
void drawControlPoints();
void drawVoronoiDiagram();
void drawEdges();

int main(int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitWindowPosition (100, 100);
    glutInitWindowSize (windowWidth, windowHeight);
	glutInitDisplayMode (GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow ("VoronoiDiagram");
	
	glutDisplayFunc(display);
    glutMouseFunc(mouseButton);
	glutReshapeFunc(reshape);
    init();
    
	glutMainLoop();
	
	return 0;
}

void init()
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glViewport( 0,0, windowWidth, windowHeight );
	glMatrixMode( GL_PROJECTION );
	glOrtho( 0.0, windowWidth, 0.0, windowHeight, 1.0, -1.0 );
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouseButton( int button, int state, int x, int y )
{
	if(state == GLUT_DOWN)
	{
        GLfloat pixels[3];
        glReadPixels(x, windowHeight - y, 1, 1, GL_RGB, GL_FLOAT, &pixels);
        
        if(pixels[0] != 0.0 || pixels[1] != 0.0 || pixels[2] != 0.0)
        {
            return;
        }
	}
	glutPostRedisplay();
}

void display (void)
{
    glViewport(0, 0, windowWidth, windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-windowWidth/2.0,windowWidth/2.0,-windowHeight/2.0,windowHeight/2.0);
	glMatrixMode(GL_MODELVIEW);
    
    glClearColor (0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	
    glFlush();
	glutSwapBuffers();
}

void reshape (int m_width, int m_height)
{
	glViewport(0, 0, (GLsizei)m_width, (GLsizei)m_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
}
