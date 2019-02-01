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
    if (c == '&') printf("&amp;");
    else if (c == '<') printf("&lt;");
    else if (c == '>') printf("&gt;");
    else printf("%c", c);
}

// Main method

int main()
{
  printf("<PRE>"); // Begin with PRE tag
  int inString = 0; // returns 1 if currently in a quote, returns 0 if not.
  int inComment = 0; // returns 1 if in line comment, returns 0 if not.
  char currChar = getchar(); // gets the first character

  // WHILE THE CODE IS NOT FINISHED...

  while (currChar != EOF) {

    // the initial goto: 

    cases:

    // COMMENT HANDLING BEGIN

    if (currChar == '/') {

      if (inString == 1) {
        printf("%c", currChar); // If it's in a quote, it cannot be processed as a comment.
      }

      else { // if it is not in a quote 

        inComment = 1; // you mark it as a part of the comment.
        currChar = getchar(); // get the next character 

        if (currChar == '/') {  // if a single line comment...
          printf("<I>//"); // you go to the single comment section. 
          goto single;
        }

        // if the next character is a line splice... 

        else if (currChar == '\\' && getchar() == '\n') {
          printf("<I>/\\\n"); // print out the beginning tag. 
          currChar = getchar(); // get the next character. 
          // WHILE THERE ARE CONSECUTIVE LINE SPLICES.... 
          while (currChar == '\\' && getchar() == '\n') {
              printf("\\\n"); 
              currChar = getchar(); // print out new line and get next character to see if that is also a line splice. 
            }
          // if the first non line splice is a single line comment. 
          if (currChar == '/') {  // if a single line comment...
            printf("/"); // you go to the single comment section. 
            goto single;
          }
          else  {// if a block comment
            printf("*");
            goto block;
          }
        }

        // if this is neither a line splice nor a line comment, this must be a block comment. 

        else  {// if a block comment
          printf("<I>/*");
          goto block; // goto block method 
        }

        // if this is a single line comment...
        single:

          currChar = getchar(); // you get the next character 
          while (currChar != '\n' || currChar != EOF) { // while the device is on the same line. 
            if (currChar == EOF) {
              printf("</I>\n");
              goto end;
            }
            else if (currChar == '\n') {
              currChar = getchar(); 
              break;
            }
            else {
              singleChar(currChar); // you print the appropriate form of the current character. 
              currChar = getchar(); // you get the next character 
            }

            // HANDLING OF A LINE SPLICE IN A SINGLE LINE COMMENT 
            while (currChar == '\\' && getchar() == '\n') {
              printf("\\\n"); 
              currChar = getchar();
            }
            //HANDLING OF A LINE SPLICE COMPLETE 

          } // this repeats until you reach a new line. once that is met... 
          printf("</I>\n"); // you print the ending tag 
          currChar = getchar(); // you get the next character post-comment
          inComment = 0; // you unmark it as part of a comment. 
          goto cases; // you begin back at cases 
     

        // if this is a block comment...
        block:

          currChar = getchar(); // get the next character 

          whileLoop: 
          while (currChar != '*') { // if this doesn't close the comment... 
            singleChar(currChar); // print the current character 
            currChar = getchar(); 
          }
          printf("%c", currChar); // print the '*'. 

          // to test the star position 
          char testChar = getchar(); // next position 

          if (testChar != '\\' && testChar != '/') { // if the asterisk is not a sign of the end of a comment...
            currChar = testChar; // change the current character to the one tested. 
            goto whileLoop; // process this next character accordingly 
          } 

          else if (testChar == '\\') { // if there is a line splice... 
            while (testChar == '\\' && getchar() == '\n') { // while line splices continue... 
              printf("\\\n"); 
              testChar = getchar();
            }
            if (testChar == '/') { // if the first non-splice is an end quote... 
              goto endComment;
            }
            else {
              // otherwise... 
              currChar = testChar; 
              goto whileLoop; 
            }
          }
          else {
            goto endComment; 
          }

          endComment: 

          printf("/</I>"); // print out ending tag 
          currChar = getchar(); // you get the next character post-comment 
          inComment = 0; // unmarks as part of comment 
          goto cases; // go back to cases
       }
    }

    // COMMENT HANDLING END

    // STRING LITERAL HANDLING BEGIN

    else if (currChar == '"') { // if the next character denotes the beginning of the string...

      // if you're NOT in a comment... 
      
      if (inComment == 0) {
        inString = 1; // puts status as within the string. 
        printf("<B>\""); // puts initial tag for the string 
        currChar = getchar(); // gets next character 
        while (currChar != '"') { // until you reach the end quote... 
          // HANDLING OF A LINE SPLICE/ESCAPE IN A QUOTE  
            if (currChar == '\\') { // if it is a backslash  
              char c = getchar(); // get next character to see if it is an escape 
              if ( c == '\n') { // if a new line...  
                printf("\\\n"); 
                currChar = getchar();
              }
              else if (c == '\'') { // if an espace single quote... 
                printf("\\\'"); 
                currChar = getchar();
              }
              else if (c == '\"') { // if an escape double quote 
                printf("\\\""); 
                currChar = getchar();
              }
              else { // if an escape for backslash... 
                printf("\\");
                currChar = c; 
              }
            }
          //HANDLING OF A LINE SPLICE COMPLETE 
            else {
              singleChar(currChar); // print current character
              currChar = getchar(); // get next character 
            }
        }
        printf("\"</B>"); // print end tag 
        inString = 0; // change status of no longer being string
      }

      // if you're in a comment, none of this will process and it'll just return a quote... 

      else {
        printf("\"");
        currChar = getchar(); 
        goto cases; 
      }
    }

    // FINAL CASE: not a special case
    else if (currChar == '\\') {
      printf("\\");
      currChar = getchar(); 
    }

    else {
      singleChar(currChar); // evaluate the character to see if it must be converted.
    }

  currChar = getchar(); // AT THE END OF EACH EVALUATION, YOU ALWAYS GET THE NEXT CHARACTER.

  }

  end: 

  printf("</PRE>\n"); // finish by printing out the final PRE tag.

  return 0;
} 
