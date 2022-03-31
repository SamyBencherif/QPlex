#include "raylib.h"

typedef struct { float x; float y; float z; float w; } vec;

/*
const enum {
  NONE,
  VIRTUAL,
  POINT,
  MULTIPOINT,
} pntCap = ...;
my various (input) devices:
pinephone....................MULTIPOINT
mbp..........................POINT (MP with driver lvl hack)
rmk2.........................MULTIPOINT
PC+ext_mouse.................POINT 
PC+ext_keyboard..............VIRTUAL
PC+ext_gamepad               VIRTUAL
PC+ext_rmk2                  POINT
PC+ext_pinephone             MULTIPOINT
PC+ext_net_iphone            NONE
*/

/*
my various (input) devices:
pinephone..................._4BTN , practically _1BTN or _2BTN
mbp  _10PLUS
rmk2 _3BTN  more like _1BTN
PC+ext_mouse 2-3 btns
PC+ext_keyboard 10+
PC+ext_gamepad probably 10+
PC+ext_rmk2 10+
PC+ext_pinephone 10+
PC+ext_net_iphone 10+
*/

/*
my various (input) devices:
pinephone 2 accel? 2-3 virtual
mbp NONE
rmk2 NONE
PC+ext_mouse NONE or 1AX
PC+ext_keyboard NONE 
PC+ext_gamepad 6AX
PC+ext_rmk2 7PL virtual
PC+ext_pinephone 2 accel 2-5 virt
PC+ext_net_iphone same^ but less reliable
*/

/*
POINT_A          ...............................  X:f,Y:f,EXISTS:b
CONTACT_A        ...............................  DOWN:b,EXISTS:b
B,C,D
pointcontact = <x, y, down, 0:dne|1:pointeronly|2:pointercontact|3:contactonly>
4 vectors
      
BTN0 - BTN9      ...............................  DOWN:b,EXISTS:b
button = <down,exists,undef,undef>
10 vectors
               
AXA AXB AXC AXD AXE AXF ........................  V:f,EXISTS:b,PAIRED:b,CIRCULAR:b
axis = <value,exists,paired (2d),circular>
4 vectors

total of 20 input vectors
*/

void start();
void update();

int width = 720;
int height = 1440;

vec input[20]; 

int main()
{

  SetConfigFlags(FLAG_FULLSCREEN_MODE);
  InitWindow(width, height, "raylib");

  SetTargetFPS(60);

  start(); 
  ClearBackground(BLACK);
  while (!WindowShouldClose())  
  {
    BeginDrawing();

    input[0].x = GetMouseX();
    input[0].y = GetMouseY();
    input[0].z = IsMouseButtonDown(0);
    input[0].w = 1; // exists ? yes.

    input[1].x = 0; 
    input[1].y = 0;
    input[1].z = 0;
    input[1].w = 0; // exists ? no.

    update();
    EndDrawing();
  }

  CloseWindow();    
  return 0;
}

void tri(vec v1, vec v2, vec v3, vec col)
{
  DrawTriangle(
    (Vector2){v1.x,v1.y},
    (Vector2){v2.x,v2.y},
    (Vector2){v3.x,v3.y},
    (Color){col.x,col.y,col.z,col.w}
  );
  // vertex order agnostic (easier ! but half as efficient )
  DrawTriangle(
    (Vector2){v3.x,v3.y},
    (Vector2){v2.x,v2.y},
    (Vector2){v1.x,v1.y},
    (Color){col.x,col.y,col.z,col.w}
  );
}
