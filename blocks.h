#include "raylib.h"

#define NUM_BLOCKS 13
#define MAX_DATAVALS 16

typedef enum {
  air = 0,
  stone, colored, dye, key, door, unlockedDoor, warp, player, monster
} blockid;

bool show_only_editor[NUM_BLOCKS][MAX_DATAVALS] = {
    {false},
    {false,false,false,false},
    {false,false,false,false,false,false,false,false},
    {false,false,false,false,false,false,false,false},
    {false,false,false,false,false,false,false,false},
    {false,false,false,false,false,false,false,false},
    {false,false,false,false,false,false,false,false},
    {true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true},
    {true},
    {false}
};

int blocktile[NUM_BLOCKS][MAX_DATAVALS] = {
    {0}, //air
    {1,2,3,8}, //stone
    {4,4,4,4,4,4,4}, //colored
    {5,5,5,5,5,5,5}, //dye
    {6,6,6,6,6,6,6}, //key
    {7,7,7,7,7,7,7}, //door
    {12,12,12,12,12,12,12}, //unlocked door
    {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9}, //warp
    {10}, //player
    {11}, //monster
};

typedef enum {
  PASS_ALWAYS = 0,
  PASS_COLOR,
  PASS_TRANSFORM,
  PASS_KEY,
  PASS_GIVE,
  PASS_NEXTLEVEL,
  PASS_SOLID,
  PASS_BREAK,
  PASS_PUSH
} collision_type;

typedef enum {
  PA = PASS_ALWAYS,
  PC = PASS_COLOR,
  PT = PASS_TRANSFORM,
  PK = PASS_KEY,
  PG = PASS_GIVE,
  PN = PASS_NEXTLEVEL,
  PS = PASS_SOLID,
  PB = PASS_BREAK,
  PP = PASS_PUSH
} collision_type_short;

Color tilecolors[NUM_BLOCKS][MAX_DATAVALS] = {
    {BLACK},
    {WHITE,WHITE,LIGHTGRAY,WHITE},
    {GOLD,ORANGE,RED,MAGENTA,VIOLET,BLUE,GREEN},
    {GOLD,ORANGE,RED,MAGENTA,VIOLET,BLUE,GREEN},
    {GOLD,ORANGE,RED,MAGENTA,VIOLET,BLUE,GREEN},
    {GOLD,ORANGE,RED,MAGENTA,VIOLET,BLUE,GREEN},
    {GOLD,ORANGE,RED,MAGENTA,VIOLET,BLUE,GREEN},
    {WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE},
    {WHITE},
    {WHITE},
};

Color worldcolors[] = {
    WHITE,GOLD,ORANGE,RED,MAGENTA,VIOLET,BLUE,GREEN,BLACK
};

int tileparams[NUM_BLOCKS][MAX_DATAVALS] = {
    {0},
    {0,0,0,0},
    {1,2,3,4,5,6,7},
    {1,2,3,4,5,6,7},
    {0,1,2,3,4,5,6},
    {0,1,2,3,4,5,6},
    {0,1,2,3,4,5,6},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0},
    {0},
};

int tilecollision[NUM_BLOCKS][MAX_DATAVALS] = {
  {PA},
  {PS,PP,PB,PS},
  {PC,PC,PC,PC,PC,PC,PC},
  {PT,PT,PT,PT,PT,PT,PT},
  {PG,PG,PG,PG,PG,PG,PG},
  {PK,PK,PK,PK,PK,PK,PK},
  {PA,PA,PA,PA,PA,PA,PA},
  {PN,PN,PN,PN,PN,PN,PN,PN,PN,PN,PN,PN,PN,PN,PN,PN},
  {PA},
  {PS},
};
