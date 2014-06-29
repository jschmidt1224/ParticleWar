
#ifndef RED_H
#define RED_H

#include "particle.h"

class Red : public Particle
{
public:
  Red(Vec2 v1, Vec2 v2, int i1, float f1, float f2, int i2, float f3, float f4, float f5) : Particle(v1, v2, i1, f1, f2, i2, 1, 0, 0, 1){}
  void step();
};







#endif
