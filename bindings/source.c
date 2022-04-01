#include "qpcommons.h"

void start()
{
}

void update()
{
  bonus_vars();

  // clear background
  color(v4(255,255,255,255));
  rect(v4(0,0,width,height));

  // place colorful square in the white screen
  color(v4(255,200,mouse.z*255,255));
  rect(v4(width/2,height/2,100,100));

  // show the gamepad interface
  gamepad();
}
