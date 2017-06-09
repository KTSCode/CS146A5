#include "parse.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

/*
 ** A very simple main program that re-prints the line after it's been scanned and parsed.
 */
int main(int argc, char *argv[])
{
  FILE *input;
  char line[MAX_LINE];
  char cwd[MAX_LINE];
  char outBuf[MAX_LINE];
  char *cmdOut = outBuf;
  char inBuf[MAX_LINE];
  char *cmdIn = inBuf;

  // Get the current working directory or error
  if(getcwd(cwd, sizeof(cwd)) == NULL){
    perror("Couldn't get cwd");
    return 1;
  }

  if(argc == 2)
  {
    input = fopen(argv[1], "r");
    if(input == NULL)
    {
      perror(argv[1]);
      exit(1);
    }
  }
  else
  {
    assert(argc == 1);
    input = stdin;
    printf("%s? ", cwd);
    /* By default, printf will not "flush" the output buffer until
     * a newline appears.  Since the prompt does not contain a newline
     * at the end, we have to explicitly flush the output buffer using
     * fflush.
     */
    fflush(stdout);
  }

  setlinebuf(input);
  while(fgets(line, sizeof(line), input))
  {
    int i;
    struct commandLine cmdLine;

    if(line[strlen(line)-1] == '\n')
      line[strlen(line)-1] = '\0';   /* zap the newline */

    Parse(line, &cmdLine);


    if(cmdLine.infile) //TODO do infile stuff
      printf("< '%s' ", cmdLine.infile);

    for(i=0; i < cmdLine.numCommands; i++)
    {
      int j = cmdLine.cmdStart[i];

      if (Execute(cwd, cmdIn, cmdLine.cmdStart[i], j, &cmdLine, cmdOut) != 0)
        printf("Error Processing Command");

      if(i < cmdLine.numCommands - 1)
        printf("| ");
    }

    if(cmdLine.append)//TODO do append stuff
    {
      /* verify that if we're appending there should be an outfile! */
      assert(cmdLine.outfile);
      printf(">");
    }
    if(cmdLine.outfile)//TODO do outfile stuff
      printf(">'%s'", cmdLine.outfile);

    /* Print any other relevant info here, such as '&' if you implement
     * background execution, etc.
     */

    printf("%s", cmdOut);

    if ( strlen(cmdOut) > 0)
      printf("\n");

    if(input == stdin)
    {
      printf("%s? ", cwd);
      fflush(stdout);
    }
  }

  return 0;
}
