#include "raylib.h"
#include <stdlib.h>
#include "titlescreen.h"
#include "levels.h"

#define NUM_GAMESTATES 2

#define STATE_TITLESCREEN 0
#define STATE_LEVEL 1

#define DEBUGK1 KEY_ONE
#define DEBUGK2 KEY_TWO
#define DEBUGK3 KEY_THREE
#define DEBUGK4 KEY_FOUR

char *nothingness;

const struct {
  void (*initfn)();
  void (*updatefn)();
  void (*drawfn)();
} states[NUM_GAMESTATES] = {
    {tinit, tupdate, tdraw},
    {linit, lupdate, ldraw},
};

void executeState(int state) {
  states[state].initfn();
  while (!WindowShouldClose()) {
    void *malloc_tester = malloc(1);
    if (!malloc_tester) {
      free(nothingness);
      crash("Out of memory","");
    }
    free(malloc_tester);
		states[state].updatefn();
		BeginDrawing();
		states[state].drawfn();
		EndDrawing();
    if (IsKeyPressed(DEBUGK1)) {
      if (IsKeyDown(KEY_LEFT_SHIFT)) {
        dv1--;
      } else {
        dv1++;
      }
    } else if (IsKeyPressed(DEBUGK2)) {
      if (IsKeyDown(KEY_LEFT_SHIFT)) {
        dv2--;
      } else {
        dv2++;
      }
    } else if (IsKeyPressed(DEBUGK3)) {
      if (IsKeyDown(KEY_LEFT_SHIFT)) {
        dv3--;
      } else {
        dv3++;
      }
    } else if (IsKeyPressed(DEBUGK4)) {
      if (IsKeyDown(KEY_LEFT_SHIFT)) {
        dv4--;
      } else {
        dv4++;
      }
    }
    cputs(VERSTR, 0, 19, WHITE, BLACK);
  }
  exit(0);
}

Texture rechromalogo;
struct {Image i;Texture t;} rechromalogo_small;

int main() {
  nothingness = (char*)malloc(355360);
	InitWindow(720,480,"Rechroma");
	SetTargetFPS(60);
  rechromalogo=LoadTexture("assets/rechromalogo.png");
  rechromalogo_small.i=LoadImage("assets/rechromalogo.png");
  ImageResizeNN(&rechromalogo_small.i,16,16);
  rechromalogo_small.t=LoadTextureFromImage(rechromalogo_small.i);
  SetWindowIcon(rechromalogo_small.i);
  InitAudioDevice();
  bumpsfx = LoadSound("bump.wav");
  if (!IsAudioDeviceReady()) {
    crash("Cannot initialize audio", "");
  }

  ldrrf(&res);
  
	executeState(STATE_TITLESCREEN);
}

