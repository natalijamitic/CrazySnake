#ifndef _preparation_h_
#define _preparation_h_
#pragma comment(lib, "winmm.lib")
//Include all header files for game.
#include <curses.h>
#include <stdio.h>
#include <windows.h>
#include "menu.h"
#include "help.h"
#include "about.h"
#include "exit.h"
#include "crazy_snake.h"
#include "loading2.h"
#include "setup.h"
#include "gameplay.h"
#include "options.h"
#include "save_game.h"
#include "timer.h"
#include "highscore.h"
#include "authors.h" 
//#include "Source.h"
#include "shortest_path.h"
#include "Demo.h"
//Preparation for game.
void prepare(Options *option, int *row, int *col);
//New game.
void new_game(Options options, Options *saved_options);
//Continue old game.
void continue_game();
//Start demo.
void demo_game(Options options);
#endif 