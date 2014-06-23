//Rotating View around a cube with lighting

#include <cstdio>
  using namespace std;
#include <GL/glut.h>

//Global variables

  GLfloat vertices[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
  {1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0},
  {1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

  GLfloat normals[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
  {1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0},
  {1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

  GLfloat colors[][4] = {{1.0,0.0,0.0,1.0},{1.0,0.0,0.0,1.0},
  {1.0,0.0,0.0,1.0}, {1.0,0.0,0.0,1.0}, {1.0,0.0,0.0,1.0},
  {1.0,0.0,0.0,1.0}, {1.0,0.0,0.0,1.0}, {1.0,0.0,0.0,1.0}};

  GLfloat eyeX = 0.0, eyeY = 0.0, eyeZ = 5.0; //Viewing coord origin
  GLfloat atX = 0.0, atY = 0.0, atZ = 0.0; //Look-at point
  GLfloat upX = 0.0, upY = 1.0, upZ = 0.0; //View-up vector

  //Near and far clipping planes
  GLfloat dnear = 2, dfar = 50.0;

void polygon(int a, int b, int c , int d , int e)
{
  GLfloat specularCoeff[] = { 1.0, 1.0, 1.0, 1.0 };

  glBegin(GL_POLYGON);
          //glColor3fv(colors[a]);
          glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, colors[e]);
          glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularCoeff);
          glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 25.0);
          glNormal3fv(normals[a]);
     glVertex3fv(vertices[a]);
          glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, colors[e]);
          glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularCoeff);
          glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 25.0);
          glNormal3fv(normals[b]);
     glVertex3fv(vertices[b]);
          glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, colors[e]);
          glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularCoeff);
          glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 25.0);
          glNormal3fv(normals[c]);
     glVertex3fv(vertices[c]);
          glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, colors[e]);
          glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularCoeff);
          glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 25.0);
          glNormal3fv(normals[d]);
     glVertex3fv(vertices[d]);
  glEnd();
}

void colorcube()
{
  polygon(0,3,2,1,1);
  polygon(2,3,7,6,2);
  polygon(0,4,7,3,3);
  polygon(1,2,6,5,4);
  polygon(4,5,6,7,5);
  polygon(0,1,5,4,6);
}

static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 0;
static GLdouble viewer[]= {eyeX, eyeY, eyeZ}; // initial viewer location

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //Update viewer position in modelview matrix
  glLoadIdentity();
  gluLookAt(viewer[0],viewer[1],viewer[2], atX, atY, atZ, upX, upY, upZ);

  //Rotate Cube
  glRotatef(theta[0], 1.0, 0.0, 0.0);
  glRotatef(theta[1], 0.0, 1.0, 0.0);
  glRotatef(theta[2], 0.0, 0.0, 1.0);      
  //Display Cube        
  colorcube();
  
  glFlush();
  glutSwapBuffers();
}

//Uses mouse to rotate cube
void mouse(int btn, int state, int x, int y)
{
  if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
  if(btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
  if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
  theta[axis] += 2.0;
  if( theta[axis] > 360.0 ) theta[axis] -= 360.0;
  display();
}

//Uses cursor, page up and page down keys to move camera
void specialKeys(int specialkey, int x, int y)
{
  if(specialkey == GLUT_KEY_LEFT) viewer[0]-= 1.0;
  if(specialkey == GLUT_KEY_RIGHT) viewer[0]+= 1.0;
  if(specialkey == GLUT_KEY_UP) viewer[1]+= 1.0;
  if(specialkey == GLUT_KEY_DOWN) viewer[1]-= 1.0;
  if(specialkey == GLUT_KEY_PAGE_UP) viewer[2]+= 1.0;
  if(specialkey == GLUT_KEY_PAGE_DOWN) viewer[2]-= 1.0;
  display();
}

void myReshape(int w, int h)
{
   glViewport(0, 0, w, h);
  //Use a perspective view
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if(w<=h)
  {
          glFrustum(-2.0, 2.0, -2.0 * (GLfloat) h/ (GLfloat) w, 2.0* (GLfloat) h / (GLfloat) w, dnear, dfar);
  }
  else
  {
          glFrustum(-2.0, 2.0, -2.0 * (GLfloat) w/ (GLfloat) h, 2.0* (GLfloat) w / (GLfloat) h, dnear, dfar);
  }
  glMatrixMode(GL_MODELVIEW);
}

void Lights(void)
{
  //Light source
  GLfloat light1PosType[] = { 100.0, 0.0, 0.0, 1.0 };
  GLfloat ambientColor[] = { 0.0, 0.0, 0.0, 1.0 };
  GLfloat diffuseColor[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat specularColor[] = { 1.0, 1.0, 1.0, 1.0 };
  //Light colours
  glLightfv(GL_LIGHT1, GL_AMBIENT, ambientColor);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseColor);
  glLightfv(GL_LIGHT1, GL_SPECULAR, specularColor);
  //Light attenuation
  glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5-1);
  glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.75-0.75);
  glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.4+0.6);
  //Switch light on!
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHTING);
}

int main(int argc, char **argv)        //Entry point for program
{
  //Initialise OpenGL Window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutCreateWindow("colorcube");

  //Reshape Window if Requested without too much distortion!
   glutReshapeFunc(myReshape);

  //Switch one lights-
   //Lights();

  //Display Graphic
   glutDisplayFunc(display);
   display();

  //Get input from user
   glutMouseFunc(mouse);
   //glutSpecialFunc(specialKeys);

   glEnable(GL_DEPTH_TEST);

  //Main program loop - wait for input and maintain display
   glutMainLoop();
 return 0;
}
