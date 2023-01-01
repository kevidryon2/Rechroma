#ifdef linux
#define LINUX 1
#include <unistd.h>
#else
#define LINUX 0
#include "lwal.h" //Linux on Windows Abstraction Layer
#endif

#include "raylib.h"

const char *gameDataPath(char *name) {
  char namebuf[256];
  getlogin_r(namebuf, (size_t)256);
  return (LINUX ? TextFormat("/home/%s/.rechroma/%s", namebuf, name) : TextFormat("c://users/%s/AppData/Roaming/Rechroma/%s",namebuf,name));
}
