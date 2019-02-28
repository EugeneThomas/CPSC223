/*

Eugene Thomas
CPSC223
Homework 3

*/

// defines and includes
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// static global variables
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
  // placeholders and variables...
  char charArr[] = "+  ";
  char upper = ' ';
  char lower = ' ';

  // check if the first character is a +...
  if (flag[0] != '+') {
    return "Nope!";
  }
  // for each of the other elements in the flag...
  for (int i = 1; i < strlen(flag); i++) {
    char c = flag[i];
    if (inFlags(c) == 1) { // if a lower
      lower = c;

    }
    else if (inFlags(c) == 2) { // if an upper
      upper = c;
    }
    else { // if neither
      return "Nope!";
    }
  }
  // place them in an upper, lower order
  charArr[1] = upper;
  charArr[2] = lower;
  // allocate 3 pieces of data for the return character
  char *retChar = malloc(3);
  // copy the array into the literal
  strcpy(retChar, charArr);
  // return the char*
  return retChar;
}

char* seg(char* line, int a, int b) {
  size_t size = 0; // size that will be reallocated when necessary
  char retArr[size]; // character array
  for (int i = a; i < b; i++) {
    size++;
    retArr[i-a] = line[i];
  }
  char *retChar = malloc(b-a);
  strcpy(retChar, retArr);
  return retChar;
}
//=========================================== helpers end =============================================


/*
  When the q flag (Quit) is specified, only the leftmost occurrence (if any) of
  FROMi in the line is replaced by TOi.

  When the n flag (continue Next) is specified, every occurrence of FROMi in
  the line is replaced by TOi.  That is, the leftmost occurrence (if any) of
  FROMi is replaced; and, after each substitution, the modified line is scanned
  beginning with the first character FOLLOWING the replacement string for
  the leftmost occurrence of FROMi, which is then replaced by TOi.

  When the r flag (Rescan) is specified, the leftmost occurrence (if any) of
  FROMi is replaced by TOi; and, after each substitution, the modified line is
  scanned beginning with the first character IN the replacement string for the
  leftmost occurrence of FROMi, which is then replaced by TOi.

  When the s flag (Start over) is specified, the leftmost occurrence (if any)
  of FROMi is replaced by TOi, and, after each substitution, the ENTIRE line is
  scanned for the leftmost occurrence of FROMi, which is then replaced by TOi.

  When the Q flag (Quit) is specified, if the application of a rule is
  successful, then the remaining rules are ignored.

  When the N flag (apply Next) is specified, if the application of a rule is
  successful, then the next rule (in left to right order) is applied.

  When the R flag (Reapply current) is specified, if the application of a rule
  is successful, then that rule is reapplied before continuing on to the next
  rule (in left to right order).

  When the P flag (reapply Previous) is specified, if the application of a rule
  is successful, then the previous rule (in left to right order) is applied
  next.  If there is no previous rule, P is equivalent to R.

  When the S flag (reStart) is specified, if the application of a rule is
  successful, then the first rule (in left to right order) is applied next.

  The default (when no upper-case flag is specified) is N.
*/

//======================================== string replacement ========================================
char* replace (char* line, char* flag, char* from, char* to) {

  if (strcmp(from, to) == 0) {return line;}

  // variables...
  int lenFrom = strlen(from); // length of the from
  int lenLine = strlen(line); // length of the entire line
  int lenTo = strlen(to); // length of the to
  int ctr = 0; // line position/counter
  size_t size = 0; // size that will be reallocated when necessary
  char retArr[size]; // character array
  int completed = 0; // if never completed: 0. if completed: 1.
  // variables end

  // while the counter is less than the length of the line...
  while (ctr < lenLine) {
    char* fromComp = seg(line, ctr, ctr+lenFrom);
    if (strcmp(fromComp, from) == 0) {
      for (int i = ctr; i < (ctr+lenTo); i++) {
        size++;
        retArr[i] = to[i-ctr];
      }
      completed = 1; // mark as completed
      ctr += lenFrom; // increases the counter by lenFrom amount

      if (flag[2] == 'q') { // if the first flag denotes to quit...
        size += (lenLine-ctr);
        break;
      }
      // n and the blank input here are neglible.
      else if (flag[2] == 'r') {
        ctr = ctr - (lenFrom-1);
      }
      else if (flag[2] == 's') {
        ctr = 0;
      }

    }

    else {
      size++;
      retArr[ctr] = line[ctr];
      ctr++;
    }

  }

  // allocate 3 pieces of data for the return character
  char *retChar = malloc(lenLine);
  // copy the array into the literal
  strcpy(retChar, retArr);
  return retChar;
}
//====================================== string replacement end =======================================


























//=============================================  main  ============================================

int main(int argc, char* argv[]) {

  // flag, from, and to
  size_t size = 0;
  char* FLAGi[size];
  char* FROMi[size];
  char* TOi[size];

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
    // Resizing them...

    // if the input is invalid, fail gracefully
    if (strcmp(parse(argv[i]), "Nope!") == 0) {
      printf("Invalid user input!\n");
      exit(0);
    }
    // otherwise, identify the flag, and the from and to flags
    else {
      size++;
      FLAGi[i/3-1] = parse(argv[i]);
      // printf("\nFlag: %s\n", FLAGi[i/3-1]);
      FROMi[i/3-1]= argv[i+1];
      // printf("From: %s\n", FROMi[i/3-1]);
      TOi[i/3-1] = argv[i+2];
      // printf("To: %s\n\n", TOi[i/3-1]);
    }

  }

  int arrLength = (argc-2)/3;
  char* filename = argv[argc-1];
  FILE *file = fopen(filename, "r");

  if (file == NULL) { // if the file is not read correctly
    printf("Cannot open file. You are the weakest link. Goodbye. \n\n");
    exit(0);
  }

  size_t bufferSize= 32; // arbitrary size
  char *bufferString = malloc(bufferSize*sizeof(char)); // expands if necessary.

  while (getline(&bufferString,&bufferSize,file) != -1) {
      bufferString = realloc(bufferString, bufferSize);
      char* line;
      for (int i = 0; i < arrLength; i++) {
        line = replace(bufferString, FLAGi[i], FROMi[i], TOi[i]);
      }
      printf("%s", line);
  }

  // to end the code: close the file and return 0.
  fclose(file);
  return 0;
}
//========================================== end of main =============================================
