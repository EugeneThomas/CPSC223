/*

Eugene Thomas
CPSC223
Homework 3

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

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

  The default (when no lower-case flag is specified) is n.
  */
}
