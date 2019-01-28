/*

  Eugene Thomas
  CS223
  Homework 1

*/

#include <stdio.h>
#include <string.h>

/*

  Objective (from Prelim Specification):

  A filter 'C2html' that copies a C program from the standard input to
  the standard output, formatting it for viewing by an HTML browser.

*/

/*

 Method 1: char singleChar (char c)

 Purpose: Takes care of single character cases.

 Regulations:
  - Each & character is replaced by the string '&amp;'.
  - Each < character is replaced by the string '&lt;'.
  - Each > character is replaced by the string '&gt;'.

*/

char * singleChar (char c)
{
    if (c == '&') return "&amp;";
    if (c == '<') return "&lt;";
    if (c == '>') return "&gt"; 
}

/*
  Method 2: char stringHandling (char c)

  Purpose: Takes care of string literals.

  Regulations:
    - Each string literal is bracketed by the strings '<B>' and '</B>'.
    - handle string literals (i.e., character constants and strings) correctly;
    - handle escaped characters within string literals correctly;

  methodNotes:

    0 (Method Explained).
    1. Here, the following three lines mean the following:
      If this character does not match the initial quote (which means the quote is not closed):
      You then add this to the return char and check for the next character to be closed.

    2. Here, we add the nextChars until there are none left.

*/

// see MethodNote0
char * stringHandling (char * c)
{
  char initChar = getchar();
  if ((initChar == 'a') || (initChar == 'b')) {
    char * retStr = "<B>"; // Return string literal
    retStr = strcat(retStr, initChar); // Adds the initial Character to retStr
    // See methodNote1 for this:
    char nextChar = getchar();
    while (nextChar != initChar) {
        retStr = strcat(retStr, nextChar);
        nextChar = getchar();
    }
    retStr = strcat(retStr, nextChar); // adds the end quote
    retStr = strcat(retStr, "</B>"); //and the </B> tag
    // See methodNote2 for this:
    while (nextChar != EOF) {
      nextChar = getchar();
      retStr = strcat(retStr, nextChar);
    }
    return retStr;
  }
  else {
    return c; //If this is not a quote, this is irrelevant and retuns the s
  }
}

/*
  As advised by TA Isabelle: Save this for last

  Method X: char commentHandling (char c)

  Purpose: To reformat comments.

  Regulations:
  Each comment is bracketed by the strings '<I>' and '</I>'.
  handle line splices correctly
  handle both block and line comments correctly
*/

char * commentHandling (char * c)
{
  return "";
}

/*
  Method X+1: The Main Method

  Purpose: To place each of the pieces together into an output.

  Regulations:
    - read from stdin and write to stdout but do no other input or output;
    - not use arrays or pointers; and
    - fail 'gracefully' (i.e., neither go into an infinite loop nor cause a
        memory dump) if the input is not a legitimate C program or any of these
        assumptions is violated.
*/

int main()
{
    char * string = "\"Hello World!\"";
    char * retStr = stringHandling(string);
    printf("<PRE>%s\n</PRE>", retStr);
    return 0;
}
