#include "qpcommons.h"

void start()
{
}

int left=0;
void update()
{
  bonus_vars();

  // clear background
  color(v4(255,255,255,255));
  rect(v4(0,0,width,height));

  // place colorful square in the white screen
  color(v4(255,200,mouse.z*255,255));
  rect(vl4(gwidth/2+left,gheight/2,100,100));
  color(v4(0,0,0,255));
  rect(vl4(gwidth/2,gheight/2-100,100,100));

  if (LPAD_DLFT.touchdown) left-=100;
  if (LPAD_DRGT.touchdown) left+=100;

  // show the gamepad interface
  gamepad();
}
