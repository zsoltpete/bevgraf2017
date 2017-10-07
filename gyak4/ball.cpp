#include "graphicalhelper.h"

vec2 windowSize = vec2(800, 800);

Circle circle = Circle(vec2 ( windowSize.x / 2.0, windowSize.y / 2.0 ), 100.0, vec2 ( 2,3 ));

void handleCircleMoving() {
    circle.center += circle.speed;
    if ( circle.center.x + circle.r > windowSize.x || circle.center.x - circle.r < 0 ) {
        circle.speed.x *= -1;
    }
    if ( circle.center.y + circle.r > windowSize.y || circle.center.y - circle.r < 0 ) {
        circle.speed.y *= -1;
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
    drawCircle ( circle, red );
    drawPointedBackgroundWithCircle(windowSize, circle, 17, black, red, gray);
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