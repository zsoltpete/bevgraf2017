#include <GL/glut.h>
#include "bevgrafmath2017.h"
#include <iostream>

//Main program
int main(int argc, char **argv)
{
  vec2 v1, v2(1,1);
  vec2 v3 = v1-v2;
  vec2 v4 = normalize(v2);
  
 printMathObject(v2);
  return 0;
}