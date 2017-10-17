#include "graphicalhelper.h"

//Globális elemek
Matrix points;
vec2 t = vec2 ( 0,1 );
double T = 0.5;

double winWidth = 600, winHeight = 600;

GLint dragged = -1;				//Tárolja az éppen mozgatott pont indexét default: -1

int fact ( long n ) {
    if ( 0>n )
        return -1;
    if ( 0 == n )
        return 1;
    else {
        return ( n* fact ( n-1 ) );
    }
}

int binomial(int n, int i){
  return fact(n) / (fact(i) * (fact(n - i)));
}

Matrix initPoints() {
    Matrix points;
    points.push_back ( vec2 ( 100,100 ) );
    points.push_back ( vec2 ( 250,500 ) );
    points.push_back ( vec2 ( 400,575 ) );
    points.push_back ( vec2 ( 450,500 ) );
    points.push_back ( vec2 ( 500,100 ) );
    return points;
}

void init() {
    glClearColor ( 1.0, 1.0, 1.0, 0.0 );
    glMatrixMode ( GL_PROJECTION );
    gluOrtho2D ( 0.0, winWidth, 0.0, winHeight );
    glShadeModel ( GL_FLAT );
    glEnable ( GL_POINT_SMOOTH );
    glPointSize ( 10.0 );
    glLineWidth ( 2.0 );

    points = initPoints();
}

void printPoints ( Matrix points ) {
    for ( int i = 0; i< points.size(); i++ ) {
        vec2 point = points[i];
        drawPoint ( point, green );
    }
}

void display() {

    glClear ( GL_COLOR_BUFFER_BIT );
    setColor ( red );
    printPoints ( points );
    std::cout << binomial(5,2) << std::endl;
    glutSwapBuffers();
}

void processMouse ( GLint button, GLint action, GLint xMouse, GLint yMouse ) {
    GLint i;
    if ( button == GLUT_LEFT_BUTTON && action == GLUT_DOWN )
        if ( ( i = getActivePoint ( points, points.size(), 8, xMouse, winHeight - yMouse ) ) != -1 )
            dragged = i;
    if ( button == GLUT_LEFT_BUTTON && action == GLUT_UP )
        dragged = -1;
}

void processMouseActiveMotion ( GLint xMouse, GLint yMouse ) {
    GLint i;
    if ( dragged >= 0 ) {
        points[dragged].x = xMouse;
        points[dragged].y = winHeight - yMouse;
        glutPostRedisplay();
    }
}

int main ( int argc, char** argv ) {
    glutInit ( &argc, argv );
    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize ( winWidth, winHeight );
    glutInitWindowPosition ( 100, 100 );
    glutCreateWindow ( "de casperis" );
    init();
    glutDisplayFunc ( display );
    glutMouseFunc ( processMouse );
    glutMotionFunc ( processMouseActiveMotion );
    glutMainLoop();
    return 0;
}