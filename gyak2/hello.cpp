#include <GL/glut.h>					// (or others, depending on the system in use)
#include <GL/freeglut.h>
#include "bevgrafmath2017.h"
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

void drawHouse(){
  glClear(GL_COLOR_BUFFER_BIT);  // Clear display window.

	glColor3f(0.0, 0.4, 0.2);      // Set line segment color to green.
	glBegin(GL_POLYGON);
	glVertex2i(0, 0);       // Specify line-segment geometry.
	glVertex2i(0, 10);
	glVertex2i(400, 10);
	glVertex2i(400, 0);
	glEnd();
	
	glColor3f(0.1, 0.1, 0.1); 
	
	glBegin(GL_POLYGON);
	glVertex2i(50, 10);       // Specify line-segment geometry.
	glVertex2i(50, 100);
	glVertex2i(150, 100);
	glVertex2i(150, 10);
	glEnd();
	
	glColor3f(1.0, 0.0, 0.0); 
	
	glBegin(GL_POLYGON);
	glVertex2i(50, 100);       // Specify line-segment geometry.
	glVertex2i(100, 150);
	glVertex2i(150, 100);
	glEnd();

	glFlush();  
  
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);                         // Initialize GLUT.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   // Set display mode.
	glutInitWindowPosition(50, 100);   // Set top-left display-window position.
	glutInitWindowSize(400, 300);      // Set display-window width and height.
	glutCreateWindow("An Example OpenGL Program"); // Create display window.

	init();                         // Execute initialization procedure.
	//setupScene();
	drawHouse();
	glutDisplayFunc(drawWithVector);       // Send graphics to display window.
	//glutDisplayFunc(drawWithoutVector);       // Send graphics to display window.
	glutMainLoop();                    // Display everything and wait.
	return 0;
}
