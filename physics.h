#include "raylib.h"
#include "rrfconstants.h"

int pcol,px,py=0; //Player Color, x, and y

#define NUM_ITEMS 7

Sound bumpsfx;

void bump() {
  playSound(SOUND_BUMP);
}

void breakblock() {
  playSound(SOUND_BREAK);
}

void push() {
  playSound(SOUND_PUSH);
}

void death() {
  playSound(SOUND_BREAK);
}

void opendoor() {

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

void gotolevel(int lvl) {
  clvl = lvl;
  bool found_spawn = false;
  for (int x=0; x<30; x++) {
    for (int y=0; y<20; y++) {
      if (getblock(x,y) == player) {
        found_spawn = true;
        px = x; py = y;
        break;
      }
    }
  }
  if (!found_spawn) {
    printf("Can't find player spawn\n");
  }
}


void checkCollision(int block, int dval, int xm, int ym) { //X modify, Y modify
  switch (tilecollision[block][dval]) {
    case PA: px+=xm; py+=ym; break;

    case PC:
    if (pcol == tileparams[block][dval]) {
      px+=xm; py+=ym;
    } else {
      bump();
    }
    break;

    case PT:
    pcol = tileparams[block][dval];
    px+=xm; py+=ym;
    break;

    case PG:

    playeritems[tileparams[block][dval]]++;
    rmblock(px+xm,py+ym);
    px+=xm; py+=ym;
    break;

  case PK:
    if (playeritems[tileparams[block][dval]] > air) {
      playeritems[tileparams[block][dval]]--;
      setblock(px+xm,py+ym,unlockedDoor,getdval(px+xm,py+ym));
      px+=xm; py+=ym;
      opendoor();
    } else {
      bump();
    }
    break;

  case PN:
    gotolevel(clvl+dval-7);
    break;

  case PP:
    if (!getblock(px+xm*2,py+ym*2)) {
      setblock(px+xm*2,py+ym*2,block,dval);
      rmblock(px+xm,py+ym);
      px+=xm; py+=ym;
      push();
    } else if (CURRMAP[px+xm*2][py+ym*2] == monster) {
      rmblock(px+xm,py+ym);
      rmblock(px+xm*2,py+ym*2);
      px+=xm; py+=ym;
      death();
    } else {
      bump();
    }
    break;

  case PB:
      rmblock(px+xm,py+ym);
      px+=xm; py+=ym;
      breakblock();
    break;

  case PS:
    bump(); break;
  }
}
