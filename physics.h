#include "raylib.h"
#include "rrfconstants.h"

int clvl;
rrf res;

int pcol,px,py=0; //Player Color, x, and y

typedef enum {
  PASS_ALWAYS = 0,
  PASS_COLOR,
  PASS_TRANSFORM,
  PASS_KEY,
  PASS_GIVE,
  PASS_NEXTLEVEL,
  PASS_SOLID,
  PASS_PUSH
} collision_type;

typedef enum {
  PA = PASS_ALWAYS,
  PC = PASS_COLOR,
  PT = PASS_TRANSFORM,
  PK = PASS_KEY,
  PG = PASS_GIVE,
  PN = PASS_NEXTLEVEL,
  PS = PASS_SOLID,
  PP = PASS_PUSH
} collision_type_short;

Color tilecolors[] = {
    BLACK,WHITE,WHITE,LIGHTGRAY,
    GOLD,ORANGE,RED,GOLD,VIOLET,BLUE,GREEN,
    GOLD,ORANGE,RED,MAGENTA,VIOLET,BLUE,GREEN,
    GOLD,ORANGE,RED,VIOLET,BLUE,GREEN,
    GOLD,ORANGE,RED,VIOLET,BLUE,GREEN,
    WHITE,WHITE
};

Color worldcolors[] = {
    WHITE,GOLD,ORANGE,RED,VIOLET,BLUE,GREEN,BLACK
};

int tileparams[] = {
  0,0,0,0,
  1,2,3,0,4,5,6,
  1,2,3,0,4,5,6,
  1,2,3,4,5,6,
  1,2,3,4,5,6,
  0,0
};

int tilecollision[] = {
  PA,PS,PP,PS,
  PC,PC,PC,PS,PC,PC,PC,
  PT,PT,PT,PS,PT,PT,PT,
  PG,PG,PG,PG,PG,PG,
  PK,PK,PK,PK,PK,PK,
  PN,PS

};

void checkCollision(int block, int xm, int ym) { //X modify, Y modify
  switch (tilecollision[block]) {
    case PA: px+=xm; py+=ym; break;

    case PC:
    if (pcol == tileparams[block]) {
      px+=xm;

    }
    break;

    case PT:
    pcol = tileparams[block];
    px+=xm; py+=ym;
    break;
  }
}
