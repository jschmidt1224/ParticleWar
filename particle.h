#ifndef PARTICLE_H
#define PARTICLE_H

#include "vec2.h"


class Particle
{
public:
  Vec2 pos;
  Vec2 momentum;
  int mass;
  float radiusi;
  float radiusf;
  float radius;
  float m;
  float red, green, blue;
  int life;
  int max_life;
  float alpha;
  int type;
public:
  Particle(Vec2, Vec2, int, float, float, int, float, float, float, int);
  void draw();
  virtual void step();
};















#endif
