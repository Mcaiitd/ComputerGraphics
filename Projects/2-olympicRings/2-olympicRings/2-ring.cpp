#include <iostream>
#include <stdlib.h>

#include <GL/glut.h>
#include <windows.h>

using namespace std;

//Called when Escape key is pressed
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
	}
}

//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}


//Draws the 3D scene
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(.5f, .5f, .5f, 0.0f);//Background as grey color
	glMatrixMode(GL_MODELVIEW); // enables us to use matrix rotation, translation etc
	glLoadIdentity(); // makes above matrix as identity.


	glTranslatef(0,0,-15);    // translating in z direction upwards
 
 // gluLookAt - 9 parameters , first 3 , my position , next 3 - direction of view ( 3 dimensional view ) , next 3 coming out of my head. 

    glColor3ub(000,000,255);//Blue Color
    glTranslatef(-4,1.85,0);
    glRotatef(8,2,-1.85,0);             
    glutSolidTorus(.1,1.8,118,118);//First Ring

	 glColor3ub(000,000,000);
	   glutSolidTorus(.05,1.9,118,118);//First Ring

 

    glColor3ub(255,255,000);//Yellow Color
    glTranslatef(2,-1.85,0);
    glRotatef(-4,2,-1.85,0);
    glutSolidTorus(.1,1.8, 118,118 );//Second Ring
    glColor3ub(000,000,000);//Black Color
    glTranslatef(2,1.85,0);
    glRotatef(-4,2,1.85,0);
    glutSolidTorus(.1,1.8, 118,118 );//Third Ring
    glColor3ub(000,255,000);//Green Color
    glTranslatef(2,-1.85,0);
    glRotatef(-4,2,-1.85,0);
    glutSolidTorus(.1,1.8, 118,118 );//Fourth Ring
    glColor3ub(255,000,000);//Red Color
    glTranslatef(2,1.85,0);
    glRotatef(-4,2,1.85,0);
    glutSolidTorus(.1,1.8, 118,118 );//Fifth Ring



	glutSwapBuffers(); // brings the back buffer into front
}


int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(768, 768);

	//Create the window
	glutCreateWindow("The Olympic Rings!");
	initRendering();

	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);

	glutMainLoop();
	return 0;
}









