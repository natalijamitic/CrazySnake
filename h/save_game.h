#ifndef _savegame_h
#define _savegame_h
#include <stdio.h>
#include "gameplay.h"
#define SAVED 1
//Save all information abou the game for next time.
_Bool savegame(Options *option, Move initialmove, Move currentmove, short **board, int score, Header header, Fruit fruit,int len,int total);
//Save if palyer finished the game or not.
void save_stop(int stop);
//Load all information about the saved game.
short ** loadgame(Options * option, Move * initialmove, Move *currentmove, int * score, Header *header, Fruit *fruit,int *len,int *total);
//Load information if player finished the game or not.
int load_stop(void);
void save_options(Options *options);
void load_options(Options *options);
#endif

