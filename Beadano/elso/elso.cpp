#include "graphicalhelper.h"

//Globális elemek
Matrix bersteinPoints;
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

int binomial ( int n, int i ) {
    return fact ( n ) / ( fact ( i ) * ( fact ( n - i ) ) );
}

double beisteinPolinom ( int i, int n, double t ) {
    double result = binomial ( n, i ) * pow ( t, i ) * pow ( ( 1 - t ), ( n - i ) );
//     std::cout << "i: " << i << " n: " << n << " t: " << t << " result: " << result << std::endl;
    return result;
}

Matrix initBersteinPoints() {
    Matrix points;
    points.push_back ( vec2 ( 400,500 ) );
    points.push_back ( vec2 ( 500,500 ) );
    points.push_back ( vec2 ( 500,350 ) );
    points.push_back ( vec2 ( 300,300 ) );
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

    bersteinPoints = initBersteinPoints();
}

void printPoints ( Matrix points ) {
    for ( int i = 0; i< points.size(); i++ ) {
        vec2 point = points[i];
        drawPoint ( point, green );
    }
}

void linkBersteinPoints ( Matrix points ) {
    for ( int i = 0; i< points.size() - 1; i++ ) {
        vec2 point1 = points[i];
        vec2 point2 = points[i + 1];
        drawLine ( point1, point2, blue );
    }
}

vec2 mirrorPointToPoint(vec2 P, vec2 O){
  vec2 PO = P - O;
  return O - PO;
}

void display() {

    glClear ( GL_COLOR_BUFFER_BIT );
    setColor ( red );
    printPoints ( bersteinPoints );
    linkBersteinPoints ( bersteinPoints );
    int n =  bersteinPoints.size();		//Pontok száma
    glBegin ( GL_LINE_STRIP );
    for ( double t = 0; t < 1; t += 0.001 ) {
        vec2 printPoint = vec2 ( 0,0 );
        for ( double i = 0; i < n; i++ ) {	//n - 1 mivel itt a görbe fokszámát kell átadni a függvénynek
            printPoint += beisteinPolinom ( i, n - 1, t ) * ( vec2 ) bersteinPoints[i];
        }
        setColor ( purple );
//         printMathObject ( printPoint );
        glVertex2f ( printPoint.x, printPoint.y );
    }
    vec2 O = bersteinPoints[n - 1];
    vec2 P = bersteinPoints[n - 2];
    vec2 newPoint = mirrorPointToPoint(P, O);
    drawPoint(newPoint, blue);
    drawPoint(newPoint, green);
    glEnd();

    glutSwapBuffers();
}

void processMouse ( GLint button, GLint action, GLint xMouse, GLint yMouse ) {
    GLint i;
    if ( button == GLUT_LEFT_BUTTON && action == GLUT_DOWN )
        if ( ( i = getActivePoint ( bersteinPoints, bersteinPoints.size(), 8, xMouse, winHeight - yMouse ) ) != -1 )
            dragged = i;
    if ( button == GLUT_LEFT_BUTTON && action == GLUT_UP )
        dragged = -1;
}

void processMouseActiveMotion ( GLint xMouse, GLint yMouse ) {
    GLint i;
    if ( dragged >= 0 ) {
        bersteinPoints[dragged].x = xMouse;
        bersteinPoints[dragged].y = winHeight - yMouse;
        glutPostRedisplay();
    }
}

int main ( int argc, char** argv ) {
    glutInit ( &argc, argv );
    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize ( winWidth, winHeight );
    glutInitWindowPosition ( 100, 100 );
    glutCreateWindow ( "Berstein" );
    init();
    glutDisplayFunc ( display );
    glutMouseFunc ( processMouse );
    glutMotionFunc ( processMouseActiveMotion );
    glutMainLoop();
    return 0;
}