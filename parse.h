#ifndef PARSE_H
#define PARSE_H
#include <stdbool.h>

struct Command {
  int numArgs;
  char *command;
  char **arguments;
};

struct Line {
  char * ifile;
  bool inApp; //true: << false: <
  char * ofile;
  char * efile;
  bool outAmp; //true: >& false: >
  struct Command *commands[16];
};

void Parse(char *input, struct Line *line);

#endif
