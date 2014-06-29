
#include "ship.h"
#include "GLFunc.h"
#include <list>
#include "particle.h"
#include "enemy.h"

using namespace std;

extern list<Particle*> particles;
extern list<Enemy> enemies;

Ship::Ship(Vec2 p, float r1)
{
  pos = p;
  radius = r1;
}

Ship::Ship()
{
  pos.x = 0;
  pos.y = 0;
  radius = 30;
  h = 0;
  health = 0;
}

void Ship::step()
{
  h++;
  if(h > 360)
    h -= 360;

  if(health > 1)
  {
    while(!enemies.empty())
    {
      enemies.pop_front();
    }
    while(!particles.empty())
    {
      particles.pop_front();
    }
    health = -1;

  }
}

void Ship::draw()
{
  float cx = pos.x;
  float cy = pos.y;
  float r = radius;
  int num_segments = 30;



  float theta = 2 * 3.1415926 / float(num_segments);
	float tangetial_factor = tanf(theta);

	float radial_factor = cosf(theta);

	float x = r;

	float y = 0;

	float R, G, B;
      float H = h;//rand() / (float)RAND_MAX *360;
      float S = 1;
      float V = 1;
      float C = V * S;
      float Hp = H/60;
      float X = C*(1 - fabs((fmod(Hp, 2)) - 1));
      if(Hp < 1)
      {
        R = C; G = X; B = 0;
      }
      else if(Hp < 2)
      {
        R = X; G = C; B = 0;
      }
      else if(Hp < 3)
      {
        R = 0; G = C; B = X;
      }
      else if(Hp < 4)
      {
        R = 0; G = X; B = C;
      }
      else if(Hp < 5)
      {
        R = X; G = 0; B = C;
      }
      else
      {
        R = C; G = 0; B = X;
      }
      float m = V-C;
      R += m;
      G += m;
      B += m;

	glBegin(GL_TRIANGLE_FAN);


    glColor4f(R +.2 - health, G+.2 - health, B+.2 - health, 1);
    glVertex2f(cx, cy);
    for(int ii = 0; ii < num_segments+1; ii++)
    {

      glColor4f(R - health, G-health, B-health, 1);
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
