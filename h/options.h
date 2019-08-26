#ifndef _options_h_
#define _options_h_
#include <curses.h>
#include "timer.h"
//Map size. 
typedef struct {
	int row, col;
} Table;
// Game options.
typedef struct {
	double minutes, seconds;
	Table size;
	int mode;
	int music;
}Options;
//Game dificulty
typedef enum { EASY = 1, MEDIUM, HARD, BACK4, BACK3 = 3, BACK2 = 2 } Game_mode;
//Keyboard keys.
typedef enum { K_DOWN = 80, K_EXIT = 13, K_UP = 72, K_LEFT = 75, K_RIGHT = 77, K_ESC = 27, ENTER = 10, PAUSE_CAPITAL = 80, PAUSE = 112, READY = -32 } KEYS;
//Game options.
typedef enum { DURATION = 1, MAP_SIZE, SNAKE_SPEED, CLEAR_HIGHSCORE, MUSIC, BACK6 } Game_options;
//Map size optins.
typedef enum { ROW_SIZE = 1, COLUMN_SIZE } Map_size_options;
//Time duration options.
typedef enum { MINUTES = 1, SECONDS } Duration_options;
//Music options.
typedef enum { ON = 1, OFF } Music;
//Print options. 
void print_options(WINDOW*, int);
//Open options.
int open_options();
//Print snake speed options.
void print_snake_speed(WINDOW *, int, int);
//Choose snake speed.
void snake_speed(Options *);
//Print music options.
void print_music(WINDOW *, int, int);
//Choose music options.
void open_music(Options *);
//Print game duration options.
void print_duration(WINDOW *, int);
//Choose game durastions option.
int game_duration(Options *, WINDOW *);
//What can be choosen for game duration.
void game_duration_choice(Options *);
//Print map size option.
void print_size(WINDOW *, int);
//Choose map size.
int game_size(Options *, WINDOW *);
//What can be choose for map size.
void game_size_choice(Options *);
//Delete highscore.
void delete_top10();
//Choose what option you would like to change.
void makeoptionchoice(Options *);
#endif
