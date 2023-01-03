#include <stdio.h>
#include <stdlib.h>
#include "crash.h"
#include <errno.h>
#include <math.h>

#pragma once

#define VERSTR "v0.04"

#define MAX_LEVELS (8*10)

const short currver = 0x0040;
const short currver_re = 0x4000;

#define NUM_BLOCKS 8
#define MAX_DATAVALS 7

int blocktile[NUM_BLOCKS][MAX_DATAVALS] = {
    {0},
    {1,2,3,128},
    {4,5,6,7,8,9,10},
    {11,12,13,14,15,16,17},
    {18,19,20,21,22,23,24},
    {25,26,27,28,29,30,31},
    {129},
    {130}
};

typedef struct {
  char map[30][20];
  char dvalmap[30][20];
} leveldata;

typedef struct {
  short version;
  char checksum;
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
      crash("invalid data.rrf version", TextFormat("Version %04x",version));
    }
  }
  fread(&rrf_buffer->levels, sizeof(leveldata)*MAX_LEVELS, 1, data);
  char checksum = 0;
  for (int i=0; i<sizeof(rrf_buffer->levels); i++) {
    checksum += *(((char*)rrf_buffer->levels)+i) + i;
  }
  fclose(data);
}
