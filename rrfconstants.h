#include <stdio.h>
#include <stdlib.h>
#include "crash.h"
#include <errno.h>
#include <math.h>

#pragma once

#define VERSTR "v0.05"

#define MAX_LEVELS (8*10)

const short currver = 0x0050;
const short currver_re = 0x5000;

#define NUM_BLOCKS 70
#define MAX_DATAVALS 8

int blocktile[NUM_BLOCKS][MAX_DATAVALS] = {
    {0},
    {1,2,3,128},
    {4,5,6,7,8,9,10},
    {11,12,13,14,15,16,17},
    {18,19,20,21,22,23,24},
    {25,26,27,28,29,30,31},
    {129,129,129,129,129,129,129,129},
    {130},
	{'A','A','A','A','A','A','A','A'},
	{'B','B','B','B','B','B','B','B'},
	{'C','C','C','C','C','C','C','C'},
	{'D','D','D','D','D','D','D','D'},
	{'E','E','E','E','E','E','E','E'},
	{'F','F','F','F','F','F','F','F'},
	{'G','G','G','G','G','G','G','G'},
	{'H','H','H','H','H','H','H','H'},
	{'I','I','I','I','I','I','I','I'},
	{'J','J','J','J','J','J','J','J'},
	{'K','K','K','K','K','K','K','K'},
	{'L','L','L','L','L','L','L','L'},
	{'M','M','M','M','M','M','M','M'},
	{'N','N','N','N','N','N','N','N'},
	{'O','O','O','O','O','O','O','O'},
	{'P','P','P','P','P','P','P','P'},
	{'Q','Q','Q','Q','Q','Q','Q','Q'},
	{'R','R','R','R','R','R','R','R'},
	{'S','S','S','S','S','S','S','S'},
	{'T','T','T','T','T','T','T','T'},
	{'U','U','U','U','U','U','U','U'},
	{'V','V','V','V','V','V','V','V'},
	{'W','W','W','W','W','W','W','W'},
	{'X','X','X','X','X','X','X','X'},
	{'Y','Y','Y','Y','Y','Y','Y','Y'},
	{'Z','Z','Z','Z','Z','Z','Z','Z'},
	{'a','a','a','a','a','a','a','a'},
	{'b','b','b','b','b','b','b','b'},
	{'c','c','c','c','c','c','c','c'},
	{'d','d','d','d','d','d','d','d'},
	{'e','e','e','e','e','e','e','e'},
	{'f','f','f','f','f','f','f','f'},
	{'g','g','g','g','g','g','g','g'},
	{'h','h','h','h','h','h','h','h'},
	{'i','i','i','i','i','i','i','i'},
	{'j','j','j','j','j','j','j','j'},
	{'k','k','k','k','k','k','k','k'},
	{'l','l','l','l','l','l','l','l'},
	{'m','m','m','m','m','m','m','m'},
	{'n','n','n','n','n','n','n','n'},
	{'o','o','o','o','o','o','o','o'},
	{'p','p','p','p','p','p','p','p'},
	{'q','q','q','q','q','q','q','q'},
	{'r','r','r','r','r','r','r','r'},
	{'s','s','s','s','s','s','s','s'},
	{'t','t','t','t','t','t','t','t'},
	{'u','u','u','u','u','u','u','u'},
	{'v','v','v','v','v','v','v','v'},
	{'w','w','w','w','w','w','w','w'},
	{'x','x','x','x','x','x','x','x'},
	{'y','y','y','y','y','y','y','y'},
	{'z','z','z','z','z','z','z','z'},
	{'!','!','!','!','!','!','!','!'},
	{'?','?','?','?','?','?','?','?'},
	{'.','.','.','.','.','.','.','.'},
	{',',',',',',',',',',',',',',','},
	{':',':',':',':',':',':',':',':'},
	{';',';',';',';',';',';',';',';'},
	{'-','-','-','-','-','-','-','-'},
	{'+','+','+','+','+','+','+','+'},
	{'(','(','(','(','(','(','(','('},
	{')',')',')',')',')',')',')',')'}
};

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
      printf("invalid data.rrf version %s\n", TextFormat("Version %04x",version));
    }
  }
  fread(&rrf_buffer->levels, sizeof(leveldata)*MAX_LEVELS, 1, data);
  char checksum = 0;
  for (int i=0; i<sizeof(rrf_buffer->levels); i++) {
    checksum += *(((char*)rrf_buffer->levels)+i) + i;
  }
  fclose(data);
}
