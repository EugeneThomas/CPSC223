/*
  Eugene Thomas
  CS223
  Homework 1
*/

#include <stdio.h>
#define ungetchar(c) ungetc(c,stdin)

/*
  Objective (from Prelim Specification):
  A filter 'C2html' that copies a C program from the standard input to
  the standard output, formatting it for viewing by an HTML browser.
*/

/*
 METHOD 1: char singleChar (char c)
 Purpose: Takes care of single character cases.
 Regulations:
  - Each & character is replaced by the string '&amp;'.
  - Each < character is replaced by the string '&lt;'.
  - Each > character is replaced by the string '&gt;'.
*/

void singleChar (char c)
{
    if (c == '&') printf("&amp");
    else if (c == '<') printf("&lt");
    else if (c == '>') printf("&gt");
    else printf("%c", c);
}

// Main method

int main()
{
  printf("<PRE>"); // Begin with PRE tag
  int inQuote = 0; // returns 1 if currently in a quote, returns 0 if not.
  char c = getchar(); // gets the first character
  while (c != EOF) { // while there is a next character in the code
    if (c == '/') { // handling comments
      if (inQuote == 1) {
        printf("%c", c); // If it's in a quote, it cannot be processed as a comment.
      }
      else {
        char d = getchar(); // d is the next character
        if (d == '/') goto single; // if a single line comment...
        else goto block; // if a block comment

        // if this is a single line comment...
        single:
          printf("<I>//");
          c = getchar();
          while (c != '\n') {
            singleChar(c);
            c = getchar();
          }
          printf("</I>");

        // if this is a block comment...
        block:
          printf("<I>/*");
          c = getchar();
          while (c != '*' && getchar() != '/') {
            ungetchar(c);
            singleChar(c);
            c = getchar();
          }
          printf("*/</I>");
      }
    }

  c = getchar();
  }

  printf("</PRE>"); // finish by printing out the final PRE tag.
  return 0;
}
