#include "graphicalhelper.h"


GLint novX = 1;
GLint halfSize = 50;
vec2 center = { 200, 200 };
Color rectColor = blue;


GLint dragged = -1;

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 400.0, 0.0, 400.0);
	glShadeModel(GL_FLAT);
	glPointSize(10.0);
	glEnable(GL_POINT_SMOOTH);
}

void display()
{
  if ((center.x > 0) && (center.x < 400) && (center.y > 0) && (center.y < 400)) {
    glClear(GL_COLOR_BUFFER_BIT);
	
	setColor(rectColor);
	glRecti(center[0] - halfSize, center[1] - halfSize, center[0] + halfSize, center[1] + halfSize);
	setColor(red);
	glBegin(GL_POINTS);
		glVertex2f(center.x, center.y);
	glEnd();
	glutSwapBuffers();
  }
	
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	case 'r':
		rectColor = red;
		break;
	case 'g':
		rectColor = green;
		break;
	case 'b':
		rectColor = blue;
		break;
	case 'w':
		halfSize += 1;
		break;
	case 's':
		halfSize -= 1;
		break;
	}
	glutPostRedisplay();
}

GLint getActivePoint1(vec2 p, GLint size, GLint sens, GLint x, GLint y) {
	GLint i, s= sens * sens;
	vec2 P = { (float)x, (float)y };

	for (i = 0; i < size; i++)
		if (dist(p, P) < s)
			return i;
	return -1;
}

void processMouse(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	GLint i;
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
		if ((i = getActivePoint1(center, 4, 8, xMouse, 400 - yMouse)) != -1)
			dragged = i;
	if (button == GLUT_LEFT_BUTTON && action == GLUT_UP)
		dragged = -1;
}

void processMouseActiveMotion(GLint xMouse, GLint yMouse) {
	GLint i;
	if (dragged >= 0) {
		center.x = xMouse;
		center.y = 400 - yMouse;
		glutPostRedisplay();
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutMouseFunc(processMouse);
	glutMotionFunc(processMouseActiveMotion);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
