#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#define TWO_PI	6.283

typedef struct lightRec {
  float amb[4];
  float diff[4];
  float spec[4];
  float pos[4];
  float spotDir[3];
  float spotExp;
  float spotCutoff;
  float atten[3];

  float trans[3];
  float rot[3];
  float swing[3];
  float arc[3];
  float arcIncr[3];
} Light;

static int useSAME_AMB_SPEC = 1;

static float modelAmb[4] = {0.2, 0.2, 0.2, 1.0};

static float matAmb[4] = {0.2, 0.2, 0.2, 1.0};
static float matDiff[4] = {0.8, 0.8, 0.8, 1.0};
static float matSpec[4] = {0.4, 0.4, 0.4, 1.0};
static float matEmission[4] = {0.0, 0.0, 0.0, 1.0};


#define NUM_LIGHTS 2
static Light spots[] =
{
  
  {
    {1, 0.0, 0.0, 1.0},  /* ambient */
    {1, 0.0, 0.0, 1.0},  /* diffuse */
    {1, 0.0, 0.0, 1.0},  /* specular */
    {1.0, 1.0, 0.0, 1.0},  /* position */
    {-1.0, -1.0, 0.0},   /* direction */
    {20.0},
    {60.0},             /* exponent, cutoff */
    {1.0, 0.0, 0.0},    /* attenuation */
    {0.0, 1.25, 0.0},   /* translation */
    {0.0, 0.0, 0.0},    /* rotation */
    {20.0, 0.0, 40.0},  /* swing */
    {0.0, 0.0, 0.0},    /* arc */
    {TWO_PI / 4800.0, 0.0, TWO_PI / 2400.0}  /* arc increment */
  },
{
    {0.0, 1, 0.0, 1.0},  /* ambient */
    {0.0, 1, 0.0, 1.0},  /* diffuse */
    {0.0, 1, 0.0, 1.0},  /* specular */
    {0.0, 0.0, 0.5, 1.0},  /* position */
    {0.0, -1.0, -1.0},   /* direction */
    {20.0},
    {60.0},             /* exponent, cutoff */
    {1.0, 0.0, 0.0},    /* attenuation */
    {0.0, 1.25, 0.0},   /* translation */
    {0.0, 0.0, 0.0},    /* rotation */
    {20.0, 0.0, 40.0},  /* swing */
    {0.0, 0.0, 0.0},    /* arc */
    {TWO_PI / 50.0, 0.0, TWO_PI / 100.0}  /* arc increment */
  }
};

static void
initLights(void)
{
  int k;

  for (k = 0; k < NUM_LIGHTS; ++k) {
    int lt = GL_LIGHT0 + k;
    Light *light = &spots[k];

    glEnable(lt);
    glLightfv(lt, GL_AMBIENT, light->amb);
    glLightfv(lt, GL_DIFFUSE, light->diff);

    glLightfv(lt, GL_SPECULAR, light->amb);

    glLightf(lt, GL_SPOT_EXPONENT, light->spotExp);
    glLightf(lt, GL_SPOT_CUTOFF, light->spotCutoff);
    glLightf(lt, GL_CONSTANT_ATTENUATION, light->atten[0]);
    glLightf(lt, GL_LINEAR_ATTENUATION, light->atten[1]);
    glLightf(lt, GL_QUADRATIC_ATTENUATION, light->atten[2]);
  }
}

static void
aimLights(void)
{
  int k;
  //for (k = 0; k < NUM_LIGHTS; ++k) {
  for (k = 0; k < NUM_LIGHTS-1; ++k) {
    Light *light = &spots[k];

    light->rot[0] = light->swing[0] * sin(light->arc[0]);
    light->arc[0] += light->arcIncr[0];
    if (light->arc[0] > TWO_PI)
      light->arc[0] -= TWO_PI;

    light->rot[1] = light->swing[1] * sin(light->arc[1]);
    light->arc[1] += light->arcIncr[1];
    if (light->arc[1] > TWO_PI)
      light->arc[1] -= TWO_PI;

    light->rot[2] = light->swing[2] * sin(light->arc[2]);
    light->arc[2] += light->arcIncr[2];
    if (light->arc[2] > TWO_PI)
      light->arc[2] -= TWO_PI;
  }
}

static void
setLights(void)
{
  int k;


  for (k = 0; k < NUM_LIGHTS; ++k) {
    int lt = GL_LIGHT0 + k;
    Light *light = &spots[k];

    glPushMatrix();
    glTranslatef(light->trans[0], light->trans[1], light->trans[2]);
    glRotatef(light->rot[0], 1, 0, 0);
    glRotatef(light->rot[1], 0, 1, 0);
    glRotatef(light->rot[2], 0, 0, 1);
    glLightfv(lt, GL_POSITION, light->pos);
    glLightfv(lt, GL_SPOT_DIRECTION, light->spotDir);
    glPopMatrix();
  }
}


static void
drawPlane(int w, int h)
{
  int i, j;
  float dw = 1.0 / w;
  float dh = 1.0 / h;

  glNormal3f(0.0, 0.0, 1.0);
 
  for (j = 0; j < h; ++j) {
    glBegin(GL_TRIANGLE_STRIP);
    for (i = 0; i <= w; ++i) {
      glVertex2f(dw * i, dh * (j + 1));
      glVertex2f(dw * i, dh * j);
    }
    glEnd();
  }
 /* glBegin(GL_QUADS);
        glVertex3f(xmin, ymin, z);
        glVertex3f(xmin, ymax, z);
        glVertex3f(xmax, ymax, z);
        glVertex3f(xmax, ymin, z);
    glEnd();*/
}

int spin = 0;

void
display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();
  glRotatef(spin, 0, 1, 0);

  aimLights();
  setLights();

  glPushMatrix();
  glColor3f(0.0, 0.0, 1);
  glRotatef(-90, 1, 0, 0);
  glScalef(1.9, 1.9, 1.0);
  glTranslatef(-0.5, -0.5, 0);
  drawPlane(30, 30);
  glPopMatrix();

  glutSwapBuffers();
}

void
animate(void)
{
  spin += 0.5;
  if (spin > 360.0)
    spin -= 360.0;
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

int
main(int argc, char **argv)
{
  int i;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutCreateWindow("Spotlight");
  glutDisplayFunc(display);
  glutVisibilityFunc(visibility);

  glMatrixMode(GL_PROJECTION);
  glFrustum(-1, 1, -1, 1, 2, 6);

  glMatrixMode(GL_MODELVIEW);
  glTranslatef(0.0, 0.0, -3.0);
  glRotatef(60.0, 1, 0, 0);

  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);

  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, modelAmb);
  glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

  glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiff);
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
  glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
  glMaterialf(GL_FRONT, GL_SHININESS, 10.0);

  initLights();

  glutMainLoop();
  return 0;
}
