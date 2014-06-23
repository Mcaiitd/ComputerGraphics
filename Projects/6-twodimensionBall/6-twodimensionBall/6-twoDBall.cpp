#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

#ifndef M_PI
#define M_PI 3.141592654
#endif

static int direction_toggle = 1;

GLfloat WHITE[] = {1, 1, 1};
GLfloat RED[] = {.8, .5, .2};
GLfloat xf= 0.0f;
GLfloat yf = 0.0f;

float xmin = -3.0f;
float xmax = 3.0f;
float ymin = -3.0f;
float ymax = 3.0f;
float z = -1.0f;
float rad = 0.15f;
int c = 0;
float h = 0.9;
int xdir = 1; // right (-1 lft)
int ydir = 1; // up
float speed= 0;
float a = 10;
float damp = 0.5;
int flag = 0;
float xi,yi;
float vx = 0;
float vy = 0;
float v = 20.0;
float xdisp = 0;
float ydisp = 0;

void
display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_LIGHTING);
  glPushMatrix();
  glColor3f(0,1,0);
  glBegin(GL_QUADS);
        glVertex3f(xmin, ymin, z);
        glVertex3f(xmin, ymax, z);
        glVertex3f(xmax, ymax, z);
        glVertex3f(xmax, ymin, z);
    glEnd();
  glColor3f(1, 1, 1);

  glTranslatef(xmin+rad + xi + xdisp , ymin+rad+yi + ydisp,-1.0f); // animate the xdisp and ydisp
    glutSolidSphere(rad, 30 , 30);
  
//                   glTranslatef(0,0,-0.4f);
    
    glPopMatrix();
  glutSwapBuffers();
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
}

void
animate(void)
{
	if(vx > 0  && xdir == 1 && xmin+rad + xi + xdisp < xmax - rad)
	{
		xdisp = xdisp + xdir*vx*.001; // 0.001 = frame rate per second
	}
	if(vx > 0  && xdir == 1 && xmin+rad + xi + xdisp >= xmax - rad)
	{
		xdir = -1;
		vx = damp*vx;
		xdisp = xdisp + xdir*vx*.001;
	}	
	if(vx > 0  && xdir == -1 && xmin+rad + xi + xdisp > xmin + rad)
	{
		xdisp = xdisp + xdir*vx*.001;
	}
	if(vx > 0  && xdir == -1 && xmin+rad + xi + xdisp <= xmin + rad)
	{
		xdir = 1;
		vx = damp*vx;
		xdisp = xdisp + xdir*vx*.001;
	}
	if(vy > 0 && ydir == 1 && ymin+rad + yi + ydisp < ymax - rad)
	{
		ydisp = ydisp + ydir*vy*.001;
	}
	if(vy > 0 && ydir == 1 && ymin+rad + yi + ydisp >= ymax - rad)
	{
		ydir = -1;
		vy = damp*vy;
	}
	if(vy > 0 && ydir == -1 && ymin+rad + yi + ydisp > ymin + rad)
	{
		ydisp = ydisp + ydir*vy*.001;
	}
	if(vy > 0 && ydir == -1 && ymin+rad + yi + ydisp <= ymin + rad)
	{
		ydir = 1;
		vy = damp*vy;
	}

  glutPostRedisplay();
}


void
visibility(int state)
{
  if (state == GLUT_VISIBLE) {
    glutIdleFunc(animate);
  } else {
    glutIdleFunc(NULL);
  }
}

void mouseEvent(int button, int state, int x, int y)
{
float tempH, tempP, tempB;

	xf = (((float)x-400)/400)*3;
	yf = ((300-(float)y)/300)*3; // transform the point of click to our background and 3 is scling factor.

	tempP = yf-(ymin+rad+yi + ydisp);
	tempB = xf-(xmin+rad + xi + xdisp);
	tempH = sqrt((tempP)*(tempP) + (tempB)*(tempB));
	if(tempP<0)
	{
		ydir = -1;
	}
	else
	{
		ydir = 1;
	}
	if(tempB<0)
	{
		xdir = -1;
	}
	else
	{
		xdir = 1;
	}
	tempP = abs(tempP);
	tempB = abs(tempB);

	vx = v*(tempB/tempH);
	vy = v*(tempP/tempH);


}

int main(int argc, char **argv)
{
  int i;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Bouncing ball");
  glutDisplayFunc(display);
  glutVisibilityFunc(visibility);
  glutMouseFunc(mouseEvent);

  glClearColor(1.0,1.0,1.0,1.0);
  glMatrixMode(GL_PROJECTION);
  glFrustum(-1, 1, -1, 1, 2, 6);// range of coordinate axis -- will clip rest

  glMatrixMode(GL_MODELVIEW);
  glTranslatef(0.0, 0.0, -5.0);


  glutMainLoop();
  return 0;
}