#include "setup.h"
#include "gameplay.h"
#include "time.h"
#include <math.h>
#include "options.h"
#include "shortest_path.h"
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
void print_nopath_win() {
	WINDOW* nopath_win;
	int row, col, x, y, c;

	wclear(stdscr);
	wrefresh(stdscr);
	getmaxyx(stdscr, row, col);
	y = (row - 7) / 2 - 2; x = (col - 46) / 2;
	nopath_win = newwin(5, 46, y, x);
	box(nopath_win, 0, 0);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);

	wbkgd(nopath_win, COLOR_PAIR(2));
	wattron(nopath_win, A_BOLD | COLOR_PAIR(1));
	mvwprintw(nopath_win, 2, 7, "There is no path to the fruit.");
	wattroff(nopath_win, A_BOLD | COLOR_PAIR(1));
	wrefresh(nopath_win);

	int choice = 0;
	while (1) {
		c = wgetch(nopath_win);
		switch (c) {
		case ENTER:
			choice = 1;
			break;
		case K_ESC:
			choice = 1;
			break;
		}
		if (choice)
			break;
	}

}

void demo(short **board, Header * header, Fruit *fruit, int * score, Options *options) {
	WINDOW *game_win;
	WINDOW *box_win;
	srand(time(NULL));
	int row, col, x, r;
	_Bool game_over = FALSE, time_is_up = FALSE;
	int m = options->size.row, n = options->size.col;
	Move initialmove, currentmove;
	Game_mode mode = options->mode;
	initialmove = STOPR;
	currentmove = RIGHT;
	Time currenttime;
	print_begining(board, options, &game_win, &box_win, header, mode, fruit, score, &currenttime, &row, &col, &x, &r);
	clock_t t1, t2;
	double t;
	int eat = 0;
	int i = 0, len, demo = -1;
	double tp, tk, tr;
	tp = clock();
	Move *moves = shortest_path(board,*header, *fruit, m, n, &len);
	tk = clock();
	tr = (tk - tp) / CLOCKS_PER_SEC * 1000;
	currentmove = moves[i++];
	time_is_up = FALSE;
	if (moves == NULL)
		game_over = TRUE;
	int c;
	int exit;

	while (TRUE) {

		if (_kbhit()) {
			c = _getch();
			if (c == PAUSE_CAPITAL || c == PAUSE || c == K_ESC) {
				exit = game_pause(game_win, box_win, board, fruit, header, mode, &initialmove, currentmove, options, score, &demo, &demo);
				if (exit)
					return;
				else {
					exit = K_EXIT;
					box_win = newwin(m + 2, x - 1, (row - m - 2) / 2, r + 1);
					box(box_win, 0, 0);
					wrefresh(box_win);
					print_score(box_win, score);
					print_time(box_win, ceil(currenttime.seconds), ceil(currenttime.minutes));
					wrefresh(box_win);
					continue;
				}
			}
		}


		while (len-- && !time_is_up && !game_over) {//Ovde staje

			if (_kbhit()) {
				c = _getch();
				if (c == PAUSE_CAPITAL || c == PAUSE || c == K_ESC) {
					exit = game_pause(game_win, box_win, board, fruit, header, mode, &initialmove, currentmove, options, score, &demo, &demo);
					if (exit)
						return;
					else {
						exit = K_EXIT;
						box_win = newwin(m + 2, x - 1, (row - m - 2) / 2, r + 1);
						box(box_win, 0, 0);
						wrefresh(box_win);
						print_score(box_win, score);
						print_time(box_win, ceil(currenttime.seconds), ceil(currenttime.minutes));
						wrefresh(box_win);
						continue;
					}
				}
			}

			t1 = clock();
			game_over = board_update(board, m, n, &initialmove, &currentmove, header, fruit, mode, score, game_win, box_win, &demo, &demo,&tr);
			if (fruit->fruit_column == -1)
				game_over = TRUE;
			if (game_over) {
				dead();
				return;
			}
			t2 = clock();
			t = (double)(t2 - t1) / CLOCKS_PER_SEC;
			if (initialmove != STOPR && initialmove != STOPD && initialmove != STOPR && initialmove != STOPU) {
				currenttime = countdown(currenttime, t);
				if (currenttime.minutes >= 0 && currenttime.seconds >= 0) {
					print_time(box_win, ceil(currenttime.seconds), ceil(currenttime.minutes));
				}
				if (currenttime.minutes <= 0 && currenttime.seconds <= 0)
					time_is_up = 1;
			}
			if (time_is_up) {
				timeisup(score, 0, &demo, &demo);
				return 1;
			}
			currentmove = moves[i++];

		}
		free(moves);
		if (!game_over && !time_is_up) {
			i = 0;
			tp = clock();
			moves = shortest_path(board, *header, *fruit, m, n, &len);
			tk = clock();
			tr = (tk - tp) / CLOCKS_PER_SEC * 1000;
			if (moves != NULL) {
				currentmove = moves[i++];
			}
			else {
				game_over = TRUE;
				print_nopath_win();

				wclear(stdscr);
				wrefresh(stdscr);
				print_game(board, game_win, m, n);
				print_fruit(game_win, fruit->fruit_row, fruit->fruit_column);
				Pointer temp;
				temp = header->tail;
				while (temp) {
					print_snake(game_win, temp->row, temp->column);
					temp = temp->next;
				}
				print_snake_head(game_win, header->head->row, header->head->column);
				box_win = newwin(m + 2, x - 1, (row - m - 2) / 2, r + 1);
				box(box_win, 0, 0);
				wrefresh(box_win);
				print_score(box_win, score);
				print_time(box_win, ceil(currenttime.seconds), ceil(currenttime.minutes));
				wrefresh(box_win);

				int choice = 0;
				while (1) {
					c = wgetch(stdscr);
					switch (c) {
					case ENTER:
						choice = 1;
						break;
					case K_ESC:
						choice = 1;
						break;
					}
					if (choice)
						break;
				}
			}
		}
		else if (time_is_up) {
			timeisup(score, 0, &demo, &demo);
			return 1;
		}
		else {
			dead();
			return;
		}


	}
	
	
	
}


/*

currentmove = moves[i++];
switch (currentmove) {
case LEFT:
initialmove = STOPL;
break;
case RIGHT:
initialmove = STOPR;
break;
case DOWN:
initialmove = STOPD;
break;
case UP:
initialmove = STOPU;
break;
}*/