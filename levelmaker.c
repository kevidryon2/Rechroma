#include "raylib.h"
#include "levels.h"
#include "font.h"
#include <stdio.h>

int scrolloffset = -9;

rrf res;
int x,y,selb = 1;

void update() {
  int k = GetKeyPressed();
  switch (k) {
    case KEY_UP: y--; break;
    case KEY_DOWN: y++; break;
    case KEY_LEFT: x--; break;
    case KEY_RIGHT: x++; break;
  case KEY_Z: res.levels[clvl][x][y]=selb; break;
  case KEY_X: res.levels[clvl][x][y]=0; break;
  case KEY_Q: dv1++; break;
  case KEY_W: dv1--; break;
  case KEY_J: clvl--; break;
  case KEY_K: clvl++; break;
  case KEY_O: selb--; break;
  case KEY_P: selb++; break;
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
}

void draw() {
	ClearBackground(BLACK);
	ldraw();
  DrawRectangleLines(x*8*scalefactor,y*8*scalefactor,8*scalefactor,8*scalefactor,WHITE);
  
  cputs("SEL",4,19,GOLD,BLACK);
  cputc(':',  7,19,WHITE,BLACK);
  cputc(selb, 8,19,tilecolors[selb],BLACK);
  for (int i=9; i<40; i++) {
    //cputc(i+scrolloffset,i,19,tilecolors[i+scrolloffset],BLACK);
  }
  cputs(TextFormat("X:%02d Y:%02d",x,y),11,19,WHITE,BLACK);
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
