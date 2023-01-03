#include "raylib.h"
#include "rrfconstants.h"

#define CURRMAP res.levels[clvl].map
#define CURRDVAL res.levels[clvl].dvalmap

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
  PASS_BREAK,
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
  PB = PASS_BREAK,
  PP = PASS_PUSH
} collision_type_short;

Color tilecolors[NUM_BLOCKS][MAX_DATAVALS] = {
    {BLACK},
    {WHITE,WHITE,LIGHTGRAY,WHITE},
    {GOLD,ORANGE,RED,MAGENTA,VIOLET,BLUE,GREEN},
    {GOLD,ORANGE,RED,MAGENTA,VIOLET,BLUE,GREEN},
    {GOLD,ORANGE,RED,MAGENTA,VIOLET,BLUE,GREEN},
    {GOLD,ORANGE,RED,MAGENTA,VIOLET,BLUE,GREEN},
    WHITE,WHITE
};

Color worldcolors[] = {
    WHITE,GOLD,ORANGE,RED,MAGENTA,VIOLET,BLUE,GREEN,BLACK
};

int tileparams[NUM_BLOCKS][MAX_DATAVALS] = {
    {0},
    {0,0,0,0},
    {1,2,3,4,5,6,7},
    {1,2,3,4,5,6,7},
    {1,2,3,4,5,6,7},
    {1,2,3,4,5,6,7},
    {0},
    {0}
};

int tilecollision[NUM_BLOCKS][MAX_DATAVALS] = {
  {PA},
  {PS,PP,PB,PS},
  {PC,PC,PC,PC,PC,PC,PC},
  {PT,PT,PT,PT,PT,PT,PT},
  {PG,PG,PG,PG,PG,PG,PG},
  {PK,PK,PK,PK,PK,PK,PK},
  {PN},
  {PS}

};

#define NUM_ITEMS 7

void bump() {
  //TODO play bump sfx
}

int playeritems[NUM_ITEMS];

int item_to_id[NUM_ITEMS][2] = {
  {4,0},
  {4,1},
  {4,2},
  {4,3},
  {4,4},
  {4,5},
  {4,6}
};

void checkCollision(int block, int dval, int xm, int ym) { //X modify, Y modify
  printf("%d %d %d\n", tilecollision[block][dval], pcol, tileparams[block][dval]);
  switch (tilecollision[block][dval]) {
    case PA: px+=xm; py+=ym; break;

    case PC:
    if (pcol == tileparams[block][dval]) {
      px+=xm; py+=ym;
    }
    break;

    case PT:
    pcol = tileparams[block][dval];
    px+=xm; py+=ym;
    break;

    case PG:

    playeritems[tileparams[block][dval]]++;
    CURRMAP[px+xm][py+ym] = 0;
    px+=xm; py+=ym;
    break;

  case PK:
    if (playeritems[tileparams[block][dval]] > 0) {
      playeritems[tileparams[block][dval]]--;
      px+=xm; py+=ym;
    } else {

    }
  }
}
