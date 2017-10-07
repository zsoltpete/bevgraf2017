#include "graphicalhelper.h"

vec2 windowSize = vec2(800, 800);
vec2 circleCenter = vec2 ( windowSize.x / 2.0, windowSize.y / 2.0 );
vec2 changeCenterVector = vec2 ( 2,3 );
GLdouble circleRadius = 100.0;

void handleCircleMoving() {
    circleCenter += changeCenterVector;
    if ( circleCenter.x + circleRadius > windowSize.x || circleCenter.x - circleRadius < 0 ) {
        changeCenterVector.x *= -1;
    }
    if ( circleCenter.y + circleRadius > windowSize.y || circleCenter.y - circleRadius < 0 ) {
        changeCenterVector.y *= -1;
    }
}

void init() {
    glClearColor ( 1.0, 1.0, 1.0, 0.0 );
    glMatrixMode ( GL_PROJECTION );
    gluOrtho2D ( 0.0, windowSize.x, 0.0, windowSize.y );
    glShadeModel ( GL_FLAT );
    glPointSize ( 10.0 );
    glLineWidth(5.0);
    glEnable ( GL_POINT_SMOOTH );
}

void display() {
    glClear ( GL_COLOR_BUFFER_BIT );
    drawCircle ( circleCenter, circleRadius, red );
    drawPointedBackgroundWithCircle(windowSize, circleCenter, circleRadius, 17, black, red, gray);
    glutSwapBuffers();
}

void update ( int n ) {
    handleCircleMoving();
    glutPostRedisplay();
    glutTimerFunc ( 5, update, 0 );

}

int main ( int argc, char** argv ) {
    glutInit ( &argc, argv );
    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize ( windowSize.x, windowSize.y );
    glutInitWindowPosition ( 100, 100 );
    glutCreateWindow ( "Drag & Drop" );
    init();
    glutDisplayFunc ( display );
    glutTimerFunc ( 5, update, 0 );
    glutMainLoop();
    return 0;
}