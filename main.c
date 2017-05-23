#include <stdio.h>
#include "parse.h"
#include "parse.c"


int main() {
  struct Line lineIn;
  char string[] = "This is a string";
  Parse(string, &lineIn);
  return 0;
}
