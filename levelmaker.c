#include "raylib.h"
#include "levels.h"
#include "font.h"
#include <stdio.h>

int scrolloffset = -9;

rrf res;
int cx,cy;
int selb = 1;
int seld = 0;

void detectkey(int k) {
  switch (k) {
    case KEY_UP: cy--; break;
    case KEY_DOWN: cy++; break;
    case KEY_LEFT: cx--; break;
    case KEY_RIGHT: cx++; break;
  case KEY_Z: CURRMAP[cx][cy]=selb; CURRDVAL[cx][cy]=seld; break;
  case KEY_X: CURRMAP[cx][cy]=0; CURRDVAL[cx][cy]=0; break;
  case KEY_Q: dv1++; break;
  case KEY_W: dv1--; break;
  case KEY_J: clvl--; break;
  case KEY_K: clvl++; break;
  case KEY_U: seld--; break;
  case KEY_I: seld++; break;
  case KEY_O: selb--; break;
  case KEY_P: selb++; break;
  case KEY_DELETE:
    for (int x=0; x<30; x++) {
      for (int y=0; y<20; y++) {
        CURRMAP[x][y] = 0;
        CURRDVAL[x][y] = 0;
      }
    }
    break;
  case KEY_S:;
    FILE *fp = fopen(gameDataPath("assets/data.rrf"),"w");
    res.version = currver;
    res.build = currbuild;
    fwrite(&res,sizeof(rrf),1,fp);
    fclose(fp);
    fp = fopen("data.rrf","w");
    res.version = currver;
    fwrite(&res,sizeof(rrf),1,fp);
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
  case KEY_Y:
    selb = 0; break;
  case KEY_T:
    seld = 0; break;
  case KEY_E:
    selb=CURRMAP[cx][cy]; seld=CURRDVAL[cx][cy]; break;
  case KEY_F:
    for (int x=0; x<30; x++) {
      for (int y=0; y<20; y++) {
        CURRMAP[x][y] = selb;
        CURRDVAL[x][y] = seld;
      }
    }
    break;
  case KEY_R:;
    detectkey(KEY_S);
    gotolevel(clvl);
    editor=false;
    while (!IsKeyPressed(KEY_E)) {
      BeginDrawing();
      lupdate();
      ldraw();
      EndDrawing();
    }
    editor=true;
    detectkey(KEY_L);
    break;
  }
}

void update() {
  cx = (cx>29)?29:cx;
  cx = (cx<0)?0:cx;
  cy = (cy>18)?18:cy;
  cy = (cy<0)?0:cy;
  int k;
  while (k = GetKeyPressed()) {
    detectkey(k);
  }
  t++;
  if (t==480) {
    playSound(MUSIC_LOOP);
  } else if (!((t-480)%1620)) {
    playSound(MUSIC_LOOP);
  }
}

void draw() {
	ClearBackground(BLACK);
  for (int i=0; i<30; i++) {
    cputc(0,i,19,WHITE,(Color){32,32,32,255});
  }

	ldraw();

  DrawRectangleLines(cx*8*scalefactor,cy*8*scalefactor,8*scalefactor,8*scalefactor,WHITE);
  
  cputs("SEL",4,19,GOLD,(Color){32,32,32,255});
  cputc(':',  7,19,WHITE,(Color){32,32,32,255});
  cputc(blocktile[selb][seld], 8,19,tilecolors[selb][seld],(Color){32,32,32,255});
  cputc(0,9,19,tilecolors[selb][seld],(Color){32,32,32,255});
  for (int i=9; i<40; i++) {
    //cputc(i+scrolloffset,i,19,tilecolors[i+scrolloffset],BLACK);
  }
  cputs(TextFormat("X:%02d Y:%02d B:%02d D:%02d",cx,cy,selb,seld),10,19,WHITE,(Color){32,32,32,255});
}

int main() {
  editor = true;
  InitAudioDevice();
  if (!IsAudioDeviceReady ()){
    crash("Cannot initialize audio device","");
  }
	InitWindow(720,480,"Level Maker");
	SetTargetFPS(30);
  loadSounds();
  playSound(MUSIC_INTRO);
	while (!WindowShouldClose()) {
		update();
		BeginDrawing();
		draw();
		EndDrawing();
	}
}
