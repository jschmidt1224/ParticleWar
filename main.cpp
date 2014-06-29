#include "GLFunc.h"
#include "particle.h"
#include "enemy.h"
#include "ship.h"
#include "control.h"
#include "red.h"
#include <list>

using namespace std;

void mainLoop(int val);

int mouse_x, mouse_y;
bool mouse_left_down, mouse_right_down, mouse_middle_down;
list<Particle*> particles;
list<Particle*> reds;
list<Enemy> enemies;
long time1, timebase1;
int frame;
Ship player;
Control ctrl;
float R = 1, G = 0, B = 0;


int main(int argc, char* args[])
{

	glutInit(&argc, args);

	glutInitContextVersion(2, 1);

	glutInitDisplayMode(GLUT_DOUBLE|GLUT_MULTISAMPLE);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Particle War");

	if(!initGL())
	{
		printf("Unable to initialize graphics library!\n");
		return 1;
	}

  glutKeyboardFunc(keyboard);

  glutMouseFunc(mouse);

  glutPassiveMotionFunc(passiveMouse);

  glutMotionFunc(passiveMouse);

	glutDisplayFunc(display);

	glutTimerFunc(1000 / SCREEN_FPS, mainLoop, 0);

	glutMainLoop();

	return 0;
}

void mainLoop(int val)
{
  update();
  display();

  //Run frame one more time
  glutTimerFunc(1000 / SCREEN_FPS, mainLoop, val);
}

