
#include "red.h"
#include <list>

using namespace std;

extern list<Particle*> reds;

void Red::step()
{
  float dist;
  Particle::step();
  if(radiusi < 30)
  {
    for(list<Particle*>::iterator it = reds.begin(); it != reds.end(); it++)
    {
      if(radiusi > 30)
        it = --reds.end();
      if((*it)->radiusi >= 30)
      {
        it = reds.erase(it);
        continue;
      }
      dist = (pos.x - (*it)->pos.x) * (pos.x - (*it)->pos.x) + (pos.y - (*it)->pos.y) * (pos.y - (*it)->pos.y);
      if(dist < (radius + (*it)->radius) * (radius + (*it)->radius) && radiusi + (*it)->radiusi <= 30)
      {
        if(pos.x != (*it)->pos.x && pos.y != (*it)->pos.y && life < max_life)
        {
          pos.x = (pos.x + (*it)->pos.x) / 2;
          pos.y = (pos.y + (*it)->pos.y) / 2;
          momentum.x += (*it)->momentum.x;
          momentum.y += (*it)->momentum.y;
          radius += (*it)->radius;
          radiusf += (*it)->radiusf*2;
          life = (life + (*it)->life) * 2;
          max_life += (*it)->max_life;
          m = (radiusf - radius)/(max_life - life);
          radiusi = radius - m*life;
          mass += (*it)->mass;
          printf("test\n");

          (*it)->life += 2 * (*it)->max_life;
          it = reds.erase(it);
        }
      }
    }
  }
}
