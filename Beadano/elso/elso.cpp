#include "graphicalhelper.h"

//Globális elemek
Matrix bersteinPoints;
Matrix deCasteljouPoints;
Matrix sumPoints;
double T = 0.5;
vec2 t = vec2 ( 0,1 );

double winWidth = 600, winHeight = 600;

GLint dragged = -1;				//Tárolja az éppen mozgatott pont indexét default: -1

/*
 * Kiszámolja az n faktorizáltját.
 * n: A számolni kívánt szám
 * return: Visszaadja a n faktorizáltját
 */
int fact ( long n ) {
    if ( 0>n )
        return -1;
    if ( 0 == n )
        return 1;
    else {
        return ( n* fact ( n-1 ) );
    }
}
/*
 * Kiszámolja a binomiális együtthatót
 * ( n )         n!
 * ( _ ) = ______________
 * ( k )   k! * ( n - k)!
 * n: n
 * i: k
 * return: Visszaadja a binomiális együtthatót
 */
int binomial ( int n, int i ) {
    return fact ( n ) / ( fact ( i ) * ( fact ( n - i ) ) );
}

/*
 * Kiszámolja a Beistein polinomot
 * i: k
 * n: n
 * t: ?????????????
 * return: Visszaadja a Berstein polinomit
 */
double beisteinPolinom ( int i, int n, double t ) {
    double result = binomial ( n, i ) * pow ( t, i ) * pow ( ( 1 - t ), ( n - i ) );
//     std::cout << "i: " << i << " n: " << n << " t: " << t << " result: " << result << std::endl;
    return result;
}

/*
 * Inicializálja a De Berstein pontokat
 * return: Visszaadja a Berstein pontokat
 */
Matrix initBersteinPoints() {
    Matrix points;
    points.push_back ( vec2 ( 400,500 ) );
    points.push_back ( vec2 ( 500,500 ) );
    points.push_back ( vec2 ( 500,275 ) );
    points.push_back ( vec2 ( 300,300 ) );
    return points;
}

/*
 * Inicializálja a De Casteljou pontokat
 * return: Visszaadja a De Casteljou pontokat
 */
Matrix initDeCasteljouPoints() {
    Matrix points;
    points.push_back ( ( vec2 ) bersteinPoints[bersteinPoints.size() - 1] );			//Egyenlő a berstein utolsójával
    points.push_back ( vec2 ( 0,0 ) );		//Számolva lesz középpontosan az előzőhöz képest
    points.push_back ( vec2 ( 37,250 ) );
    points.push_back ( vec2 ( 41,93 ) );
    points.push_back ( vec2 ( 485,107 ) );
    return points;
}

/*
 * Kiszámolja a P-hez tartozó t értéket
 * matrix: Pontok halmazát reprezentáló matrix
 * t: [0,1] intervallumból vett aktuális érték
 * return: Visszaadja a De Casteljou pontot a matrix és t értékek függvényében
 */
vec2 deCasteljou ( Matrix P, double t ) {
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

/*
 * Összeköti a De Casteljou pontokból alkotott alpontokat és kirajzolja a pontokat is.
 * matrix: Pontok halmazát reprezentáló matrix
 * T: Osztópont. Ez a adja meg a osztás aránát két pont között
 */
void linkDeCasteljouPoints ( Matrix points, double T ) {
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
            drawPoint ( point2, green );
        }
        linkDeCasteljouPoints ( newPoints, T );
    }
}

/*
 * Kirajzolva a De Casteljou féle Bezier görbét
 * matrix: De Casteljou pontok halmazát reprezentáló matrix
 */
void drawDeCasteljou ( Matrix points ) {
    glBegin ( GL_LINE_STRIP );
    for ( double i = t.x; i < t.y; i += 0.001 ) {
        vec2 printPoint = deCasteljou ( points, i );
        setColor ( purple );
        glVertex2f ( printPoint.x, printPoint.y );
    }
    glEnd();
}
/*
 * Összegzése a részVektorosnak
 */
void sumPointsMatrix() {
    sumPoints = bersteinPoints;
    for ( int i = 0; i < deCasteljouPoints.size(); i++ ) {
        sumPoints.push_back ( deCasteljouPoints[i] );
    }
}

/*
 * Kirajzolva a Berstein pontokat
 * matrix: Berstein pontok halmazát reprezentáló matrix
 */
void drawBersteinPoints ( Matrix points ) {
    for ( int i = 0; i< points.size(); i++ ) {
        vec2 point = points[i];
        drawPoint ( point, green );
    }
}
/*
 * Kirajzolva a De Casteljou pontokat
 * matrix: De Casteljou pontok halmazát reprezentáló matrix
 */
void drawDeCasteljouPoints ( Matrix points ) {
    for ( int i = 0; i< points.size(); i++ ) {
        vec2 point = points[i];
	if (i == 1){
	  drawPoint ( point, red );
	}else{
	  drawPoint ( point, green );
	}
    }
}

/*
 * Összeköti a Berstein pontokból alkotott alpontokat
 * matrix: Pontok halmazát reprezentáló matrix
 */
void linkBersteinPoints ( Matrix points ) {
    for ( int i = 0; i< points.size() - 1; i++ ) {
        vec2 point1 = points[i];
        vec2 point2 = points[i + 1];
        drawLine ( point1, point2, blue );
    }
}
/*
 * Középpontosan tükröz.
 * P: Kívánt pont, amit tükrözni kell
 * O: Középpont
 * return: P' pont, ami O középpontosan tükrös P-vel
 */
vec2 mirrorPointToPoint ( vec2 P, vec2 O ) {
    vec2 PO = P - O;
    return O - PO;
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
    deCasteljouPoints = initDeCasteljouPoints();
}

void display() {

    glClear ( GL_COLOR_BUFFER_BIT );
    setColor ( red );
    drawBersteinPoints ( bersteinPoints );
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
    glEnd();
    vec2 O = bersteinPoints[n - 1];
    vec2 P = bersteinPoints[n - 2];
    vec2 newPoint = mirrorPointToPoint ( P, O );			//Kiszámolva a De Casparis 2 (1 indexű) pontját
    deCasteljouPoints[0] = ( vec2 ) bersteinPoints[bersteinPoints.size() - 1];
    deCasteljouPoints[1] = newPoint;
    linkDeCasteljouPoints ( deCasteljouPoints, T );
    drawDeCasteljou ( deCasteljouPoints );
    drawDeCasteljouPoints ( deCasteljouPoints );
    sumPointsMatrix();
    glutSwapBuffers();
}

void processMouse ( GLint button, GLint action, GLint xMouse, GLint yMouse ) {
    GLint i;
    if ( button == GLUT_LEFT_BUTTON && action == GLUT_DOWN )
        if ( ( i = getActivePoint ( sumPoints, sumPoints.size(), 8, xMouse, winHeight - yMouse ) ) != -1 ) {
            dragged = i;
        }

    if ( button == GLUT_LEFT_BUTTON && action == GLUT_UP )
        dragged = -1;
}

void processMouseActiveMotion ( GLint xMouse, GLint yMouse ) {
    GLint i;
    int bersteinSize = bersteinPoints.size();
    if ( dragged >= 0 && dragged < bersteinSize ) {
        bersteinPoints[dragged].x = xMouse;
        bersteinPoints[dragged].y = winHeight - yMouse;
        glutPostRedisplay();
    } else if ( dragged >= bersteinSize && dragged < bersteinSize + deCasteljouPoints.size() ) {
        deCasteljouPoints[dragged - bersteinSize].x = xMouse;
        deCasteljouPoints[dragged - bersteinSize].y = winHeight - yMouse;
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
    glutCreateWindow ( "Berstein" );
    init();
    glutDisplayFunc ( display );
    glutKeyboardFunc ( keyboard );
    glutMouseFunc ( processMouse );
    glutMotionFunc ( processMouseActiveMotion );
    glutMainLoop();
    return 0;
}