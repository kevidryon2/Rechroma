#include "raylib.h"
#include "font.h"
#include "transitions.h"

#define STATE_GAME 1

Color titlecolors[6] = {RED,ORANGE,GOLD,GREEN,BLUE,VIOLET};

char chroma[] = "CHROMA";

int tcre[6] = {0,1,2,3,4,5}; 

void tinit() {
  SetTargetFPS(20);
}

void tupdate() {
  int bk = tcre[5];
  tcre[5] = tcre[0];
  tcre[0] = tcre[1];
  tcre[1] = tcre[2];
  tcre[2] = tcre[3];
  tcre[3] = tcre[4];
  tcre[4] = bk;
  if (IsKeyPressed(KEY_SPACE)) {
    //TODO: Play "click" animation
    fadeToBlack(15);
    executeState(STATE_GAME);
  }
}

void tdraw() {
  ClearBackground(BLACK);
  cputsbig("RE", 7, 5, WHITE, BLACK);
  for (int i=0; i<6; i++) {
    cputcbig(chroma[i], 11+(i*2), 5, titlecolors[tcre[i]], BLACK);
  }
  cputs("Press SPACE to start", 5, 8, WHITE, BLACK);
}
