
#ifndef CONTROL_H
#define CONTROL_H

#include "vec2.h"

#define MAX_MOM 100

class Control
{
public:
  int mode;
public:
  Control();
  void draw();
  void change_mode(int m);
};

#endif


