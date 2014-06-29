
#include "GLFunc.h"
#include "control.h"

extern float R, G, B;

void Control::draw()
{
  draw_circle(SCREEN_WIDTH / 2 - 28, -1*(SCREEN_HEIGHT / 2 - 28), 24, 4, R, G, B, 1.0f);
}

Control::Control()
{
  mode = 1;
}

void Control::change_mode(int m)
{
  mode = m;

  switch(mode)
  {
  case 1:
    R = 1;
    G = 0;
    B = 0;
    break;
  case 2:
    R = 0;
    G = 1;
    B = 0;
    break;
  case 3:
    R = 0;
    G = 0;
    B = 1;
    break;
  }
}
