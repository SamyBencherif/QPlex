#include "qplex.h"

typedef vec vec4;
typedef vec vec3;
typedef vec vec2;
#define mouse (touches[0])

vec v2(float x, float y)
{
  return (vec){x,y,0,0};
}

vec vl2(float y, float x)
{
  return (vec){x,y,0,0};
}

vec v4(float x, float y, float z, float w)
{
  return (vec){x,y,z,w};
}

vec v4c(float x, float y, float z, float w)
{
  return (vec){x-z/2,y-w/2,z,w};
}

vec vl4(float y, float x, float w, float z)
{
  return (vec){x,y,z,w};
}

vec vl4c(float y, float x, float w, float z)
{
  return (vec){x-z/2,y-w/2,z,w};
}

vec col = {255,255,255,255};

void color(vec c)
{
  col = c;
}

void rect(vec b)
{
  tri(v2(b.x,b.y), v2(b.x+b.z,b.y), v2(b.x+b.z,b.y+b.w), col);
  tri(v2(b.x,b.y), v2(b.x,b.y+b.w), v2(b.x+b.z,b.y+b.w), col);
}

int lwidth;
int lheight;
int panel_width;
int gwidth;
int gheight;
void bonus_vars()
{
  lwidth = height; 
  lheight = width;
  panel_width = (lwidth-lheight)/2;
  gwidth = lwidth-panel_width*2;
  gheight = lheight;

}

// keyboard gamepad
void kgamepad();

// real gamepad
void rgamepad();

// touch gamepad
void tgamepad()
{
  bonus_vars();
  color(v4(107, 67, 67, 255));
  rect(vl4(0,0,panel_width,lheight));
  rect(vl4(lwidth-panel_width,0,panel_width,lheight));

  color(v4(174, 174, 187, 255));
  int btn_size = 100;
  int btn_margin = 20;
  int dlt = btn_size + btn_margin;
  int x = panel_width/2; int y = lheight/2;
  //rect(vl4c(x,y,btn_size,btn_size));   // LPAD D-CNT
  rect(vl4c(x+dlt,y,btn_size,btn_size)); // LPAD D-RGT
  rect(vl4c(x,y-dlt,btn_size,btn_size)); // LPAD D-UPB
  rect(vl4c(x-dlt,y,btn_size,btn_size)); // LPAD D-LFT
  rect(vl4c(x,y+dlt,btn_size,btn_size)); // LPAD D-DWN
  
  x = lwidth - panel_width/2;
  rect(vl4c(x,y,btn_size,btn_size));     // RPAD D-CNT
  rect(vl4c(x+dlt,y,btn_size,btn_size)); // RPAD D-RGT
  rect(vl4c(x,y-dlt,btn_size,btn_size)); // RPAD D-UPB
  rect(vl4c(x-dlt,y,btn_size,btn_size)); // RPAD D-LFT
  rect(vl4c(x,y+dlt,btn_size,btn_size)); // RPAD D-DWN
}
