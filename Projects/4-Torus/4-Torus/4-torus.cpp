#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

#ifndef M_PI
#define M_PI 3.141592654
#endif

static int direction_toggle = 1;

float spin = 0;

void circle(float x, float y, float r, int segments)
{
    glBegin( GL_TRIANGLE_FAN );
        glVertex2f(x, y);
        for( int n = 0; n <= segments; ++n ) {
            float const t = 2*M_PI*(float)n/(float)segments;
			if(t>=0 && t<=2*M_PI+M_PI/5) {
				glVertex2f(x + sin(t)*r, y + cos(t)*r);
			}
        }
    glEnd();

}

void
display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_LIGHTING);

  glPushMatrix();
  glRotatef(spin, 0, 1, 0); // rotating with variable parameter about y axis.

  glColor3f(.1, .5, .8);
  //glutSolidTorus(0.1, 1, 15, 30);
  circle(0.0, 0.0, 1, 100);
  
  glPopMatrix();
  
  glutSwapBuffers();
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
}

void
animate(void)
{
 // spin += direction_toggle*1;
 // if (spin > 360.0)
 //   spin -= 360.0;
 // else if (spin < 0.0)
 //	spin += 360.0;
  
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
switch(button){
case GLUT_LEFT_BUTTON:
	spin = spin + 10;
//direction_toggle = -1;
break;
case GLUT_RIGHT_BUTTON:
	 spin = spin - 10;
//direction_toggle = 1;
break;
};
}

int
main(int argc, char **argv)
{
  int i;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(800, 800);
  glutCreateWindow("Rotating object");
  glutDisplayFunc(display);
  glutVisibilityFunc(visibility);
  glutMouseFunc(mouseEvent);

  glClearColor(1.0,1.0,1.0,1.0);
  glMatrixMode(GL_PROJECTION);
  glFrustum(-1, 1, -1, 1, 2, 6);

  glMatrixMode(GL_MODELVIEW);
  glTranslatef(0.0, 0.0, -5.0);

  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);

  
  glutMainLoop();
  return 0;
}
