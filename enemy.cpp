
#include "enemy.h"
#include "GLFunc.h"
#include "particle.h"
#include "ship.h"
#include <list>



using namespace std;

extern bool mouse_right_down, mouse_middle_down;
extern int mouse_y, mouse_x;
extern list<Particle*> particles;
extern Ship player;

Enemy::Enemy(Vec2 p, Vec2 mo, int ma, float r1, int s)
{
  pos = p;
  momentum = mo;
  mass = ma;
  radius = r1;
  alpha = 1.5;
  sides = s;
  repel = rand() % 5;
}

void Enemy::draw()
{
  draw_circle(pos.x, pos.y, radius, sides, 1, 1, 1, alpha);
}

void Enemy::step()
{
  pos.x += momentum.x / mass;
  pos.y += momentum.y / mass;
  momentum.x *= .99;
  momentum.y *= .99;
  float dx = -1* pos.x;
  float dy = -1* pos.y;
  float mag = dx*dx + dy*dy;
  dx = 1*dx/sqrt(mag)*20;
  dy = 1*dy/sqrt(mag)*20;

  momentum.x += dx;
  momentum.y += dy;
  for (list<Particle*>::iterator it = particles.begin(); it != particles.end(); it++)
  {
    float dx = pos.x - (*it)->pos.x;
    float dy = pos.y - (*it)->pos.y;
    if(dx*dx + dy*dy < (radius + (*it)->radius)*(radius + (*it)->radius))
    {
      if((*it)->type == 1)
      {
        momentum.x += (*it)->momentum.x;
        momentum.y += (*it)->momentum.y;
      }
      else
      {
        momentum.x += (*it)->momentum.x * .5;
        momentum.y += (*it)->momentum.y * .5;
      }
      if((*it)->momentum.x * (*it)->momentum.x + (*it)->momentum.y * (*it)->momentum.y > 16)
      {
        if((*it)->type == 1)
          radius -= (*it)->mass / (float)10;
        else
          radius -= (*it)->mass / (float)100;
      }
      (*it)->momentum.x *= -.5;
      (*it)->momentum.y *= -.5;
      (*it)->life += 20;
    }


  }
  float dpx = pos.x - player.pos.x;
  float dpy = pos.y - player.pos.y;
  if(dpx*dpx + dpy*dpy < (radius + player.radius)*(radius + player.radius))
  {
    radius = 2;
    player.health += .05;
  }

}
