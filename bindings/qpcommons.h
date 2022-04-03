#include "qplex.h"

typedef vec vec4;
typedef vec vec3;
typedef vec vec2;
#define mouse (input[0])
#define touch0 (input[0])
#define touch1 (input[1])

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

// set color
void color(vec c)
{
  col = c;
}

void rect(vec b)
{
  tri(v2(b.x,b.y), v2(b.x+b.z,b.y), v2(b.x+b.z,b.y+b.w), col);
  tri(v2(b.x,b.y), v2(b.x,b.y+b.w), v2(b.x+b.z,b.y+b.w), col);
}

// landscape dimensions
int lwidth;
int lheight;
// gamepad interface panel size
int panel_width;
// gamepad screen dim
int gx;
int gy;
int gcx;
int gcy;
int gwidth;
int gheight;
#ifndef qpc
#define qpc
int _qpinit=0;
#endif
typedef struct {
  int hidden;
  int value;
  int pvalue;
  vec bounds;
  vec color;
  int touchdown;
  int touchup;
} vbtn;
vbtn vbtns[10] = {};
#define LPAD_DCNT (vbtns[0])
#define LPAD_DRGT (vbtns[1])
#define LPAD_DUPB (vbtns[2])
#define LPAD_DLFT (vbtns[3])
#define LPAD_DDWN (vbtns[4])
#define RPAD_DCNT (vbtns[5])
#define RPAD_DRGT (vbtns[6])
#define RPAD_DUPB (vbtns[7])
#define RPAD_DLFT (vbtns[8])
#define RPAD_DDWN (vbtns[9])
#define VBTN_SIZE 10
void bonus_vars()
{
  lwidth = height; 
  lheight = width;
  panel_width = (lwidth-lheight)/2;
  gx = panel_width;
  gy = 0;
  gcx = gx+gwidth/2;
  gcy = gy+gheight/2;
  gwidth = lwidth-panel_width*2;
  gheight = lheight;
  if (!_qpinit)
  {
    vec c = v4(174, 174, 187, 255);
    int btn_size = 100;
    int btn_margin = 20;
    int dlt = btn_size + btn_margin;
    int x = panel_width/2; int y = lheight/2;
    for (vbtn* b=vbtns; b<vbtns+VBTN_SIZE; b++)
    {
      b->color = c;
    }
    LPAD_DCNT.hidden = 1;
    LPAD_DRGT.bounds = vl4c(x+dlt,y,btn_size,btn_size);
    LPAD_DUPB.bounds = vl4c(x,y-dlt,btn_size,btn_size); 
    LPAD_DLFT.bounds = vl4c(x-dlt,y,btn_size,btn_size); 
    LPAD_DDWN.bounds = vl4c(x,y+dlt,btn_size,btn_size); 
    
    x = lwidth - panel_width/2;
    RPAD_DCNT.bounds = vl4c(x,y,btn_size,btn_size);     
    RPAD_DRGT.bounds = vl4c(x+dlt,y,btn_size,btn_size); 
    RPAD_DUPB.bounds = vl4c(x,y-dlt,btn_size,btn_size); 
    RPAD_DLFT.bounds = vl4c(x-dlt,y,btn_size,btn_size); 
    RPAD_DDWN.bounds = vl4c(x,y+dlt,btn_size,btn_size); 
  }
  _qpinit = 1;
}

void vset(vbtn* btn, int value)
{
  btn->value = value;
  if (btn->value != btn->pvalue)
  {
    btn->touchdown = value;
    btn->touchup = !value;
  }
  else
  {
    btn->touchdown = btn->touchup = 0;
  }
  btn->pvalue = value;
}

int vbtn_draw(vbtn* btn)
{
  vec bounds = btn->bounds;
  vec _col = btn->color;
  //col
  int btnvalue = 0;
  if (mouse.z)
  {
    if (bounds.x < mouse.x)
    if (bounds.y < mouse.y)
    if (bounds.x+bounds.z > mouse.x)
    if (bounds.y+bounds.w > mouse.y)
      btnvalue = 1;
  }
  if (touch1.z)
  {
    if (bounds.x < touch1.x)
    if (bounds.y < touch1.y)
    if (bounds.x+bounds.z > touch1.x)
    if (bounds.y+bounds.w > touch1.y)
      btnvalue = 1;
  }
  if (btnvalue)
  {
    float brite = .9;
    col.x = 255-(255-col.x)*(1-brite);
    col.y = 255-(255-col.y)*(1-brite);
    col.z = 255-(255-col.z)*(1-brite);
  }
  rect(bounds);
  col = _col;
  vset(btn, btnvalue);
  return btnvalue;
}

int cpu_temp()
{
  // /sys/class/thermal/thermal_zone0/temp
}

// touch gamepad
void vgamepad()
{

  bonus_vars();
  color(v4(107, 67, 67, 255));
  rect(vl4(0,0,panel_width,lheight));
  rect(vl4(lwidth-panel_width,0,panel_width,lheight));

  for (vbtn* b=vbtns; b<vbtns+VBTN_SIZE; b++)
    vbtn_draw(b);
}

void gamepad()
{
  // in the future: poll input for capabilities
  // if the implementation is attached to something close enough
  // to a real controller, don't show this interface
  // (or if perhaps it has less than 2 contact points)

  vgamepad();
}
