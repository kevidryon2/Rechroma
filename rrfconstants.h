#include <stdio.h>
#include <stdlib.h>
#include "crash.h"
#include <errno.h>
#include <math.h>
#include "blocks.h"

#pragma once

#define CURRMAP res.levels[clvl].map
#define CURRDVAL res.levels[clvl].dvalmap
#define VERSTR "v0.09"
#define MAX_LEVELS (8*10)

const short currver = 0x0090;
const char currbuild = 1;
const short currver_re = 0x9000;

#define NUM_SOUNDS 6

#define SOUND_CRASH 0
#define SOUND_BUMP 1
#define SOUND_BREAK 2
#define SOUND_PUSH 3
#define MUSIC_INTRO 4
#define MUSIC_LOOP 5

Sound sounds[NUM_SOUNDS];

char *soundnames[NUM_SOUNDS] = {
  "crash.wav","bump.wav","break.wav","push.wav", "music_intro.ogg", "music-loop.ogg"
};

void playSound(int sound) {
  PlaySound(sounds[sound]);
}

void loadSounds() {
  for (int i=0; i<NUM_SOUNDS; i++) {
    sounds[i] = LoadSound(soundnames[i]);
  }
}

typedef struct {
  char map[30][20];
  char dvalmap[30][20];
} leveldata;

typedef struct {
  short version;
  char build;
  leveldata levels[MAX_LEVELS];
} rrf;

rrf res; int clvl;

void setblock(int x, int y, int block, int dval) {
  CURRMAP[x][y] = block;
  CURRDVAL[x][y] = dval;
}

void rmblock(int x, int y) {
  CURRMAP[x][y] = 0;
  CURRDVAL[x][y] = 0;
}

int getblock(int x, int y) {
  return CURRMAP[x][y];
}

int getdval(int x, int y) {
  return CURRDVAL[x][y];
}

void ldrrf(rrf *rrf_buffer) {
  FILE *data = fopen(gameDataPath("assets/data.rrf"), "r");
  if (!data) {
    crash("can't access data.rrf",TextFormat("Errno: %d", errno));
  }
  short version = -555;
  char file_checksum = EOF;
  fread(&version, sizeof(char), 2, data);
  fread(&file_checksum, sizeof(char), 1, data);
  if (currver != version) {
    if (file_checksum == EOF) {
      crash("data.rrf is empty","");
    } else {
      printf("invalid data.rrf version %s\n", TextFormat("Version %04x",version));
    }
  }
  fread(&rrf_buffer->levels, sizeof(leveldata)*MAX_LEVELS, 1, data);

  fclose(data);
}
