
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <GL/glut.h>

using namespace std;

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = {0,1,4,1};
int windowWidth = 640, windowHeight = 480;
double yRot = 0;
int curProblem = 1; 

float specular[] = { 1.0, 1.0, 1.0, 1.0 };
float shininess[] = { 50.0 };

void problem1() {
	for(int i=0;i<10;i++)
	{	glPushMatrix();
		glTranslatef(cos(i*36*3.14/180),sin(i*36*3.14/180),0); //10 teapots shown in the graph, so assume we have a polar coordinate system with radius 1. Starts from 3 o'clock, rotates 										   //countercolckwise, so the coordinate for each teapot is (1,360/10*0),(1,360/10*1),......(1,360/10*9), transfer to x-y coordinate
									//iti becomes (cos angle, sin angle) where angle stands for the angle of each teapot, and since sin, cos in cmath use arc system,
									//transfer it as cos(degree*pi/180) and sin(degree*pi/180).
		glRotatef(i*36,0,0,1);	//Rotates over z-axis(0,0,1), and the 10 teapots rotate 0,36,72,108,......,288,324 degrees.
		glutSolidTeapot(0.25);
		glPopMatrix();
	}
}

void problem2() {
	for(int i=0;i<=8;i++) // left part
	{
		glPushMatrix();
		glScalef(1,pow(2,0.4*(2.4-0.3*i)),1);	//Scaling cubes only on y-axis. Since the top is not a stright line, I use the curve of an exponential function to represent the top.
		glTranslatef(-0.3*i,0.15,0);		//Move the scaled cubes on x-axis 0.3*i each time to let them stand adjacent to each other, and move each 0.15 on y-axis to align their bottom.
		glutSolidCube(0.3);
		glPopMatrix();
	}
	for(int i=0;i<=8;i++) // right part
	{
		glPushMatrix();
		glScalef(1,pow(2,0.4*(2.4+0.3*i)),1);
		glTranslatef(0.3*i,0.15,0);
		glutSolidCube(0.3);
		glPopMatrix();
	}
	
}

void problem3() {
    	for(int i=0;i<=5;i++)				//Similar method to print a pascal triangle.
	{
		glPushMatrix();
		glTranslatef(-0.6*i,1.2-i*0.6,0);      //Starts from the middle teapot on the third row, make translate each time to let teapot starts on the front of each row.
		for(int j=0;j<=i;j++)		
		{	
			glutSolidTeapot(0.3);
			glTranslatef(1.2,0,0);		// Increment by 1() when number of rows grow by 1
		}
		glPopMatrix();
	}
}

void problem4(){					//The previouw problems are all doing reproduction on xy plane, so I decided to make use of z-axis in problem 4, to create a pyramid.
	for(int i=0;i<=5;i++)				//It's retrieved from problem 3, and also use the middle teapot of the 3rd layer (row3 column3) as the origin of coordinate system.
	{						//Change teapot to Cubes.
		glPushMatrix();
		glTranslatef(-0.6*i,1.2-i*0.6,-0.6*i);
		for(int j=0;j<=i;j++)
		{
			glPushMatrix();
			glTranslatef(0,0,1.2*j);
			for(int k=0;k<=i;k++)
				{
					glutSolidCube(0.3);
					glTranslatef(1.2,0,0);	
				}
			glTranslatef(-1.2*(i+1),0,0);
			glPopMatrix();
		}
		glPopMatrix();
	}
	glBegin(GL_POLYGON);			//Having 4 triangles covers the 4 side-planes, fit in its coordinates.
	glVertex3f(0,1.2,0);
	glVertex3f(-3,-1.8,-3);
	glVertex3f(3,-1.8,-3);
	glVertex3f(3,-1.8,3);
	glVertex3f(-3,-1.8,3);
	glVertex3f(-3,-1.8,-3);
	glEnd();
	glBegin(GL_POLYGON);		//Base of Pyramid, also fit in its coordinates.
	glVertex3f(3,-1.8,3);
	glVertex3f(3,-1.8,-3);
	glVertex3f(-3,-1.8,3);
	glVertex3f(-3,-1.8,-3);
	glEnd();			//Zoom in to see its inner structure.
}

void display() {
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_LINES);
		glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(1,0,0); // x axis
		glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,1,0); // y axis
		glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,1); // z axis
	glEnd(/*GL_LINES*/);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,windowWidth,windowHeight);

	float ratio = (float)windowWidth / (float)windowHeight;
	gluPerspective(50, ratio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

	glRotatef(yRot,0,1,0);

	if (curProblem == 1) problem1();
	if (curProblem == 2) problem2();
	if (curProblem == 3) problem3();
	if (curProblem == 4) problem4();

	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) leftDown = (state == GLUT_DOWN);
	else if (button == GLUT_RIGHT_BUTTON) rightDown = (state == GLUT_DOWN);

	lastPos[0] = x;
	lastPos[1] = y;
}

void mouseMoved(int x, int y) {
	if (leftDown) yRot += (x - lastPos[0])*.1;
	if (rightDown) {
		for (int i = 0; i < 3; i++)
			cameraPos[i] *= pow(1.1,(y-lastPos[1])*.1);
	}


	lastPos[0] = x;
	lastPos[1] = y;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	curProblem = key-'0';
    if (key == 'q' || key == 'Q' || key == 27){
        exit(0);
    }
	glutPostRedisplay();
}

void reshape(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("HW2");

	glutDisplayFunc(display);
	glutMotionFunc(mouseMoved);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}

