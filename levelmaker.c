#include "raylib.h"
#include "levels.h"
#include "font.h"
#include <stdio.h>

int scrolloffset = -9;

rrf res;
int x,y;
int selb = 1;
int seld = 0;

void update() {
  x %= 30;
  x = (x<0)?29:x;
  y %= 19;
  y = (y<0)?19:y;
  int k = GetKeyPressed();
  switch (k) {
    case KEY_UP: y--; break;
    case KEY_DOWN: y++; break;
    case KEY_LEFT: x--; break;
    case KEY_RIGHT: x++; break;
  case KEY_Z: CURRMAP[x][y]=selb; CURRDVAL[x][y]=seld; break;
  case KEY_X: CURRMAP[x][y]=0; CURRDVAL[x][y]=0; break;
  case KEY_Q: dv1++; break;
  case KEY_W: dv1--; break;
  case KEY_J: clvl--; break;
  case KEY_K: clvl++; break;
  case KEY_U: seld--; break;
  case KEY_I: seld++; break;
  case KEY_O: selb--; break;
  case KEY_P: selb++; break;
  case KEY_D:
    for (int x=0; x<30; x++) {
      for (int y=0; y<20; y++) {
        res.levels[clvl].map[x][y] = 0;
      }
    }
    break;
  case KEY_S:;
    FILE *fp = fopen("data.rrf","w");
    res.version = currver;
    fwrite(&res,sizeof(rrf),1,fp);
    fseek(fp,0,SEEK_SET);
    fclose(fp);
    break;
  case KEY_L:
    ldrrf(&res);
    break;
  default:
    if (k >= KEY_ZERO & k <= KEY_NINE) {
      selb = k-KEY_ZERO;
    }
    break;
  }
  lupdate();
}

void draw() {
	ClearBackground(BLACK);
	ldraw();
  DrawRectangleLines(x*8*scalefactor,y*8*scalefactor,8*scalefactor,8*scalefactor,WHITE);
  
  cputs("SEL",4,19,GOLD,BLACK);
  cputc(':',  7,19,WHITE,BLACK);
  cputc(blocktile[selb][seld], 8,19,tilecolors[selb][seld],BLACK);
  cputc(0,9,19,tilecolors[selb][seld],BLACK);
  for (int i=9; i<40; i++) {
    //cputc(i+scrolloffset,i,19,tilecolors[i+scrolloffset],BLACK);
  }
  cputs(TextFormat("X:%02d Y:%02d B:%02d D:%02d",x,y,selb,seld),10,19,WHITE,BLACK);
}

int main() {
  editor = true;
  InitAudioDevice();
  if (!IsAudioDeviceReady ()){
    crash("Cannot initialize audio device","");
  }
	InitWindow(720,480,"Level Maker");
	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		update();
		BeginDrawing();
		draw();
		EndDrawing();
	}
}
