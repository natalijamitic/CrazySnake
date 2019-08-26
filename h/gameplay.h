#ifndef _game_play_h_
#define _game_play_h_
#include "setup.h"
#include "options.h"
#define TOPTEN
//Current snake state.
typedef enum { HITWALL, TIMEISUP, ALIVE } Game_state;
//Snake move.
typedef enum { LEFT, RIGHT, DOWN, UP, STOPL, STOPR, STOPD, STOPU } Move;
//Speed of snake
typedef enum { EASY_SPEED = 150, MEDIUM_SPEED = 100, HARD_SPEED = 50, LOAD = 10 } Snake_speed;
//Game options
typedef enum { QUIT, NEW_GAME, CONTINUE, DEMO, HIGHSCORE, OPTIONS, HELP, ABOUT, AUTHORS, EXIT } GAME_OPTION;
//Print current score.
void print_score(WINDOW *, int *);
//Print current time.
void print_time(WINDOW *, int, int);
//Delete snake from game.
void delete_snake(WINDOW*, int, int);
//Print snake on map.
void print_snake(WINDOW*, int, int);
//Print fruit on map.
void print_fruit(WINDOW*, int, int);
//Print snake head.
void print_snake_head(WINDOW *, int, int);
//Print game pause window.
void print_game_pause(WINDOW *, int);
//Game pause. 
int game_pause(WINDOW *, WINDOW *, short **, Fruit *, Header *, Game_mode, Move *, Move, Options *, int *, int *len, int *total);
//Print map.
void print_game(short **, WINDOW *, int, int);
//Update snake after user command.
void one_move(short **, int, int, Move*, Move*, Header*, WINDOW*);
//Update board(map)  and game state using snake position.
_Bool board_update(short **, int, int, Move*, Move*, Header *, Fruit *, Game_mode, int *, WINDOW *, WINDOW *, int*, int*, double *);
//Update entire game. 
int gameplay(short **, Header *, Fruit *, Options *, Move *, Move *, int *, int *, int *);
//Print window if user is dead.
void dead(void);
//Print window if time is up.
void timeisup(int *, int, int*, int*);
//Print continue window
void print_continue(void);

void command(short **, Time *, Options *, Move *, Move *, Fruit *, WINDOW *, WINDOW*, Header *, int *, _Bool *, _Bool *, int*, int*, double*);
void print_begining(short **, Options *, WINDOW **, WINDOW **, Header *, int, Fruit *, int *, Time *, int *, int *, int *, int *);

#endif  
