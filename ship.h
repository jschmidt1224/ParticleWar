#ifndef SHIP_H
#define SHIP_H

#include "vec2.h"

class Ship
{
public:
  Vec2 pos;
  float radius;
  int h;
  float health;
public:
  Ship(Vec2, float);
  Ship();
  void draw();
  void step();
};


#endif
