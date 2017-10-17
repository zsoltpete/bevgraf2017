#include "graphicalhelper.h"

//Globális elemek
Matrix points;
vec2 t = vec2 ( 0,1 );
double T = 0.5;

double winWidth = 600, winHeight = 600;

GLint dragged = -1;				//Tárolja az éppen mozgatott pont indexét default: -1

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

vec2 deCasparis ( Matrix P, double t ) {
    Matrix Q;
    int n = P.size();
    for ( int i = 0; i< n; i++ ) {
        Q.push_back ( P[i] );
    }
    for ( int r = 1; r < n; r++ ) {
        for ( int i = 0; i < n - r; i++ ) {
            vec2 point;
            point.x = ( 1 - t ) * ( ( vec2 ) Q[i] ).x + t * ( ( vec2 ) Q[i + 1] ).x;
            point.y = ( 1 - t ) * ( ( vec2 ) Q[i] ).y + t * ( ( vec2 ) Q[i + 1] ).y;
            Q[i] = point;
        }
    }
    return Q[0];

}

void linkDeCasparisPoints ( Matrix points, double T ) {
    int n = points.size();
    if ( n == 1 ) {
        for ( int i = 0; i < n; i++ ) {
            vec2 point1 = points[i];
            drawPoint ( point1, green );
        }
    } else {
        Matrix newPoints;
        for ( int i = 0; i < n - 1; i++ ) {
            vec2 point1 = points[i];
            vec2 point2 = points[i + 1];
            vec2 vector = point2 - point1;
            vector *= T;
            vector += point1;
            drawLine ( point1, point2, blue );
            newPoints.push_back ( vector );
            drawPoint ( point1, green );
        }
        linkDeCasparisPoints ( newPoints, T );
    }
}

void printPoints ( Matrix points ) {
    for ( int i = 0; i< points.size(); i++ ) {
        vec2 point = points[i];
        drawPoint ( point, green );
    }
}

void drawDeCasparis() {
    glBegin ( GL_LINE_STRIP );
    for ( double i = t.x; i < t.y; i += 0.001 ) {
        vec2 printPoint = deCasparis ( points, i );
        setColor ( purple );
        glVertex2f ( printPoint.x, printPoint.y );
    }
    glEnd();
}

void display() {

    glClear ( GL_COLOR_BUFFER_BIT );
    setColor ( red );
    linkDeCasparisPoints ( points, T );
    drawDeCasparis();
    printPoints ( points );
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

void keyboard ( unsigned char key, int x, int y ) {
    switch ( key ) {
    case 27:
        exit ( 0 );
        break;
    case 'w':
        T += 0.01;
        if ( T >= 1.0 ) {
            T = 1.0;
        }
        break;
    case 's':
        T -= 0.01;
        if ( T <= 0.0 ) {
            T = 0.0;
        }
        break;
    }
    glutPostRedisplay();
}

int main ( int argc, char** argv ) {
    glutInit ( &argc, argv );
    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize ( winWidth, winHeight );
    glutInitWindowPosition ( 100, 100 );
    glutCreateWindow ( "de casperis" );
    init();
    glutDisplayFunc ( display );
    glutKeyboardFunc ( keyboard );
    glutMouseFunc ( processMouse );
    glutMotionFunc ( processMouseActiveMotion );
    glutMainLoop();
    return 0;
}