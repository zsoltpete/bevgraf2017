#include "graphicalhelper.h"

//Globális elemek
vec2 tInverval = vec2 ( 0, 1 );
vec2 tPoints = vec2 ( 0.0, 1.0 );

double winWidth = 600, winHeight = 600;

GLint dragged = -1;				//Tárolja az éppen mozgatott pont indexét default: -1

Matrix initPoints() {
    Matrix points;
    points.push_back ( vec2 ( 300,200 ) );
    points.push_back ( vec2 ( 500,250 ) );
    points.push_back ( vec2 ( 350,220 ) );
    points.push_back ( vec2 ( 400,245 ) );
    return points;
}

Matrix points = initPoints();

mat24 calculateG ( mat24 G, Matrix points ) {
    G[0] = vec4 ( points[0].x, points[1].x, points[2].x - points[0].x, points[3].x - points[1].x);
    G[1] = vec4 ( points[0].y, points[1].y, points[2].y - points[0].y, points[3].y - points[1].y);
    return G;
}

mat4 convertMatrix4Tomat4 ( Matrix4 matrix ) {
    mat4 MInvers = mat4 ( 0 );
    for ( int i = 0; i<matrix.size(); i++ ) {
        for ( int j = 0; j<matrix.size(); j++ ) {
            MInvers[i][j] = matrix[i][j];
        }
    }
    return MInvers;
}

void printTPoints ( Matrix points ) {
    for ( int i = 0; i< points.size(); i++ ) {
        vec2 point = points[i];
        drawPoint ( point, blue );
    }
}

void calculator ( vec2 t, vec2 tPoints, Matrix points ) {
    mat24 G = mat24 ( 0 );
    G = calculateG ( G, points );
    //Matrix4 adatszerkezet bevezetése a ciklusban lévő feltöltés végett
    Matrix4 tmpMInvers;
    //Feltöltés oszlop foltanosan
    tmpMInvers.push_back ( vec4 ( pow ( tPoints.x, 3 ), pow ( tPoints.x, 2 ), tPoints.x, 1 ) );
    tmpMInvers.push_back ( vec4 ( pow ( tPoints.y, 3 ), pow ( tPoints.y, 2 ), tPoints.y, 1 ) );
    tmpMInvers.push_back ( vec4 (3 * ( pow ( tPoints.x, 2 )), 2 * tPoints.x, 1, 0 ) );
    tmpMInvers.push_back ( vec4 (3 * ( pow ( tPoints.y, 2 )), 2 * tPoints.y, 1, 0 ) );
    mat4 MInvers = convertMatrix4Tomat4 ( tmpMInvers );
    MInvers = transpose(MInvers);
    //Más adatszerkezettel töltöm fel azt konvertálom át mat4-be
    mat4 M = inverse ( MInvers );
    mat24 C = G*M;
    glBegin ( GL_LINE_STRIP );
    for ( double i = t.x; i < t.y; i += 0.0001 ) {
        //T vektor inicialaizálása
        vec4 tVector = vec4 ( pow ( i, 3 ), pow ( i, 2 ), i,1 );
        vec2 printPoint = C*tVector;
        glVertex2f ( printPoint.x, printPoint.y );
    }
    glEnd();
    printTPoints ( points );
}




void init() {
    glClearColor ( 1.0, 1.0, 1.0, 0.0 );
    glMatrixMode ( GL_PROJECTION );
    gluOrtho2D ( 0.0, winWidth, 0.0, winHeight );
    glShadeModel ( GL_FLAT );
    glEnable ( GL_POINT_SMOOTH );
    glPointSize ( 10.0 );
    glLineWidth ( 2.0 );
}

void display() {

    glClear ( GL_COLOR_BUFFER_BIT );
    setColor ( red );
    calculator ( tInverval, tPoints, points );
    glutSwapBuffers();

}

void processMouse ( GLint button, GLint action, GLint xMouse, GLint yMouse ) {
    GLint i;
    if ( button == GLUT_LEFT_BUTTON && action == GLUT_DOWN )
        if ( ( i = getActivePoint ( points, 4, 8, xMouse, winHeight - yMouse ) ) != -1 )
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
    glutCreateWindow ( "4 Hermite" );
    init();
    glutDisplayFunc ( display );
    glutMouseFunc ( processMouse );
    glutMotionFunc ( processMouseActiveMotion );
    glutMainLoop();
    return 0;
}