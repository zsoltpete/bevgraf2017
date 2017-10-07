#ifndef H___BEVGRAFHELPER
#define H___BEVGRAFHELPER

#include "bevgrafmath2017.h"
#include <GL/glut.h>					// (or others, depending on the system in use)
#include <GL/freeglut.h>
#include <iostream>
#include <vector>

typedef std::vector<vec2 > Matrix;

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

inline void setColor ( double red, double green, double blue )
{
    glColor3f ( red / 255.0, green / 255.0, blue / 255.0 );
}

inline void setColor ( Color color )
{
    switch ( color ) {
    case red :
        glColor3f ( 1.0, 0.0, 0.0 );
        break;
    case green :
        glColor3f ( 0.0, 1.0, 0.0 );
        break;
    case blue :
        glColor3f ( 0.0, 0.0, 1.0 );
        break;
    case black :
        glColor3f ( 0.0, 0.0, 0.0 );
        break;
    case white :
        glColor3f ( 1.0, 1.0, 1.0 );
        break;
    case gray :
        glColor3f ( 0.1, 0.1, 0.1 );
        break;
    case purple :
        glColor3f ( 75.0 / 255.0, 0.0, 130.0 / 255.0 );
        break;
    case yellow :
        glColor3f ( 1.0, 1.0, 0.0 );
        break;
    case brown :
        glColor3f ( 0.5, 0.0, 0.0 );
        break;
    }
}

inline void setBackgroundColor ( Color color )
{
    switch ( color ) {
    case red :
        glClearColor ( 1.0, 0.0, 0.0, 1.0 );
        break;
    case green :
        glClearColor ( 0.0, 1.0, 0.0, 1.0 );
        break;
    case blue :
        glClearColor ( 0.0, 0.0, 1.0, 1.0 );
        break;
    case black :
        glClearColor ( 0.0, 0.0, 0.0, 1.0 );
        break;
    case white :
        glClearColor ( 1.0, 1.0, 1.0, 1.0 );
        break;
    case gray :
        glClearColor ( 0.1, 0.1, 0.1, 1.0 );
        break;
    case purple :
        glClearColor ( 75.0 / 255.0, 0.0, 130.0 / 255.0, 1.0 );
        break;
    case yellow :
        glClearColor ( 1.0, 1.0, 0.0, 1.0 );
        break;
    case brown :
        glClearColor ( 0.5, 0.0, 0.0, 1.0 );
        break;
    }
}

inline void drawPoint ( vec2 point, Color color = none )
{

    if ( color != none ) {
        setColor ( color );
    }
    glBegin ( GL_POINTS );
    glVertex2f ( point.x, point.y );
    glEnd();

}

/*
 * point1, point2, point3, point4: Az alakzat sarkait reprezentáló pontok
 * isFilled: Legyen-e kitöltve a háromsz9g vagy nem
 * color: Háromszög színe
 */

inline void drawRect ( vec2 point1, vec2 point2, vec2 point3, vec2 point4, bool isFilled = true, Color color = none )
{

    //glClear(GL_COLOR_BUFFER_BIT);
    if ( isFilled == true ) {
        glBegin ( GL_POLYGON );
    } else {
        glBegin ( GL_LINE_LOOP );
    }

    if ( color != none ) {
        setColor ( color );
    }
    glVertex2i ( point1.x, point1.y );
    glVertex2i ( point2.x, point2.y );
    glVertex2i ( point3.x, point3.y );
    glVertex2i ( point4.x, point4.y );
    glEnd();
    //glFlush();
}

/*
 * bottomLeft: Bal alsó sarok pontja
 * topRight: Jobb felső sarokban lévő pont
 * color: Alakzat színe
 */

inline void drawRect ( vec2 bottomLeft, vec2 topRight, Color color = none )
{

    glClear ( GL_COLOR_BUFFER_BIT );
    if ( color != none ) {
        setColor ( color );
    }
    glRecti ( bottomLeft.x, bottomLeft.y, topRight.x, topRight.y );

}

/*
 * center: Alakzat közepét reprezentáló pont
 * halfSize: Alakzat fele
 * color: Alakzat színe
 */

inline void drawRect ( vec2 center, GLfloat halfSize, Color color = none )
{

    glClear ( GL_COLOR_BUFFER_BIT );
    if ( color != none ) {
        setColor ( color );
    }
    glRecti ( center.x - halfSize, center.y - halfSize, center.x + halfSize, center.y + halfSize );

}

/*
 * point1, point2, point3: A háromszög sarkait reprezentáló pontok
 * isFilled: Legyen-e kitöltve a háromsz9g vagy nem
 * color: Háromszög színe
 */

inline void drawTriangle ( vec2 point1, vec2 point2, vec2 point3, bool isFilled = true, Color color = none )
{

    //glClear(GL_COLOR_BUFFER_BIT);
    if ( isFilled == true ) {
        glBegin ( GL_POLYGON );
    } else {
        glBegin ( GL_LINE_LOOP );
    }
    if ( color != none ) {
        setColor ( color );
    }
    glVertex2i ( point1.x, point1.y );
    glVertex2i ( point2.x, point2.y );
    glVertex2i ( point3.x, point3.y );
    glEnd();
    //glFlush();
}

void drawLine(vec2 from, vec2 to, Color color1 = none, Color color2 = none){
  glBegin ( GL_LINE_LOOP );
  if (color1 != none) {
    setColor(color1);
  }
  glVertex2i ( from.x, from.y );
  if (color2 != none) {
    setColor(color2);
  }
  glVertex2i ( to.x, to.y );
  glEnd();
}

/*
 * p: ellenőrésre váró pont
 * size: optional: itt mindig egy legyen
 * sens: A pont és az egér kattintás közötti érzékenységre vonatkozik
 * x: Egér x koordináta
 * y: Egér y koordináta
 * return: -1 ha nem az ellenőrzött pontra kattintott, 1 ha igen
 */
GLint getActivePoint ( vec2 p, GLint size, GLint sens, GLint x, GLint y )
{
    GLint i, s= sens * sens;
    vec2 P = { ( float ) x, ( float ) y };
    for ( i = 0; i < size; i++ )
        if ( dist ( p, P ) < s ) {
            return i;
        }
    return -1;
}

void drawSemicircle ( vec2 O, GLdouble r )
{

    glBegin ( GL_LINE_STRIP );
    for ( GLdouble t = 0; t <= pi(); t += 0.01 ) {
        glVertex2d ( O.x + r * cos ( t ), O.y + r * sin ( t ) );
    }
    glEnd();
}

inline void drawCircle ( vec2 O, GLdouble r, Color color = none )
{
    if (color != none){
      setColor(color);
    }
    glBegin ( GL_LINE_LOOP );
    for ( GLdouble t = 0; t <= 2 * pi(); t += 0.01 ) {
        glVertex2d ( O.x + r * cos ( t ), O.y + r * sin ( t ) );
    }
    glEnd();
}

void drawEllipse ( vec2 O, GLdouble a, GLdouble b )
{

    glBegin ( GL_LINE_LOOP );
    for ( GLdouble t = 0; t <= 2 * pi(); t += 0.01 ) {
        glVertex2d ( O.x + a * cos ( t ), O.y + b * sin ( t ) );
    }
    glEnd();
}

Matrix drawPoligon ( int type, vec2 O, GLdouble r )
{
    Matrix matrix;
    GLdouble jump = two_pi() / type;
    glBegin ( GL_LINE_LOOP );
    for ( GLdouble t = 0; t <= 2 * pi(); t += jump ) {
	GLdouble x = O.x + r * cos ( t );
	GLdouble y = O.y + r * sin ( t );
        glVertex2d ( x, y );
	matrix.push_back(vec2(x, y));
    }
    glEnd();
    return matrix;
}

void drawAllDiagonal(Matrix matrix, Color color1 = none, Color color2 = none){
  for (int i = 0; i< matrix.size() - 1; i++){
    for (int j = i + 1;j < matrix.size() - 1; j++){
      drawLine(matrix[i], matrix[j], color1, color2);
    }
  }
}

void drawPointedBackground(vec2 windowSize, int distance = 1, Color pointsColor = none, Color backgroundColor = none){
  
  if (backgroundColor != none){
    setBackgroundColor(backgroundColor);
  }
  if (pointsColor != none){
    setColor(pointsColor);
  }
  for (int i = 0; i < windowSize.x; i += distance){
    for (int j = 0; j < windowSize.y; j += distance){
      drawPoint(vec2(i, j));
    }
  }
  
}

bool isPointInCircle(vec2 circleCenter, vec2 actualPoint, GLdouble radius){
  // Segéd változó az (x - u)^2
  GLdouble xu2 = pow(( circleCenter.x - actualPoint.x ), 2);
  // Segéd változó az (y - z)^2
  GLdouble yz2 = pow(( circleCenter.y - actualPoint.y ), 2);
  // Segéd változó az (x - u)^2 + (y - z)^2 - r^2
  GLdouble sum = xu2 + yz2 - pow(radius, 2);
  std::cout << sum << std::endl;
  if (sum < 0){
    return true;
  }else{
    return false;
  }
}

void drawPointedBackgroundWithCircle(vec2 windowSize, vec2 circleCenter, GLdouble radius, int distance = 1, Color pointsColor = none, Color circlePointsColor = none, Color backgroundColor = none){
  
  if (backgroundColor != none){
    setBackgroundColor(backgroundColor);
  }
  for (int i = 0; i < windowSize.x; i += distance){
    for (int j = 0; j < windowSize.y; j += distance){
      vec2 actualPoint = vec2(i, j);
      if (isPointInCircle(circleCenter, actualPoint, radius)){
	setColor(circlePointsColor);
      }else{
	setColor(pointsColor);
      }
      drawPoint(actualPoint);
    }
  }
  
}

#endif