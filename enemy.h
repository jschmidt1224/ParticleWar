#ifndef ENEMY_H
#define ENEMY_H

#include "vec2.h"


class Enemy
{
public:
  Vec2 pos;
  Vec2 momentum;
  int mass;
  float radius;
  float red, green, blue;
  float alpha;
  int sides;
  bool repel;
public:
  Enemy(Vec2, Vec2, int, float, int);
  void draw();
  void step();
};

#endif
