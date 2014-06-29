
#ifndef GLFUNC_H
#define GLFUNC_H

#include "OGL.h"
#include <stdio.h>
#include <math.h>
#include <list>
#include "particle.h"
#include "red.h"

//Screen Constants
const int SCREEN_WIDTH = (int)(640*1.5);
const int SCREEN_HEIGHT = (int)(480*1.5);
const int SCREEN_FPS = 30;

bool initGL();

void update();

void display();

void keyboard(unsigned char key, int x, int y);

void mouse(int button, int state, int x, int y);

void passiveMouse(int x, int y);

void draw_circle(float cx, float cy, float r, int num_segments, float, float, float, float);

DWORD WINAPI update1(LPVOID iValue);





#endif
