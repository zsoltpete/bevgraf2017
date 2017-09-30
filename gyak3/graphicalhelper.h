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

inline void drawPoint(vec2 point, Color color = none){
  
  if (color != none) {
      setColor(color);
  }
  glBegin(GL_POINTS);
    glVertex2f(point.x, point.y);
  glEnd();
  
}

/*
 * point1, point2, point3, point4: Az alakzat sarkait reprezentáló pontok 
 * isFilled: Legyen-e kitöltve a háromsz9g vagy nem
 * color: Háromszög színe
 */

inline void drawRect(vec2 point1, vec2 point2, vec2 point3, vec2 point4, bool isFilled = true, Color color = none){
  
	//glClear(GL_COLOR_BUFFER_BIT);
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
	//glFlush(); 
}

/*
 * bottomLeft: Bal alsó sarok pontja
 * topRight: Jobb felső sarokban lévő pont
 * color: Alakzat színe
 */

inline void drawRect(vec2 bottomLeft, vec2 topRight, Color color = none){
  
  glClear(GL_COLOR_BUFFER_BIT);
  if (color != none) {
    setColor(color);
  }
  glRecti(bottomLeft.x, bottomLeft.y, topRight.x, topRight.y);
  
}

/*
 * center: Alakzat közepét reprezentáló pont
 * halfSize: Alakzat fele
 * color: Alakzat színe
 */

inline void drawRect(vec2 center, GLfloat halfSize, Color color = none){
  
  glClear(GL_COLOR_BUFFER_BIT);
  if (color != none) {
    setColor(color);
  }
  glRecti(center.x - halfSize, center.y - halfSize, center.x + halfSize, center.y + halfSize);
  
}

/*
 * point1, point2, point3: A háromszög sarkait reprezentáló pontok 
 * isFilled: Legyen-e kitöltve a háromsz9g vagy nem
 * color: Háromszög színe
 */

inline void drawTriangle(vec2 point1, vec2 point2, vec2 point3, bool isFilled = true, Color color = none){
  
	//glClear(GL_COLOR_BUFFER_BIT);
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
	//glFlush(); 
}

/*
 * p: ellenőrésre váró pont
 * size: optional: itt mindig egy legyen
 * sens: A pont és az egér kattintás közötti érzékenységre vonatkozik
 * x: Egér x koordináta
 * y: Egér y koordináta 
 * return: -1 ha nem az ellenőrzött pontra kattintott, 1 ha igen
 */
GLint getActivePoint(vec2 p, GLint size, GLint sens, GLint x, GLint y) {
	GLint i, s= sens * sens;
	vec2 P = { (float)x, (float)y };
	for (i = 0; i < size; i++)
		if (dist(p, P) < s)
			return i;
	return -1;
}

#endif 