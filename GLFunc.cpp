
#include "GLFunc.h"
#include <ctime>
#include <list>
#include "particle.h"
#include "enemy.h"
#include "ship.h"
#include "control.h"

using namespace std;

extern int mouse_x, mouse_y;
extern bool mouse_left_down, mouse_right_down, mouse_middle_down;
extern list<Particle*> particles;
extern list<Particle*> reds;
extern list<Enemy> enemies;
extern int frame;
extern long time1, timebase1;
extern Ship player;
extern Control ctrl;
extern float R, G, B;

bool initGL()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  srand(time(NULL));

  glClearColor(0.f, 0.f, 0.f, .5f);

  GLenum error = glGetError();
  if(error != GL_NO_ERROR)
  {
    printf("Error initializing OpenGL! %s\n", gluErrorString(error));
    return false;
  }

  glEnable(GL_BLEND);
  glDisable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  return true;
}

void update()
{
  static float h = 0;
  static float t = 0;
  static float ttn = 300;
  t++;
  h++;
  if (h > 360)
  {
    h -= 360;
  }
  if(mouse_left_down && !mouse_right_down)
  {
    for(int i = 0; i < 10; i++)
    {
      Vec2 pos = {mouse_x, mouse_y};
      Vec2 mom;
      float theta = rand() / (float) RAND_MAX * 3.1416 * 2;
      float scale = rand() / (float) RAND_MAX;
      mom.x = 2*cos(theta)*scale;
      mom.y = 2*sin(theta)*scale;
      Particle* test = new Red(pos, mom, 1, 5 + 5*rand() /(float) RAND_MAX, 3*rand() /(float) RAND_MAX,
                    (int)(30*2 + 30*rand() / (float) RAND_MAX - 15), R, G, B);
      particles.push_back(test);
      reds.push_back(test);
    }
  }
  //printf("Particles: %d\n", particles.size());

  if(t > ttn)
  {
    Vec2 pos = {-SCREEN_WIDTH / 2 + SCREEN_WIDTH * rand() / (float) RAND_MAX,
                -SCREEN_HEIGHT / 2 + SCREEN_HEIGHT * rand() / (float) RAND_MAX};
    while(pos.x*pos.x + pos.y*pos.y < 1)
    {
      pos.x = -SCREEN_WIDTH * 2 + 4*SCREEN_WIDTH * rand() / (float) RAND_MAX;
      pos.y = -SCREEN_HEIGHT * 2 + 4*SCREEN_HEIGHT * rand() / (float) RAND_MAX;
    }
    Vec2 mom = {0, 0};
    Enemy test(pos, mom, 1000, 30, 6);
    enemies.push_back(test);
    t = 0;
    ttn -= 10;
    if(ttn < 1)
      ttn = 1;

    if(player.health == -1)
    {
      player.health = 0;
      ttn = 300;
    }
  }

  for(list<Particle*>::iterator it = particles.begin(); it != particles.end(); it++)
  {
    (*it)->step();
    if((*it)->life > (*it)->max_life)
    {
      it = particles.erase(it);
    }
  }

  for(list<Particle*>::iterator it = reds.begin(); it != reds.end(); it++)
  {
    if((*it)->life > (*it)->max_life)
    {
      it = reds.erase(it);
    }
  }

  for(list<Enemy>::iterator it = enemies.begin(); it != enemies.end(); it++)
  {
    it->step();
    if(it->radius < 4)
    {
      it = enemies.erase(it);
    }
  }

  player.step();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glTranslatef(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, 0.f);

  //draw_circle(50.f, 50.f, 50, 50, 1.f, 0.f, 0.f, 1);
  //draw_circle(0.f, 0.f, 50, 50, 1.f, 0.f, 0.f, 1);
  //Vec2 pos;
  //pos.x = rand() / (float)RAND_MAX * SCREEN_WIDTH - SCREEN_WIDTH / 2;
  //pos.y = rand() / (float)RAND_MAX * SCREEN_HEIGHT - SCREEN_HEIGHT / 2;
  //Vec2 mom = {0, 0};
  //Particle test(pos, mom, 5, 30, rand() / (float) RAND_MAX, rand() / (float) RAND_MAX, rand() / (float) RAND_MAX);
  //particles.push_back(test);

  for(list<Particle*>::iterator it = particles.begin(); it != particles.end(); it++)
  {
    (*it)->draw();
  }

  for(list<Enemy>::iterator it = enemies.begin(); it != enemies.end(); it++)
  {
    it->draw();
  }

  player.draw();
  ctrl.draw();

  frame++;

	time1=glutGet(GLUT_ELAPSED_TIME);
	if (time1 - timebase1 > 1000) {
		printf("FPS:%4.2f\nParticles: %d\n",
			frame*1000.0/(time1-timebase1), particles.size() + reds.size());
		timebase1 = time1;
		frame = 0;
		printf("Mode: %d\n", ctrl.mode);
	}

  glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y)
{
  if(key == '1')
  {
    ctrl.change_mode(1);
  }
  if(key == '2')
  {
    ctrl.change_mode(2);
  }
  if(key == '3')
  {
    ctrl.change_mode(3);
  }
}

void mouse(int button, int state, int x, int y)
{
  mouse_x = x - SCREEN_WIDTH / 2;
  mouse_y = y - SCREEN_HEIGHT / 2;
  switch(button)
  {
  case GLUT_LEFT_BUTTON:
    if (state == GLUT_DOWN)
      mouse_left_down = true;
    else
      mouse_left_down = false;
    break;
  case GLUT_RIGHT_BUTTON:
    if (state == GLUT_DOWN)
      mouse_right_down = true;
    else
      mouse_right_down = false;
    break;
  case GLUT_MIDDLE_BUTTON:
    if (state == GLUT_DOWN)
      mouse_middle_down = true;
    else
      mouse_middle_down = false;
    break;
  }
}

void passiveMouse(int x, int y)
{
  mouse_x = x - SCREEN_WIDTH / 2;
  mouse_y = y - SCREEN_HEIGHT / 2;
}

void draw_circle(float cx, float cy, float r, int num_segments, float R, float G, float B, float A)
{
  float theta = 2 * 3.1415926 / float(num_segments);
	float tangetial_factor = tanf(theta);

	float radial_factor = cosf(theta);

	float x = r;

	float y = 0;

	glBegin(GL_TRIANGLE_FAN);
    glColor4f(R, G, B, A);
    glVertex2f(cx, cy);
    for(int ii = 0; ii < num_segments+1; ii++)
    {
      glColor4f(R, G, B, A);
      glVertex2f(x + cx, y + cy);

      float tx = -y;
      float ty = x;

      x += tx * tangetial_factor;
      y += ty * tangetial_factor;

      x *= radial_factor;
      y *= radial_factor;
    }
	glEnd();
}











