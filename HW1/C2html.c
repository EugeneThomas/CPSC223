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
        else  {// if a block comment
          printf("<I>/*");
          goto block;
        }

        // if this is a single line comment...
        single:
          currChar = getchar(); // you get the next character 
          while (currChar != '\n') { // while the device is on the same line. 
            singleChar(currChar); // you print the appropriate form of the current character. 
            currChar = getchar(); // you get the next character 

            // HANDLING OF A LINE SPLICE IN A SINGLE LINE COMMENT 
            if (currChar == '\\' && getchar() == '\n') {
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
          char nextChar = getchar(); // get the character after that
          while (currChar != '*' || nextChar != '/') { // if this doesn't close the comment... 
            singleChar(currChar); // print the current character 
            ungetchar(nextChar);  // these three lines turn current into next and next into the one after. 
            currChar = getchar(); 
            nextChar = getchar(); 
          }
          printf("*/</I>"); // print out ending tag 
          currChar = getchar(); // you get the next character post-comment 
          inComment = 0; // unmarks as part of comment 
          goto cases; // go back to cases
       }
    }

    // COMMENT HANDLING END

    // STRING LITERAL HANDLING BEGIN

    else if (currChar == '"') { // if the next character denotes the beginning of the string...
      if (inComment == 0) {
        inString = 1; // puts status as within the string. 
        printf("<B>\""); // puts initial tag for the string 
        currChar = getchar(); // gets next character 
        while (currChar != '"') { // until you reach the end quote... 
          // HANDLING OF A LINE SPLICE IN A QUOTE  
            if (currChar == '\\' && getchar() == '\n') {
              printf("\\\n"); 
              currChar = getchar();
            }
          //HANDLING OF A LINE SPLICE COMPLETE 
          singleChar(currChar); // print current character
          currChar = getchar(); // get next character 
        }
        printf("\"</B>"); // print end tag 
        inString = 0; // change status of no longer being string
      }
      else {
        printf("\"");
        currChar = getchar(); 
        goto cases; 
      }
    }
    
    // STRING LITERAL HANDLING END 
 

    // ESCAPE HANDLING BEGIN 
       
    // ESCAPE HANDLING END 

    // LINE SPLICE HANDLING BEGIN
        
    // LINE SPLICE HANDLING END 

    
 
    /*
    else if (currChar == '\\') {

      if (inComment == 1) { // this means that there is a line splice in a line comment.
        if (getchar() == '\n') {
          goto single;
        }
        else {
          currChar = getchar();
          goto cases;
        }
      }

      else {
        if (inString == 1) {
          if (getchar() == '\n') {

          }
          else {
            currChar = getchar();
            goto cases;
          }
        }
        else {

        }
      }

    }
    */ 


    // FINAL CASE: not a special case

    else {
      singleChar(currChar); // evaluate the character to see if it must be converted.
    }

  currChar = getchar(); // AT THE END OF EACH EVALUATION, YOU ALWAYS GET THE NEXT CHARACTER.

  }

  printf("</PRE>\n"); // finish by printing out the final PRE tag.

  return 0;
}
