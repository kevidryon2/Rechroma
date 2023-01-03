#include "raylib.h"
#include <stdio.h>
#include <errno.h>
#include "rrfconstants.h"

char dbuff[16*65536];

bool started = false;

void update() {
  if (IsKeyPressed(KEY_R)) {
    system("~/.rechroma/rechroma &");
  } else if (IsKeyPressed(KEY_E)) {
    system("~/.rechroma/maker &");
  }
}

//TODO: make rest api that returns title and image of rechroma news articles

Texture rechromalogo;
struct {Image i;Texture t;} rechromalogo_small;

void draw() {
  DrawRectangle(0,400,640,80,(Color){32,32,32,255});
  DrawRectangle(0,0,640,50,(Color){16,16,16,255});
  DrawText("RECHROMA Launcher", 10, 12, 30, RAYWHITE);
  //DrawTexture(rechromalogo, MeasureText("Rechroma Launcher",30)+20, 10, WHITE);
  if (started) {
    DrawText("Press X to stop RECHROMA", 10, 415, 20, RAYWHITE); 
  } else {
    DrawText(TextFormat("Press R to launch RECHROMA     Press E to launch editor\nCurrent version: %s", VERSTR), 10, 415, 20, RAYWHITE);
  }
  DrawText("News",275,60,30,RAYWHITE);
}

int main() {
  InitWindow(640,480,"RECHROMA Launcher");
  SetTargetFPS(60);
  rechromalogo=LoadTexture("assets/rechromalogo.png");
  rechromalogo_small.i=LoadImage("assets/rechromalogo.png");
  ImageResizeNN(&rechromalogo_small.i,16,16);
  rechromalogo_small.t=LoadTextureFromImage(rechromalogo_small.i);
  SetWindowIcon(rechromalogo_small.i);
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground((Color){64,64,64,255});
    draw();
    update();
    EndDrawing();
  }
}
