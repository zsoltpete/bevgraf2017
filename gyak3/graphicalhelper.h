#ifndef H___BEVGRAFHELPER
#define H___BEVGRAFHELPER

#include "bevgrafmath2017.h"
#include <GL/glut.h>					// (or others, depending on the system in use)
#include <GL/freeglut.h>

enum Color {
  
  none,
  red,
  green,
  blue,
  white,
  black,
  gray,
  purple,
  yellow,
  brown
  
};

inline void setColor(double red, double green, double blue){
  glColor3f(red / 255.0, green / 255.0, blue / 255.0);
}

inline void setColor(Color color){
  switch (color) {
    case red : glColor3f(1.0, 0.0, 0.0); break;
    case green : glColor3f(0.0, 1.0, 0.0); break;
    case blue : glColor3f(0.0, 0.0, 1.0); break;
    case white : glColor3f(0.0, 0.0, 0.0); break;
    case black : glColor3f(1.0, 1.0, 1.0); break;
    case gray : glColor3f(0.1, 0.1, 0.1); break;
    case purple : glColor3f(75.0 / 255.0, 0.0, 130.0 / 255.0); break;
    case yellow : glColor3f(1.0, 1.0, 0.0); break;
    case brown : glColor3f(0.5, 0.0, 0.0); break;
  }
}

inline void drawRect(vec2 point1, vec2 point2, vec2 point3, vec2 point4, bool isFilled = true, Color color = none){
  
	glClear(GL_COLOR_BUFFER_BIT);
	if (isFilled == true) {
	    glBegin(GL_POLYGON);
	}else{
	  glBegin(GL_LINE_LOOP);
	}
	
	if (color != none) {
	  setColor(color);
	}
	glVertex2i(point1.x, point1.y);
	glVertex2i(point2.x, point2.y);
	glVertex2i(point3.x, point3.y);
	glVertex2i(point4.x, point4.y);
	glEnd();
	glFlush(); 
}

inline void drawTriangle(vec2 point1, vec2 point2, vec2 point3, bool isFilled = true, Color color = none){
  
	glClear(GL_COLOR_BUFFER_BIT);
	if (isFilled == true) {
	    glBegin(GL_POLYGON);
	}else{
	  glBegin(GL_LINE_LOOP);
	}
	if (color != none) {
	  setColor(color);
	}
	glVertex2i(point1.x, point1.y);
	glVertex2i(point2.x, point2.y);
	glVertex2i(point3.x, point3.y);
	glEnd();
	glFlush(); 
}
  
  
  

  


#endif 