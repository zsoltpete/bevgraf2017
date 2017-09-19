#include <GL/glut.h>
#include "bevgrafmath2017.h"

vec2 points[4] = { { 100.0, 100.0 } ,{ 200.0, 150.0 },{ 300.0, 175.0 },{ 350.0, 50.0 } };

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 400.0, 0.0, 300.0);
}

GLfloat* vecToArray(vec2 vector) {
	GLfloat p[2] = { vector.x, vector.y };
	return p;
}

void display() {
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	glBegin(GL_LINE_LOOP);
	for (i = 0; i < 4; i++)
		glVertex2fv(vecToArray(points[i]));
	glEnd();

	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(400, 300);
	glutCreateWindow("Polygon");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
