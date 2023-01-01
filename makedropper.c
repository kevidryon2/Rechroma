#include <stdio.h>
#include <string.h>

const char ddha[] = "char rechroma[] = {";

int main() {
  printf("Generating dropper source code...\n");
  FILE *rechromafp = fopen("./build/rechroma", "rb");
  FILE *dropperdatafp = fopen("dropperdata.h", "w");
  fprintf(dropperdatafp, ddha);
  int c;
  while ((c = getc(rechromafp)) != EOF) {
    fprintf(dropperdatafp, "0x%02x,", c);
  }
  fprintf(dropperdatafp, "}; ");
  fprintf(dropperdatafp, "int rel=%ld;", ftell(rechromafp));
}
