#include "graphicalhelper.h"
#include <vector>

std::vector<vec2> points = std::vector<vec2>();

void init(void)
{	
	glClearColor(1.0, 1.0, 1.0, 0.0);	// Set display-window color to white.

	glMatrixMode(GL_PROJECTION);		// Set projection parameters.
	gluOrtho2D(0.0, 400.0, 0.0, 300.0);
}

void drawWithVector() {
	glClear(GL_COLOR_BUFFER_BIT);  // Clear display window.

	glColor3f(0.0, 0.4, 0.2);      // Set line segment color to green.
	glBegin(GL_LINES);
	for (vec2 &point : points) {
		glVertex2i(point.x, point.y);       // Specify line-segment geometry.
	}
	glEnd();

	glFlush();     // Process all OpenGL routines as quickly as possible.
}

void drawWithoutVector() {
	glClear(GL_COLOR_BUFFER_BIT);  // Clear display window.

	glColor3f(0.0, 0.4, 0.2);      // Set line segment color to green.
	glBegin(GL_LINES);
	glVertex2i(100, 40);       // Specify line-segment geometry.
	glVertex2i(300, 200);
	glEnd();

	glFlush();     // Process all OpenGL routines as quickly as possible.
}

void setupScene() {
	points.push_back(vec2(100.0, 40.0));
	points.push_back(vec2(300.0, 200.0));
	drawWithVector();
}

void spareIt(){
  
  drawTriangle(vec2(0,0), vec2(0,100), vec2(100,100), true, green);
  
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);                         // Initialize GLUT.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   // Set display mode.
	glutInitWindowPosition(50, 100);   // Set top-left display-window position.
	glutInitWindowSize(400, 400);      // Set display-window width and height.
	glutCreateWindow(""); // Create display window.

	init();  // Execute initialization procedure.
	spareIt();
	glutDisplayFunc(drawWithVector);       // Send graphics to display window.
	//glutDisplayFunc(drawWithoutVector);       // Send graphics to display window.
	glutMainLoop();                    // Display everything and wait.
	return 0;
}
