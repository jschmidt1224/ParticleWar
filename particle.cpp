#include "particle.h"
#include "GLFunc.h"

extern bool mouse_right_down, mouse_middle_down, mouse_left_down;
extern int mouse_y, mouse_x;

Particle::Particle(Vec2 p, Vec2 mo, int ma, float r1, float r2, int l, float re, float g, float b, int t)
{
  pos = p;
  momentum = mo;
  mass = ma;
  radiusi = r1;
  radiusf = r2;
  radius = r1;
  red = re;
  green = g;
  blue = b;
  max_life = l;
  life = 0;
  alpha = 1;
  m = (radiusf - radiusi) / l;
  type = t;
}

void Particle::draw()
{
  draw_circle(pos.x, pos.y, radius, ((int)radius < 8) ? 8 : (int)radius, red, green, blue, alpha);
}

void Particle::step()
{
  life++;
  pos.x += momentum.x / mass;
  pos.y += momentum.y / mass;
  momentum.x *= .99;
  momentum.y *= .99;
  radius = m*life + radiusi;

  if(mouse_right_down && !mouse_left_down)
  {
    float dx = mouse_x - pos.x;
    float dy = mouse_y - pos.y;
    float mag = dx*dx + dy*dy;
    dx = dx/sqrt(mag)*2;
    dy = dy/sqrt(mag)*2;

    momentum.x += dx;
    momentum.y += dy;
  }
  //momentum.y += .1;
  if(mouse_right_down && mouse_left_down)
  {
    float dx = mouse_x - pos.x;
    float dy = mouse_y - pos.y;
    float mag = dx*dx + dy*dy;
    dx = -1*dx/sqrt(mag)*2;
    dy = -1*dy/sqrt(mag)*2;

    momentum.x += dx;
    momentum.y += dy;
  }
}



