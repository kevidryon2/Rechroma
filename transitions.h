#include "raylib.h"
void fadeToBlack(int duration) {
  SetTargetFPS(30);
  for (int i=0; i<duration; i++) {
    DrawRectangle(0, 0, 99999, 99999, (Color){0,0,0,(255/duration)*3});
    EndDrawing();
    BeginDrawing();
  }
}
void fadeFromBlack(int duration) {
  SetTargetFPS(30);
  for (int i=0; i<duration; i++) {
    DrawRectangle(0, 0, 99999, 99999, (Color){0,0,0,i/(duration)});
    EndDrawing();
    BeginDrawing();
  }
}
