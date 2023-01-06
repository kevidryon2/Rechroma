#include <stdio.h>
#include <stdlib.h>
#include "crash.h"
#include <errno.h>
#include <math.h>
#include "blocks.h"

#pragma once

#define VERSTR "v0.08p2"

#define MAX_LEVELS (8*10)

const short currver = 0x0080;
const char currbuild = 1;
const short currver_re = 0x8000;
#define NUM_SOUNDS 4

#define SOUND_CRASH 0
#define SOUND_BUMP 1
#define SOUND_BREAK 2
#define SOUND_PUSH 3

Sound sounds[NUM_SOUNDS];

char *soundnames[NUM_SOUNDS] = {
  "crash.wav","bump.wav","break.wav","push.wav"
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
