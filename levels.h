#include "raylib.h"
#include "font.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "rrfconstants.h"
#include "crash.h"
#include <unistd.h>
#include "physics.h"

//TODO v0.04: Work on a system where every block has a data value

#define CURRMAP res.levels[clvl].map

void gotolevel(int lvl) {
  bool found_spawn = false;
  for (int x=0; x<30; x++) {
    for (int y=0; y<20; y++) {
      if (CURRMAP[x][y] == player) {
        found_spawn = true;
        px = x; py = y;
        CURRMAP[x][y] = 0;
      }
    }
  }
}

void linit() {
  gotolevel(0);
}

void lupdate() {
  switch (GetKeyPressed()) {
    case KEY_W:
      checkCollision(CURRMAP[px][py-1],0,-1);
      break;
    case KEY_S: py++; break;
    case KEY_A: px--; break;
    case KEY_D: px++; break;
    case KEY_U: pcol--; break;
    case KEY_I: pcol++; break;
  }
}

bool editor = false;

void ldraw() {
  for (int x=0; x<40; x++) {
    for (int y=0; y<30; y++) {
      cputc(CURRMAP[x][y], x, y, tilecolors[CURRMAP[x][y]], BLACK);
    }
  }
  cputc('A'+(clvl/10),0,19,worldcolors[clvl/10],BLACK);
  cputc('-',1,19,WHITE,BLACK);
  cputc('0'+clvl%10,2,19,WHITE,BLACK);
  cputc(player, px, py, worldcolors[pcol], BLACK);
  cputs(TextFormat("X:%02d Y:%02d",px,py),11,19,WHITE,BLACK);
}
