#include "graphicalhelper.h"


double winWidth = 800, winHeight = 800;

Matrix initPoints() {
    Matrix points;
    points.push_back ( vec2 ( 400,400 ) );
    points.push_back ( vec2 ( 500,100 ) );
    points.push_back ( vec2 ( 650,350 ) );
    points.push_back ( vec2 ( 30,600 ) );
    return points;
}

mat24 calculateG ( mat24 G, Matrix points ) {
    G[0] = vec4 ( points[0].x, points[1].x, points[2].x, points[3].x );
    G[1] = vec4 ( points[0].y, points[1].y, points[2].y, points[3].y );
    return G;
}

Vector initTPoints ( double p1, double p2, double p3, double p4 ) {
    Vector tPoints;
    tPoints.push_back ( p1 );
    tPoints.push_back ( p2 );
    tPoints.push_back ( p3 );
    tPoints.push_back ( p4 );
    return tPoints;
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

void printTPoints(Matrix points){
  for(int i = 0;i< points.size(); i++){
    vec2 point = points[i];
    drawPoint(point, blue);
  }
}

void calculator() {
    Matrix points = initPoints();
    mat24 G = mat24 ( 0 );
    G = calculateG ( G, points );
    //t intervallum
    vec2 t = vec2 ( -1, 2 );
    //4 pont
    Vector tPoints = initTPoints ( -1.0,0.0,1.0,2.0 );
    Matrix4 tmpMInvers;
    for ( int i = 0; i< tPoints.size(); i++ ) {
        tmpMInvers.push_back ( vec4 ( pow ( tPoints[0], 3-i ), pow ( tPoints[1], 3-i ), pow ( tPoints[2], 3-i ), pow ( tPoints[3], 3-i ) ) );
    }
    //Más adatszerkezettel töltöm fel azt konvertálom át mat4-be
    mat4 MInvers = convertMatrix4Tomat4 ( tmpMInvers );
    mat4 M = inverse ( MInvers );
    mat24 C = G*M;
    for ( double i = t.x; i < t.y; i += 0.001 ) {
        vec4 tVector = vec4 ( pow ( i, 3 ), pow ( i, 2 ), pow ( i, 1 ), pow ( i, 0 ) );
        vec2 printPoint = C*tVector;
        drawPoint ( printPoint, red );
    }
    printTPoints(points);
}




void init() {
    glClearColor ( 1.0, 1.0, 1.0, 0.0 );
    glMatrixMode ( GL_PROJECTION );
    gluOrtho2D ( 0.0, winWidth, 0.0, winHeight );
    glShadeModel ( GL_FLAT );
    glEnable ( GL_POINT_SMOOTH );
    glEnable ( GL_LINE_STIPPLE );
    glPointSize ( 5.0 );
    glLineWidth ( 5.0 );
    glLineStipple ( 1, 0xFF00 );
}

void display() {

    glClear ( GL_COLOR_BUFFER_BIT );
    setColor ( red );
    calculator();
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