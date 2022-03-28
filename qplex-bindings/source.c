#include "qpcommons.h"

void start()
{
}

void update()
{
  bonus_vars();

  color(v4(255,255,255,255));
  rect(v4(0,0,width,height));

  color(v4(255,0,mouse.z*255,255));
  rect(v4(width/2,height/2,100,100));

  tgamepad();
}
