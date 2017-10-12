#include "graphicalhelper.h"

//Globális elemek
vec2 tInverval = vec2 ( -1, 2 );
vec4 tPoints = vec4 (-1.0,0.0,1.0,2.0);

double winWidth = 800, winHeight = 800;

Matrix initPoints() {
    Matrix points;
    points.push_back ( vec2 ( 400,400 ) );
    points.push_back ( vec2 ( 500,100 ) );
    points.push_back ( vec2 ( 650,350 ) );
    points.push_back ( vec2 ( 30,600 ) );
    return points;
}

Matrix points = initPoints();

mat24 calculateG ( mat24 G, Matrix points ) {
    G[0] = vec4 ( points[0].x, points[1].x, points[2].x, points[3].x );
    G[1] = vec4 ( points[0].y, points[1].y, points[2].y, points[3].y );
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

void calculator(vec2 t, vec4 tPoints, Matrix points ) {
    mat24 G = mat24 ( 0 );
    G = calculateG ( G, points );
    //Matrix4 adatszerkezet bevezetése a ciklusban lévő feltöltés végett
    Matrix4 tmpMInvers;
    //Feltöltés oszlop foltanosan 																						    
    for ( int i = 0; i< 4; i++ ) {
         tmpMInvers.push_back ( vec4 ( pow ( tPoints.x, 3-i ), pow ( tPoints.y, 3-i),pow ( tPoints.z, 3-i), pow ( tPoints.w, 3-i) ) ); 
	 printMathObject(tmpMInvers[i]);
    }
    //Más adatszerkezettel töltöm fel azt konvertálom át mat4-be
    mat4 MInvers = convertMatrix4Tomat4 ( tmpMInvers );
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
    glPointSize ( 5.0 );
    glLineWidth ( 2.0 );
}

void display() {

    glClear ( GL_COLOR_BUFFER_BIT );
    setColor ( red );
    calculator(tInverval, tPoints, points);
    glutSwapBuffers();

}

int main ( int argc, char** argv ) {
    glutInit ( &argc, argv );
    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize ( winWidth, winHeight );
    glutInitWindowPosition ( 100, 100 );
    glutCreateWindow ( "4 Hermite" );
    init();
    glutDisplayFunc ( display );
    glutMainLoop();
    return 0;
}