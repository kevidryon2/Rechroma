#include <stdio.h>
#include <stdlib.h>
#include "crash.h"
#include <errno.h>
#include <math.h>

#pragma once

#define MAX_LEVELS (8*10)

const short currver = 0x0030;
const short currver_re = 0x3000;

typedef char levelmap[30][20];

typedef struct {
  short version; 
  char checksum;
  levelmap levels[MAX_LEVELS];
} rrf;

void ldrrf(rrf *rrf_buffer) {
  printf("a\n");
  FILE *data = fopen(gameDataPath("data.rrf"), "r");
  if (!data) {
    crash("missing data.rrf",TextFormat("Errno: %d", errno));
  }
  short version = -555;
  char file_checksum = EOF;
  printf("a\n");
  fread(&version, sizeof(char), 2, data);
  fread(&file_checksum, sizeof(char), 1, data);
  printf("a\n");
  printf("a\n");
  if (currver != version) {
    if (file_checksum == EOF) {
      crash("data.rrf is empty","");
    } else {
      crash("invalid data.rrf version", TextFormat("Version %04x",version));
    }
  }
  printf("c\n");
  fread(&rrf_buffer->levels, sizeof(levelmap)*MAX_LEVELS, 1, data);
  printf("c\n");
  char checksum = 0;
  for (int i=0; i<sizeof(rrf_buffer->levels); i++) {
    checksum += *(((char*)rrf_buffer->levels)+i) + i;
  }
}
