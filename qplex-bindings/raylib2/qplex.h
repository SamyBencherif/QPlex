#include "raylib.h"

void start();
void update();

int main()
{
  int screenWidth = 720;
  int screenHeight = 1440;

  SetConfigFlags(FLAG_FULLSCREEN_MODE);
  InitWindow(screenWidth, screenHeight, "raylib");

  SetTargetFPS(60);

  start(); 
  ClearBackground(BLACK);
  while (!WindowShouldClose())  
  {
    BeginDrawing();
    update();
    EndDrawing();
  }

  CloseWindow();    
  return 0;
}

typedef struct { float x; float y; float w; float z; } vec;

vec mouse() { 
  return (vec){
    GetMouseX(),
    GetMouseY(),
    IsMouseButtonDown(0),
    0};
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
