#include "font.h"
#include "gamedatapath.h"

#pragma once

void crash(char *desc, char *otherdesc) {
  PlaySound(LoadSound(gameDataPath("assets/crash.mp3")));
  cputs("RECHROMA Crashed!", 0, 0, WHITE, RED);
  cputs(desc, 0, 2, WHITE, RED);
  cputs(otherdesc, 0, 4, WHITE, RED);
  while (!WindowShouldClose()){BeginDrawing();EndDrawing();}
  exit(127);
}
