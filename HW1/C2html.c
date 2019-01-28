/*

  Eugene Thomas
  CS223
  Homework 1

*/

#include <stdio.h>

/*

  Objective (from Prelim Specification):

  A filter "C2html" that copies a C program from the standard input to
  the standard output, formatting it for viewing by an HTML browser.

*/

/*

 Method 1: preAndPost (char c):

 Purpose: Adds the <PRE> and </PRE> before and after the program

*/

char preAndPost (char c)
{
  return "<PRE>"+c+"\n</PRE>\n";
}

/*

 Method 2: char singleChar (char c)

 Purpose: Takes care of single character stuff

 Regulations:
  - Each & character is replaced by the string "&amp;".
  - Each < character is replaced by the string "&lt;".
  - Each > character is replaced by the string "&gt;".

*/

char singleChar (char c)
{
  if (c == "&") return "&amp;";
  if (c == "<") return "&lt;";
  if (c == ">") return "&gt;";
  else return c;
}

/*
  Method 3: char stringHandling (char c)

  Purpose: Takes care of string literals.

  Regulations:
    - Each string literal is bracketed by the strings "<B>" and "</B>".
    - handle string literals (i.e., character constants and strings) correctly;
    - handle escaped characters within string literals correctly;
*/

char stringHandling (char c)
{

}

/*
  As advised by TA Isabelle: Save this for last

  Method X: char commentHandling (char c)

  Purpose: To reformat comments.

  Regulations:
  Each comment is bracketed by the strings "<I>" and "</I>".
  handle line splices correctly
  handle both block and line comments correctly
*/

char commentHandling (char c)
{

}

/*
  Method X+1: The Main Method

  Purpose: To place each of the pieces together into an output.

  Regulations:
    - read from stdin and write to stdout but do no other input or output;
    - not use arrays or pointers; and
    - fail "gracefully" (i.e., neither go into an infinite loop nor cause a
        memory dump) if the input is not a legitimate C program or any of these
        assumptions is violated.
*/

main()
{
    printf("hello, world\n");
}
