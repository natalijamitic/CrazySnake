#ifndef __highscore_h
#define __highscore_h
#include <stdio.h>
//Save top ten users score.
int topTen(int);
//Copy one text file to another. 
void file_copy(FILE *, FILE *);
//Print highscore
void print_Highscore(void);
//Print highscore after time is up
void print_Highscore_underline(int);
#endif