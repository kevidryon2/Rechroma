#include <stdio.h>
#include <stdlib.h>
#include "crash.h"
#include <errno.h>
#include <math.h>

#pragma once

#define VERSTR "v0.03_01"

#define MAX_LEVELS (8*10)

const short currver = 0x0031;
const short currver_re = 0x3100;

typedef struct {
  char map[30][20];
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
}
