#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include "parse.h"

int alphaSort (const void *a, const void *b) {
    struct dirent *A = (struct dirent *)a;
    struct dirent *B = (struct dirent *)b;
    char *aa = A->d_name;
    char *bb = B->d_name;
    int r = strcasecmp(aa, bb);
    if (r) return r;
    return -strcmp(aa, bb);
}

int Execute(char *cwd, char *input, int cmdIndex, int args, struct commandLine *sc, char *output){
  // Clear output
  output[0] = '\0';
  char command[1024];
  strcpy(command, sc->argv[cmdIndex]); //set command

  // Parse Commands
  if (strcmp(command, "echo") == 0){ //Echo TODO: remove "s
    char toEcho[1024];
    int i;
    for(i = args+1; sc->argv[i] != NULL; i++){
      strcat(output, sc->argv[i]);
      strcat(output, " ");
    }
    // removes the trailing white space
    output[strlen(output)-1] = '\0';
  }
  else if (strcmp(command, "cd") == 0){ //Change Directory
    DIR* dir;
    char dirName[1024];
    strcpy(dirName, sc->argv[args+1]);
    if (dirName != NULL){
      dir = opendir(dirName);
    }
    if (dir){
      if (strcmp(dirName, "..") == 0){
        int i=strlen(cwd);
        while(cwd[i] != '/'){
          cwd[i] = '\0';
          --i;
        }
        if(strlen(cwd) > 1)
          cwd[i] = '\0';
      }
      else if(strcmp(dirName, ".") == 0){}
      else if(dirName[0] == '/'){
        strcpy(cwd, dirName);
      }
      else{
        strcat(cwd, "/");
        strcat(cwd, dirName);
      }
    }
    else{
      printf("cd: %s is not a valid directory\n", dirName);
    }

  }
  else if (strcmp(command, "pwd") == 0){ //Print Working Directory
    strcpy(output, cwd);
  }
  else if (strcmp(command, "ls") == 0){ //List
    struct dirent *dirEnt; //declare an array for of dirents
    int numDirs = 0;
    DIR* dir;
    char dirName[1024];
    if (sc->argv[args+1] == NULL){
      strcpy(dirName, cwd);
    }
    else{
      strcpy(dirName, sc->argv[args+1]);
    }
    if (dirName != NULL){ //check if a directory name was passed
      dir = opendir(dirName);
    }
    if (dir){
      while ((dirEnt = readdir(dir)) != NULL){
        numDirs++;
      }
      rewinddir(dir); //reset the directory pointer
      struct dirent dirEnts[numDirs]; //declare an array for of dirents
      int i = 0;
      while ((dirEnt = readdir(dir)) != NULL){
        if(dirEnt->d_name[0] != '.'){
          dirEnts[i] = *dirEnt;
          i++;
        }
      }
      qsort(dirEnts, i, sizeof(struct dirent), alphaSort);
      int j;
      for (j = 0; j < i; j++){
        struct dirent *tempdr = &dirEnts[j];
        strcat(output, tempdr->d_name);
        strcat(output, " ");
      }
      if(strlen(output) > 0){
        output[strlen(output)-1] = '\0';//removes the trailing white space
      }
      closedir(dir); //close the directory
    }
    else{
      printf("ls: cannot access %s No such file or directory\n", dirName);
    }
  }
  else if (strcmp(command, "cat") == 0){ //cat
    FILE *file;
    char line[MAX_LINE];
    if (sc->argv[args+1] != NULL){
      file = fopen(sc->argv[args+1], "r");
      if(file == NULL)
      {
        printf("cat: %s: No such file or directory\n", sc->argv[args+1]);
      }
      else {
        while(fgets(line, sizeof(line), file)){
          strcat(output, line);
        }
        if(strlen(output) > 0){
          output[strlen(output)-1] = '\0';//removes the trailing white space
        }
      }
    }
    else if (strlen(input) > 0){
      strcpy(output, input);
    }

  }
  else if (strcmp(command, "exit") == 0){ //exit
    exit(0);
  }
  else {
  }

  input[0] = '\0';
  return 0;
}
