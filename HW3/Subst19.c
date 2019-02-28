/*

Eugene Thomas
CPSC223
Homework 3

*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* UFlags = "QNPRS";
static char* LFlags = "qnsr ";

//================================================ helpers =============================================

// inFlags: examines whether a character is in flags or not.
int inFlags(char x) {
  for (int i = 0; i < 4; i++) {
    if (x == UFlags[i]) {
      return 1;
    }
    if (x == LFlags[i]) {
      return 2;
    }
  }
  return 0;
}

// Parse: goes through a command and translates it into the correct command given:
char* parse(char* flag) {

  char charArr[] = "+  ";
  char upper = ' ';
  char lower = ' ';

  if (flag[0] != '+') {
    return "Nope!";
  }

  for (int i = 1; i < strlen(flag); i++) {
    char c = flag[i];
    if (inFlags(c) == 1) {
      lower = c;
    }
    else if (inFlags(c) == 2) {
      upper = c;
    }
    else {
      return "Nope!";
    }
  }

  charArr[1] = upper;
  charArr[2] = lower;
  char *retChar = malloc(3);
  strcpy(retChar, charArr);
  return retChar;
}

int main(int argc, char* argv[]) {

  char* FLAGi;
  char* FROMi;
  char* TOi;

  // if there is only one argument...
  if (argc == 1) {
    printf("...\n");
    exit(0);
  }

  // if there are not triplets of three
  if (argc%3 != 2) { // in threes, but the program and file names must be there too.
    printf("The triplets ain't there!\n");
    exit(0);
  }

  // note that argv[0] = "Subst19".

  // for the rest of the inputs:

  for (int i = 1; i < argc-2; i=i+3) {
    // if the input is invalid, fail gracefully
    if (strcmp(parse(argv[i]), "Nope!") == 0) {
      printf("Invalid user input!\n");
      exit(0);
    }

    // otherwise, identify the flag, and the from and to flags
    else {
      FLAGi = parse(argv[i]);
      printf("\nFlag: %s\n", FLAGi);
      FROMi = argv[i+1];
      printf("From: %s\n", FROMi);
      TOi = argv[i+2];
      printf("To: %s\n\n", TOi);
    }

  }

  char* filename = argv[argc-1];
  FILE *file = fopen(filename, "r");

  if (file == NULL) { // if the file is not read correctly
    printf("Cannot open file. You are the weakest link. Goodbye. \n\n");
    exit(0);
  }

  size_t bufferSize= 32; // arbitrary size
  char *bufferString = malloc(bufferSize*sizeof(char)); // expands if necessary.
  int line = 1; // keeps track of lines

  while (getline(&bufferString,&bufferSize,file) != -1) {
      bufferString = realloc(bufferString, bufferSize);
      line++;
  }

  // to end the code: close the file and return 0.
  fclose(file);
  return 0;
}
