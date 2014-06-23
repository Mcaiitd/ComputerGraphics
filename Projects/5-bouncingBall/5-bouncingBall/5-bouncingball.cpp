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
GLfloat initX = 0.0f;
GLfloat initY = 0.0f;
int flag = 0;
float xmin = -1.0f;
float xmax = 1.0f;
float ymin = -1.5f;
float ymax = 1.5f;
float z = -1.0f;
float rad = 0.2f;
int c = 0;
float h = 2.0;
int dir = 1;
float speed= 0;
float a = 10;
float damp = 0.9;
int shape = 30;
void
display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_LIGHTING); // disable lighting so that what we define comes ahead and becomes visible.

  glPushMatrix(); // in order to work on identity matrix
  glColor3f(0,1,0);
  glBegin(GL_QUADS);
        glVertex3f(xmin, ymin, -z);
        glVertex3f(xmin, ymin, z);
        glVertex3f(xmax, ymin, z);
        glVertex3f(xmax, ymin, -z);
    glEnd();
	glColor3f(1,0,0);
if(shape == 3)
{glColor3f(0, 0, 1);}

  glTranslatef(0,h+ymin+rad-0.1f,-0.8f);
    glutSolidSphere(rad, 30 , 30);
  

    
    glPopMatrix();
  
	glutSwapBuffers();
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST); // initialise 3d rendering
}

void
animate(void)
{
	if(flag == 1){
if(h>0 && dir == 1)
{
	shape = 30;
	speed = (speed + a*.001);
	h = h - speed*.001*dir;
}
if(h<=0 && dir == 1)
{
	dir = -1;
	shape = 3;
	speed = damp*(speed);// -a*.001);
	h  = h - speed*.001*dir;
}
if(h>=0 && dir == -1 && speed > 0 )
{
	shape = 30;
	speed = speed - a*.001;
	h  = h - speed*.001*dir;
}
if(h>=0 && dir == -1 && speed <= 0 )
{
	dir = 1;
	shape = 30;
	speed = speed + a*.001;
	h  = h - speed*.001*dir;

}
if(h>=0 && h<0.1f)
{shape = 3;}
	}
  glutPostRedisplay();
}

void mouseEvent(int button, int state, int x, int y)
{
switch(button){
case GLUT_LEFT_BUTTON:
flag = 1;
break;

}
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