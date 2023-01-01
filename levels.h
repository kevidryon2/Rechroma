#include "raylib.h"
#include "font.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "rrfconstants.h"
#include "crash.h"
#include <unistd.h>

int clvl = 0;
rrf res;

int px,py=0;


typedef enum {
  PASS_ALWAYS = 0,
  PASS_COLOR,
  PASS_TRANSFORM,
  PASS_KEY,
  PASS_NEXTLEVEL,
  PASS_SOLID
} collision_type;

typedef enum {
  PA = PASS_ALWAYS,
  PC = PASS_COLOR,
  PT = PASS_TRANSFORM,
  PK = PASS_KEY,
  PN = PASS_NEXTLEVEL,
  PS = PASS_SOLID
} collision_type_short;

void gotolevel(int lvl) {
  bool found_spawn = false;
  for (int x=0; x<30; x++) {
    for (int y=0; y<30; y++) {
      if (res.levels[clvl][x][y] == player) {
        found_spawn = true;
        px = x; py = y;
      }
    }
  }
}

void linit() {
  
}

void lupdate() {
  switch (GetKeyPressed()) {
    case KEY_W:
      switch (res.levels[clvl][px][py-1]) {
      case 0:
        py--;
      }
      break;
    case KEY_S: py++; break;
    case KEY_A: px--; break;
    case KEY_D: px++; break;
  }
}

Color tilecolors[] = {
    BLACK,WHITE,WHITE,LIGHTGRAY,
    GOLD,ORANGE,RED,MAGENTA,VIOLET,BLUE,GREEN,
    GOLD,ORANGE,RED,MAGENTA,VIOLET,BLUE,GREEN,
    GOLD,ORANGE,RED,VIOLET,BLUE,GREEN,
    GOLD,ORANGE,RED,VIOLET,BLUE,GREEN,
    WHITE,WHITE
};

Color worldcolors[] = {
    WHITE,GOLD,ORANGE,RED,PINK,VIOLET,BLUE,GREEN,BLACK
};

int tileparams[] = {
  0,0,0,0,1,2,3,4,5,6,7,
};

int tilecollision[] = {
  PA,PS,PS,PS,
  PC,PC,PC,PC,PC,PC,PC,
  PT,PT,PT,PT,PT,PT,PT,
  PA,PA,PA,PA,PA,PA,
  PK,PK,PK,PK,PK,PK,
  PN,PS
  
};

bool editor = false;

void ldraw() {
  for (int x=0; x<40; x++) {
    for (int y=0; y<30; y++) {
      cputc(res.levels[clvl][x][y], x, y, tilecolors[res.levels[clvl][x][y]], BLACK);
    }
  }
  cputc('A'+(clvl/10),0,19,worldcolors[clvl/10],BLACK);
  cputc('-',1,19,WHITE,BLACK);
  cputc('0'+clvl%10,2,19,WHITE,BLACK);
  if (!editor) cputc(31, px, py, WHITE, BLACK);
}
