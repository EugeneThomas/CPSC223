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


  int inString = 0; // returns 1 if currently in a quote, returns 0 if not.
  int inComment = 0; // returns 1 if in line comment, returns 0 if not.
  char c = getchar(); // gets the first character

  // WHILE THE CODE IS NOT FINISHED...

  while (c != EOF) {

    cases:

    // COMMENT HANDLING BEGIN

    if (c == '/') {
      if (inString == 1) {
        printf("%c", c); // If it's in a quote, it cannot be processed as a comment.
      }
      else {
        char d = getchar(); // d is the next character
        if (d == '/') {  // if a single line comment...
          printf("<I>//");
          goto single;
        }
        else {// if a block comment
          printf("<I>/*");
          goto block;
        }

        // if this is a single line comment...
        single:
          inComment = 1;
          c = getchar();
          while (c != '\n') {
            goto cases;
            c = getchar();
          }
          inComment = 0;
          printf("</I>");

        // if this is a block comment...
        block:
          c = getchar();
          while (c != '*' && getchar() != '/') {
            ungetchar(c);
            singleChar(c);
            c = getchar();
          }
          printf("<*//I>");
      }
    }

    // COMMENT HANDLING END

    // STRING LITERAL HANDLING BEGIN

    else if (c == '"') { // if the next character denotes the beginning of the string...
      if (inString == 0) {
        inString = 1;
        printf("<B>\"");
        c = getchar();
        while (c != '"') {
          goto runDown;
          c = getchar();
        }
        inString = 0;
        printf("\"</B>");
      }
     else {
       printf("\"</B>");
     }
    }

    // STRING LITERAL HANDLING END

    // CHARACTER HANDLING BEGIN

    else if (c == '\'') { // if the next character is the beginning of a string....
      printf("<B>\'");
      printf("%c", singlechar(getchar()));
      getchar(); // to process the closing apostrophe.
      printf("\'</B>");
    }

    // CHARACTER HANDLING END

    // BACKWARD SLASH HANDLING BEGIN -- LINE SPLICES AND ESCAPES

    else if (c == '\\') {

      if (inComment == 1) { // this means that there is a line splice in a line comment.
        if (getchar() == '\n') {
          goto single;
        }
        else {
          c = getchar();
          goto cases;
        }
      }

      else {
        if (inString == 1) {
          if (getchar() == '\n') {
            
          }
          else {
            c = getchar();
            goto cases;
          }
        }
        else {}
      }

    }

    // FINAL CASE: not a special case

    else {
      singlechar(c); // evaluate the character to see if it must be converted.
    }

  c = getchar(); // AT THE END OF EACH EVALUATION, YOU ALWAYS GET THE NEXT CHARACTER.

  }

  printf("</PRE>"); // finish by printing out the final PRE tag.

  return 0;
}
