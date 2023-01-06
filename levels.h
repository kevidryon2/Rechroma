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

#define DEFAULT_MMT 20
#define DEFAULT_SWT 10
#define ATTACK_MMT 6

bool editor = false;

int mmt = DEFAULT_MMT; //Monster Move Timer
int mwandering = true;
int swt = 0; //Start Wondering Timer

typedef enum {
  up, down, left, right
} Direction;

struct {int xi, yi;} pos_dir[4] = {
    {0,-1},
    {0,1},
    {-1,0},
    {1,0}
};

typedef struct {
          int oldx; int oldy; int newx; int newy;
        } ScheduledMovement;

void linit() {
  gotolevel(0);
}

int t = 0;

void lupdate() {
  t++;
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
  px = (px>29)?29:px;
  px = (px<0)?0:px;
  py = (py>18)?18:py;
  py = (py<0)?0:py;
  if (!editor) {
    mmt--;
    if (!mmt) {
      if (mwandering) {
        mmt = DEFAULT_MMT;
        int dir = rand()%4;
        for (int x=0; x<30; x++) {
          for (int y=0; y<20; y++) {
            if (CURRMAP[x][y] == monster) {
              while (CURRMAP[x+pos_dir[dir].xi][y+pos_dir[dir].yi]) dir = rand()%4;
              rmblock(x,y);
              setblock(x+pos_dir[dir].xi,y+pos_dir[dir].yi,monster,0);
              if (abs(x-px) < 5 & abs(y-py) < 5) {
                swt += 3;
              }
            }
          }
        }
      }
    }
  }
}

void ldraw() {
  for (int x=0; x<40; x++) {
    for (int y=0; y<30; y++) {
      if (show_only_editor[CURRMAP[x][y]][CURRDVAL[x][y]]) {
        if (editor) {
          cputc(
          blocktile [ getblock(x,y) ] [ getdval(x,y) ], x, y,
          tilecolors[ getblock(x,y) ] [ getblock(x,y) ], BLACK);
        }
      } else {
        cputc(
        blocktile [ CURRMAP[x][y] ] [ CURRDVAL[x][y] ], x, y,
        tilecolors[ CURRMAP[x][y] ] [ CURRDVAL[x][y] ], BLACK);
      }
    }
  }
  cputc('A'+(clvl/10),0,19,worldcolors[clvl/10],(Color){32,32,32,255});
  cputc('-',1,19,WHITE,(Color){32,32,32,255});
  cputc('0'+clvl%10,2,19,WHITE,(Color){32,32,32,255});
  cputc(blocktile[player][0], px, py, worldcolors[pcol], BLANK);
  cputs(TextFormat(" X:%02d Y:%02d                                ",px,py),3,19,WHITE,(Color){32,32,32,255});
  int x=14;
  for (int i=0; i<NUM_ITEMS; i++) {
    for (int j=0; j<playeritems[i]; j++) {
      int *item = item_to_id[i];
      cputc(blocktile[item[0]][item[1]], x, 19, tilecolors[item[0]][item[1]], (Color){32,32,32,255});
      x++;
    }
  }
}
