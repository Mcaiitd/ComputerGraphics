#include <GL/glut.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
 
#define WIDTH 480
#define HEIGHT 480
 
int direction = 0;
// direction is 0 for 
 
void reshape(int width, int height){
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WIDTH/2,WIDTH/2-1,-HEIGHT/2,HEIGHT/2-1,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
 
void init(void){
	glClearColor(0.0,0.0,1.0,0.0);
	glPointSize(2.0);
}
 
void Timer(int ex)
{
	glutPostRedisplay();
	glutTimerFunc(50,Timer,0);
}
 
int k=-200;
int l=0;
void circle(int p,int q,int m)
{
	int x=0,y,d,r;
	r=m;
	y=r;
	d=3-2*r;
	while(x<=y)
	{
		glVertex2i(x+q,y+p);
		glVertex2i(y+q,x+p);
		glVertex2i(-x+q,y+p);
		glVertex2i(-y+q,x+p);
		glVertex2i(-x+q,-y+p);
		glVertex2i(-y+q,-x+p);
		glVertex2i(y+q,-x+p);
		glVertex2i(x+q,-y+p);
		
		if(d<0)
			d=d+4*x+6;
		else
		{
			d=d+4*(x-y)+10;
			y--;
		}

		x++;
	}
}
 
int r=40,flag=-1;
 
void display(void)
{

	/*
	flag = 0 => going up
	flag = 1 => going down
	flag = -1 => stop at bottom
	*/
 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor4f(0.0,1.0,0.0,1.0);
	glBegin(GL_POINTS);
 
 
	circle(k,l,r);
 
 
	if(flag==0)
	{
		if((k+r)<=240)
		{
			k=k+10;
 
		}
 
		if((k+r)>=240){
			flag=1;
 
		}
	}
 
	if(flag==1)
	{
		k=k-10;
 
 
		if((k-r)<=-240)
		{
			flag=-1;
			//if(r!=10)
				//r=r-10;
		}
	}
 
	glEnd();
	glutSwapBuffers();
 
}

void mouse(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON:
        	printf("%d, %d\n", x, y);
            if (x <= 280 && x >= 200 && y <= 480 && y >= 400) {
            	printf("hurrah!\n");
            	flag = 0;
            }
            break;
        case GLUT_RIGHT_BUTTON:
            exit(0);
            break;
    }
}
 
void idle(void){
/* do nothing */
}
 
int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(WIDTH,HEIGHT);
	glutCreateWindow(argv[0]);
	init();
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutDisplayFunc(display);
	glutTimerFunc(0,Timer,0);
	glutMainLoop();
	return(1);
}
