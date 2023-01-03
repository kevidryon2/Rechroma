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
#define CURRDVAL res.levels[clvl].dvalmap

void gotolevel(int lvl) {
  bool found_spawn = false;
  for (int x=0; x<30; x++) {
    for (int y=0; y<20; y++) {
      if (CURRMAP[x][y] == 7) {
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
      checkCollision(CURRMAP[px][py-1],CURRDVAL[px][py-1],0,-1);
      break;
    case KEY_S:
      checkCollision(CURRMAP[px][py+1],CURRDVAL[px][py+1],0,1);; break;
    case KEY_A:
      checkCollision(CURRMAP[px-1][py],CURRDVAL[px-1][py],-1,0);; break;
    case KEY_D:
      checkCollision(CURRMAP[px+1][py],CURRDVAL[px+1][py],1,0);; break;
  }
  px %= 30;
  px = (px<0)?29:px;
  py %= 20;
  py = (py<0)?19:py;
}

bool editor = false;

void ldraw() {
  for (int x=0; x<40; x++) {
    for (int y=0; y<30; y++) {
      cputc(
      blocktile [ CURRMAP[x][y] ] [ CURRDVAL[x][y] ], x, y,
      tilecolors[ CURRMAP[x][y] ] [ CURRDVAL[x][y] ], BLACK);
    }
  }
  cputc('A'+(clvl/10),0,19,worldcolors[clvl/10],BLACK);
  cputc('-',1,19,WHITE,BLACK);
  cputc('0'+clvl%10,2,19,WHITE,BLACK);
  cputc(player, px, py, worldcolors[pcol], BLACK);
  cputs(TextFormat("X:%02d Y:%02d",px,py),11,19,WHITE,BLACK);
}
