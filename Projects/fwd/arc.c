#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

typedef struct
{
float x;
float y;
}CIRCLE;

#define pi 3.142

float red = 0.0;
float blue = 0.0;
float green = 1.0;
int hollow = 0;
float arc_angle = .5*pi;

static GLfloat rotaty=0.0;
static GLfloat rotatx=0.0;
int drag = 0;
int drag_x_origin;
int drag_y_origin;
int mouse_x;
int mouse_y;
int difference_x = 0;
int difference_y = 0;

CIRCLE circle;

float rot = 0;


void createcircle (int k, int r, int h, float theta) {
    glBegin(GL_LINES);
    for (int i = 0; i < 180; i++)
    {
    circle.x = r * cos(i) - h;
    circle.y = r * sin(i) + k;
    glVertex3f(circle.x + k,circle.y - h,0);
    
    circle.x = r * cos(i + 0.1) - h;
    circle.y = r * sin(i + 0.1) + k;
    glVertex3f(circle.x + k,circle.y - h,0);
    }
    glEnd();
}

void drawcircle (float ax, float ay, float ar, float depth, int segments)
{    
    float r,g,b,a;
 
    r = red;
    g = green;
    b = blue;
    a = 1.0;
 
   glColor4f(r, g, b, a);
    float AL_PI = pi;
    float theta = 0.0628;
    //float theta = 2 * AL_PI / float(segments);
    float tangetial_factor = tanf(theta);
    float radial_factor = 1 - cosf(theta);
    
    float x = ax + ar;
    float y = ay;
    
    glBegin(GL_POLYGON);
    for(int ii = 0; ii < segments; ii++)
    {
        glVertex3f(x, y, depth);
       
        float tx = -(y - ay);
       float ty = x - ax;
        
        x += tx * tangetial_factor;
        y += ty * tangetial_factor;
        
        float rx = ax - x;
        float ry = ay - y;
        
       x += rx * radial_factor;
        y += ry * radial_factor;
    }
    glEnd();
    
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void DrawArc(float _x, float _y, float _r, float depth, float start_angle, float d_angle, int segments)
{
    float r,g,b,a;
 
    r = red;
    g = green;
    b = blue;
    a = 1.0;
 
    glColor4f(r, g, b, a);
   
    float real_segments = fabsf(d_angle) / 6.28 * 100.0 + 1;
    
    float theta = d_angle / real_segments;
    float tangetial_factor = tanf(theta);
    float radial_factor = 1 - cosf(theta);
    
    float x = _x + _r * cosf(start_angle);
    float y = _y + _r * sinf(start_angle);
    if (hollow == 1)
        glBegin(GL_LINE_STRIP);
    else 
        glBegin(GL_POLYGON);
    for(int ii = 0; ii < real_segments + 1; ii++)
    {
        glVertex3f(x, y, depth);
        
        float tx = -(y - _y);
        float ty = x - _x;
        
        x += tx * tangetial_factor;
        y += ty * tangetial_factor;
        
        float rx = _x - x;
        float ry = _y - y;
        
        x += rx * radial_factor;
        y += ry * radial_factor;
    }
    glEnd();
    
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}


void display (void) {
    glClearColor (0.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0,0,-20);
    glRotatef(rotaty * 100,0,1,0);
    //glRotatef(rot,1,0,0);
    glRotatef(rotatx * 100,1,0,0);
    difference_x = mouse_x - drag_x_origin;
    difference_y = mouse_y - drag_y_origin;
    glColor3f(red,green,blue);
    DrawArc(0, 0, 5, -1, 0, arc_angle, 100);
    //drawcircle(0,0,5,1, 100);
    /*
    glRotatef(rot,0,1,0);
    glRotatef(rot,1,0,0);
    glRotatef(rot,0,0,1);
    glColor3f(1,0,0);
    createcircle(-2,8,-2);
    glRotatef(rot,0,1,0);
    glRotatef(rot,1,0,0);
    glRotatef(rot,0,0,1);
    glColor3f(0,1,0);
    createcircle(-1,6,-1);
    glRotatef(rot,0,1,0);
    glRotatef(rot,1,0,0);
    glRotatef(rot,0,0,1);
    glColor3f(0,0,1);
    createcircle(2,4,2);
    glRotatef(rot,0,1,0);
    glRotatef(rot,1,0,0);
    glRotatef(rot,0,0,1);
    glColor3f(0,1,1);
    createcircle(1,2,1);
    */
    glutSwapBuffers();
    rot++;
}

void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
    glMatrixMode (GL_MODELVIEW);
}

void move_display(void)
{   
	if (drag) {
		printf("current mouse x: %d\n", mouse_x);
		//int diff = mouse_x - drag_x_origin;
		rotaty = -0.01 * difference_x;
		rotatx = 0.01 * difference_y;
	}
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{   switch(button)
    {   case GLUT_LEFT_BUTTON:
	    //printf("Left button!");
            if(state==GLUT_DOWN) {
		drag = 1;
		printf("======= drag start\n");
		drag_x_origin = x;
		printf("origin: %d\n", drag_x_origin);
		drag_y_origin = y;
	    }
            if(state==GLUT_UP)
            {
		printf("======= drag stop\n");
		//rotaty=0;
		//rotatx=0;
		drag = 0;
	    }
	    break;
        case GLUT_RIGHT_BUTTON:
            if(state==GLUT_DOWN)
                //rotatq=0;
            break;
        default:
            break;
    }
	mouse_x = x;
	mouse_y = y;
}

void mouse_motion (int x, int y) {
	mouse_x = x;
	mouse_y = y;
	glutPostRedisplay();
}

int main (int argc, char **argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("A basic OpenGL Window");

    glutDisplayFunc (display);
    glutMouseFunc (mouse);
    glutMotionFunc(mouse_motion);
    glutIdleFunc (move_display);
    glutReshapeFunc (reshape);
    glutMainLoop ();
    return 0;
}