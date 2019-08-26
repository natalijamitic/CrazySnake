
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include "gameplay.h"
#include "save_game.h" 
#include "options.h"
#include "highscore.h"
HANDLE wHnd;

#define POINT 5

void print_continue(void) {
	int x, y, row, col, c, choice = 0;
	WINDOW *cont_win;
	wclear(stdscr);
	wrefresh(stdscr);
	getmaxyx(stdscr, row, col);
	y = (row - 7) / 2 - 2; x = (col - 46) / 2;
	cont_win = newwin(5, 46, y, x);
	box(cont_win, 0, 0);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	wbkgd(cont_win, COLOR_PAIR(2));
	wattron(cont_win, A_BOLD | COLOR_PAIR(1));
	mvwprintw(cont_win, 2, 2, "There is no saved game. Start a new game.");
	wattroff(cont_win, A_BOLD | COLOR_PAIR(1));
	x = col - 35;
	y = row - 2;
	mvprintw(y, x, "Press ESC for menu page");
	wrefresh(cont_win);
	refresh();
	while (1) {
		c = wgetch(cont_win);
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

void print_score(WINDOW *box_win, int *score) {
	init_pair(5, COLOR_GREEN, COLOR_BLACK);
	wattron(box_win, COLOR_PAIR(5) | A_BOLD);
	mvwprintw(box_win, 2, 3, "Time: ");
	mvwprintw(box_win, 4, 3, "Score: %d", *score);
	wattroff(box_win, COLOR_PAIR(5) | A_BOLD);
	wrefresh(box_win);
}

void print_time(WINDOW *box_win, int sec, int min) {
	init_pair(5, COLOR_GREEN, COLOR_BLACK);
	wattron(box_win, COLOR_PAIR(5) | A_BOLD);
	if (sec == 60) {
		sec = 0;
		min++;
	}
	mvwprintw(box_win, 2, 8, " %0.2d:%0.2d", min, sec);
	wattroff(box_win, COLOR_PAIR(5) | A_BOLD);
	wrefresh(box_win);

}

void print_snake(WINDOW* game_win, int row, int col) {
	int x = row + 1, y = col + 1;
	init_pair(1, COLOR_GREEN, COLOR_GREEN);
	wattron(game_win, COLOR_PAIR(1));
	mvwprintw(game_win, x, y, " ");
	wattroff(game_win, COLOR_PAIR(1));
	wrefresh(game_win);
}

void print_snake_head(WINDOW *game_win, int row, int col) {
	int x = row + 1, y = col + 1;
	init_pair(9, COLOR_GREEN, COLOR_BLUE);
	wattron(game_win, COLOR_PAIR(9) | A_BOLD);
	mvwprintw(game_win, x, y, "*");
	wattroff(game_win, COLOR_PAIR(9) | A_BOLD);
	wrefresh(game_win);
}

void delete_snake(WINDOW* game_win, int row, int col) {
	int x = row + 1, y = col + 1;
	init_pair(8, COLOR_BLACK, COLOR_BLACK);
	wattron(game_win, COLOR_PAIR(8));
	mvwprintw(game_win, x, y, " ");
	wattroff(game_win, COLOR_PAIR(8));
	wrefresh(game_win);
}

void print_fruit(WINDOW* game_win, int row, int col) {
	int x = row + 1, y = col + 1;
	init_pair(3, COLOR_RED, COLOR_RED);
	wattron(game_win, COLOR_PAIR(3));
	mvwprintw(game_win, x, y, " ");
	wattroff(game_win, COLOR_PAIR(3));
	wrefresh(game_win);

}

void one_move(short ** board, int m, int n, Move* initialmove, Move *currentmove, Header * header, WINDOW*game_win) {
	int x = header->head->column, y = header->head->row;
	if (*initialmove == DOWN && *currentmove == UP) {
		if (++y == m)
			y = 0;
	}
	else
		if (*initialmove == UP && *currentmove == DOWN) {
			if (--y == -1)
				y = m - 1;
		}
		else
			if (*initialmove == RIGHT && *currentmove == LEFT) {
				if (++x == n)
					x = 0;
			}
			else
				if (*initialmove == LEFT && *currentmove == RIGHT) {
					if (--x == -1)
						x = n - 1;
				}
				else {
					switch (*currentmove) {
					case DOWN:
						if (STOPU != *initialmove) {
							if (++y == m) y = 0;
							*initialmove = *currentmove;
						}
						break;
					case LEFT:
						if (STOPR != *initialmove) {
							if (--x == -1)
								x = n - 1;
							*initialmove = *currentmove;
						}
						break;
					case RIGHT:
						if (STOPL != *initialmove) {
							if (++x == n)
								x = 0;
							*initialmove = *currentmove;
						}
						break;
					case UP:
						if (STOPD != *initialmove) {
							if (--y == -1)
								y = m - 1;
							*initialmove = *currentmove;
						}
						break;
					}
				}


				if (*initialmove != STOPR && *initialmove != STOPD && *initialmove != STOPR && *initialmove != STOPU) {
					Pointer temp;
					temp = (Pointer)malloc(sizeof(Element));
					if (temp == NULL)
						exit(EXIT_FAILURE);
					temp->column = x;
					temp->row = y;
					header->head->next = temp;
					temp->next = NULL;
					header->head = temp;
				}
}

_Bool board_update(short ** board, int m, int n, Move *initialmove, Move *currentmove, Header *header, Fruit *fruit, Game_mode mode, int *score, WINDOW *game_win, WINDOW *box_win, int *len, int *total, double  *eat) {
	_Bool game_over;
	double t1, t2, t;
	print_snake(game_win, header->head->row, header->head->column);
	one_move(board, m, n, initialmove, currentmove, header, game_win);
	int i = header->head->row, j = header->head->column;
	if (*initialmove != STOPR && *initialmove != STOPD && *initialmove != STOPR && *initialmove != STOPU) {
		if (board[i][j] == OBSTACLE || board[i][j] == SNAKE)
			return game_over = 1;
		t = 0;
		if (board[i][j] == FRUIT) {
			board[fruit->fruit_row][fruit->fruit_column] = SNAKE;
			*fruit = generate_fruit(board, m, n);
			if (fruit->fruit_row == -1) {
				return;
			}
			*score += POINT;
			if (mode != HARD)
				print_snake_head(game_win, i, j);
			else
				print_snake(game_win, i, j);
			if (*total != -1)
				*total = *total + 1;
			print_fruit(game_win, fruit->fruit_row, fruit->fruit_column);
			print_score(box_win, score);
			
			if (*len != -1) {
				t1 = clock();
				*len = *len + shortest_path_length(board, *header, *fruit, m, n);
				t2 = clock();
				t = (t2 - t1) / CLOCKS_PER_SEC;
				t *= 1000;
			}
		}
		else {
			Pointer temp = header->tail;
			int r = temp->row, c = temp->column;
			delete_snake(game_win, r, c);
			board[r][c] = FREE;
			header->tail = header->tail->next;
			free(temp);
			r = header->head->row;
			c = header->head->column;
			board[r][c] = SNAKE;
			if (mode != HARD)
				print_snake_head(game_win, r, c);
			else
				print_snake(game_win, r, c);
			if (*total != -1)
				*total = *total + 1;
		}
	}

	if (*initialmove != STOPR && *initialmove != STOPD && *initialmove != STOPR && *initialmove != STOPU) {
		if (*currentmove == RIGHT || *currentmove == LEFT) {
			switch (mode) {
			case EASY:
				if (EASY_SPEED - t < 0)
					t = EASY_SPEED;
				if (EASY_SPEED - *eat < 0)
					*eat = EASY_SPEED;
				if (*len != -1)
					*eat = 0;
				Sleep((EASY_SPEED - t-*eat) / 2);
				break;
			case MEDIUM:
				if (MEDIUM_SPEED - t < 0)
					t = MEDIUM_SPEED;
				if (MEDIUM_SPEED - *eat < 0)
					*eat = MEDIUM_SPEED;
				if (*len != -1)
					*eat = 0;
				Sleep((MEDIUM_SPEED - t-*eat) / 2);
				break;
			case HARD:
				if (HARD_SPEED - t < 0)
					t = HARD_SPEED;
				if (HARD_SPEED - *eat <0 )
					*eat = HARD_SPEED;
				if (*len!=-1)
					*eat = 0;
				Sleep((HARD_SPEED -t-*eat) / 2);
				break;
			}
		}
		else {
			switch (mode) {
			case EASY:
				if (EASY_SPEED - t < 0)
					t = EASY_SPEED;
				if (EASY_SPEED - *eat < 0)
					*eat = EASY_SPEED;
				if (*len != -1)
					*eat = 0;
				Sleep(EASY_SPEED - t-*eat);
				break;
			case MEDIUM:
				if (MEDIUM_SPEED - t < 0)
					t = MEDIUM_SPEED;
				if (MEDIUM_SPEED - *eat < 0)
					*eat = MEDIUM_SPEED;
				if (*len != -1)
					*eat = 0;
				Sleep(MEDIUM_SPEED - t-*eat);
				break;
			case HARD:
				if (HARD_SPEED - t < 0)
					t = HARD_SPEED;
				if (HARD_SPEED - *eat < 0 )
					*eat = HARD_SPEED;
				if (*len != -1)
					*eat = 0;
				Sleep(HARD_SPEED -t-*eat);
				break;
			}
		}
		*eat = 0;
	}
	return game_over = 0;
}

void print_game(short **table, WINDOW *game_win, int m, int n) {
	int i, j;
	wclear(game_win);

	init_pair(1, COLOR_GREEN, COLOR_GREEN);
	init_pair(2, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(3, COLOR_RED, COLOR_RED);
	init_pair(4, COLOR_BLUE, COLOR_BLUE);



	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++) {
			if (table[i][j] == OBSTACLE) {
				wattron(game_win, COLOR_PAIR(2));
				int t = i + 1, z = j + 1;
				mvwprintw(game_win, t, z, " ");
				wattroff(game_win, COLOR_PAIR(2));
				wrefresh(game_win);
			}
		}
	box(game_win, 0, 0);
	wrefresh(game_win);
}

void print_game_pause(WINDOW *pause_win, int highlight) {
	int row, col;
	getmaxyx(stdscr, row, col);
	int y = (row - 7) / 2 - 2, x = (col - 46) / 2;

	init_pair(11, COLOR_GREEN, COLOR_BLACK);
	init_pair(22, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(33, COLOR_GREEN, COLOR_MAGENTA);
	y += 3; x += 5;
	WINDOW *yes_win;
	yes_win = newwin(3, 15, y, x);
	box(yes_win, 0, 0);
	wbkgd(yes_win, COLOR_PAIR(11));
	wattron(yes_win, A_BOLD);
	if (highlight == 1)
		wattron(yes_win, COLOR_PAIR(33));
	mvwprintw(yes_win, 1, 4, "CONTINUE");
	if (highlight == 1)
		wattroff(yes_win, COLOR_PAIR(33));
	wattroff(yes_win, A_BOLD);
	wrefresh(pause_win);
	wrefresh(yes_win);

	x += 20;
	WINDOW *no_win;
	no_win = newwin(3, 15, y, x);
	box(no_win, 0, 0);
	wbkgd(no_win, COLOR_PAIR(11));
	wattron(no_win, A_BOLD);
	if (highlight == 2)
		wattron(no_win, COLOR_PAIR(33));
	mvwprintw(no_win, 1, 5, "EXIT");
	if (highlight == 2)
		wattroff(no_win, COLOR_PAIR(33));
	wattroff(no_win, A_BOLD);
	wrefresh(pause_win);
	wrefresh(no_win);
}

int game_pause(WINDOW *game_win, WINDOW *box_win, short **board, Fruit *fruit, Header *header, Game_mode mode, Move *initialmove, Move currentmove, Options * option, int *score, int *len, int *total) {
	int row, col;
	getmaxyx(stdscr, row, col);
	int y = (row - 7) / 2 - 2, x = (col - 46) / 2, highlight = 1, choice = 0, choose;
	wclear(stdscr);
	wrefresh(stdscr);
	initscr();
	clear();
	int m = option->size.row, n = option->size.col;
	refresh();
	WINDOW *pause_win;
	pause_win = newwin(7, 46, y, x);
	box(pause_win, 0, 0);
	keypad(pause_win, TRUE);
	wrefresh(game_win);
	init_pair(11, COLOR_GREEN, COLOR_BLACK);
	init_pair(22, COLOR_MAGENTA, COLOR_BLACK);

	wbkgd(pause_win, COLOR_PAIR(22));
	wattron(pause_win, A_BOLD | COLOR_PAIR(11));
	mvwprintw(pause_win, 1, 12, "You paused the game.");
	wattroff(pause_win, A_BOLD | COLOR_PAIR(11));
	wrefresh(pause_win);

	print_game_pause(pause_win, highlight);

	while (1) {
		choose = _getch();
		if (choose == READY)
			choose = _getch();
		switch (choose) {
		case K_LEFT:
			if (highlight == 1)
				highlight = 2;
			else
				--highlight;
			break;
		case K_RIGHT:
			if (highlight == 2)
				highlight = 1;
			else
				++highlight;
			break;
		case K_EXIT:
			choice = highlight;
			break;
		}
		print_game_pause(pause_win, highlight);
		if (choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}

	if (choice == 1) {
		wclear(pause_win);
		wrefresh(pause_win);
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
		return 0;
	}
	else if (choice == 2) {
		switch (currentmove) {
		case DOWN:
			*initialmove = STOPD;
			break;
		case UP:
			*initialmove = STOPU;
			break;
		case LEFT:
			*initialmove = STOPL;
			break;
		case RIGHT:
			*initialmove = STOPR;
			break;
		}
		if (*len != -1 && *total != -1)
			savegame(option, *initialmove, currentmove, board, *score, *header, *fruit, *len, *total);
		return 1;
	}
	return 0;
}

void dead(void) {
	WINDOW* dead_win;
	int row, col, x, y, c;

	wclear(stdscr);
	wrefresh(stdscr);
	getmaxyx(stdscr, row, col);
	y = (row - 7) / 2 - 2; x = (col - 46) / 2;
	dead_win = newwin(5, 46, y, x);
	box(dead_win, 0, 0);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_MAGENTA);

	wbkgd(dead_win, COLOR_PAIR(2));
	wattron(dead_win, A_BOLD | COLOR_PAIR(1));
	mvwprintw(dead_win, 2, 18, "You lost.");
	wattroff(dead_win, A_BOLD | COLOR_PAIR(1));
	wrefresh(dead_win);
	int choice = 0;
	while (1) {
		c = wgetch(dead_win);
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

void timeisup(int *score, int is_top, int *len, int *total) {
	WINDOW* timeup_win;
	int row, col, x, y, c;

	wclear(stdscr);
	wrefresh(stdscr);
	getmaxyx(stdscr, row, col);
	y = (row - 7) / 2 - 2; x = (col - 46) / 2 - 2;
	timeup_win = newwin(5, 50, y, x);
	box(timeup_win, 0, 0);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_MAGENTA);

	int maxscore = *score * *total / *len;
	if (maxscore % 5 < 3)
		maxscore = maxscore / 5 * 5;
	else maxscore = maxscore / 5 * 5 + 5;

	wbkgd(timeup_win, COLOR_PAIR(2));
	wattron(timeup_win, A_BOLD | COLOR_PAIR(1));
	mvwprintw(timeup_win, 2, 3, "Time is up. You scored %d points out of %d.", *score, maxscore);
	wattroff(timeup_win, A_BOLD | COLOR_PAIR(1));
	wrefresh(timeup_win);

	int choice = 0;
	while (1) {
		c = wgetch(timeup_win);
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

	int place;

	if (is_top) {
		place = topTen(*score);
		wclear(stdscr);
		wrefresh(stdscr);
		print_Highscore_underline(place);
	}
	return;
}

void command(short ** board, Time *currenttime, Options *options, Move *initialmove, Move * currentmove, Fruit *fruit, WINDOW *game_win, WINDOW* box_win, Header *header, int *score, _Bool *game_over, _Bool *time_is_up, int *len, int *total, double *eat) {
	double t1, t2, t;
	t1 = clock();
	*game_over = board_update(board, options->size.row, options->size.col, initialmove, currentmove, header, fruit, options->mode, score, game_win, box_win, len, total, eat);
	if (fruit->fruit_row == -1) {
		*time_is_up = TRUE;
		return;
	}
	if (*game_over)
		return;
	t2 = clock();
	t = (double)(t2 - t1) / CLOCKS_PER_SEC;
	if (*initialmove != STOPR && *initialmove != STOPD && *initialmove != STOPR && *initialmove != STOPU) {
		*currenttime = countdown(*currenttime, t);
		options->minutes = currenttime->minutes;
		options->seconds = currenttime->seconds;
		if (currenttime->minutes >= 0 && currenttime->seconds >= 0) {
			print_time(box_win, ceil(currenttime->seconds), ceil(currenttime->minutes));
		}
		if (currenttime->minutes <= 0 && currenttime->seconds <= 0)
			*time_is_up = TRUE;
	}
}

void print_begining(short **board, Options *options, WINDOW **game_win, WINDOW **box_win, Header *header, int mode, Fruit *fruit, int *score, Time *currenttime, int *row, int *col, int *x, int *r) {
	initscr();
	clear();
	noecho();
	cbreak();
	start_color();
	curs_set(0);
	//resize_term(m + 2, n + 22);
	int m = options->size.row, n = options->size.col;
	getmaxyx(stdscr, *row, *col);
	*game_win = newwin(m + 2, n + 2, (*row - m - 2) / 2, (*col - n - 22) / 2);
	*r = (*col - n - 22) / 2 + n + 2;
	keypad(*game_win, TRUE);
	wrefresh(*game_win);

	init_pair(1, COLOR_GREEN, COLOR_GREEN);
	init_pair(2, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(3, COLOR_RED, COLOR_RED);
	init_pair(4, COLOR_BLUE, COLOR_BLUE);

	print_game(board, *game_win, m, n);
	print_fruit(*game_win, fruit->fruit_row, fruit->fruit_column);
	Pointer temp;
	temp = header->tail;
	while (temp) {
		print_snake(*game_win, temp->row, temp->column);
		temp = temp->next;
	}
	print_snake_head(*game_win, header->head->row, header->head->column);
	*x = 20;
	*box_win = newwin(m + 2, *x - 1, (*row - m - 2) / 2, *r + 1);
	box(*box_win, 0, 0);
	wrefresh(*box_win);
	currenttime->minutes = options->minutes;
	currenttime->seconds = options->seconds;
	print_score(*box_win, score);
	print_time(*box_win, ceil(currenttime->seconds), ceil(currenttime->minutes));
}

int gameplay(short **board, Header *header, Fruit *fruit, Options *options, Move *initialmove, Move *currentmove, int *score, int *len, int *total) {
	WINDOW *game_win;
	WINDOW *box_win;
	srand(time(NULL));
	int row, col, x, r;
	_Bool game_over = FALSE, time_is_up = FALSE;
	Game_mode mode = options->mode;
	Time currenttime;
	print_begining(board, options, &game_win, &box_win, header, mode, fruit, score, &currenttime, &row, &col, &x, &r);
	int m = options->size.row, n = options->size.col;
	char move;
	int u = FALSE;
	int exit;
	double eat = 0;
	while (!game_over && !time_is_up) {
		exit = FALSE;

		if (_kbhit() || u) {
			if (u == FALSE) {
				move = _getch();
				if (move == READY)
					move = _getch();
				else if (move == PAUSE_CAPITAL || move == PAUSE || move == K_ESC) {
					exit = game_pause(game_win, box_win, board, fruit, header, mode, initialmove, *currentmove, options, score, len, total);
					if (exit)
						return ALIVE;
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
			switch (move) {
			case K_DOWN: {
				if (*currentmove == UP)
					break;
				while (move == K_DOWN) {
					*currentmove = DOWN;
					command(board, &currenttime, options, initialmove, currentmove, fruit, game_win, box_win, header, score, &game_over, &time_is_up, len, total, &eat);
					if (time_is_up || game_over)
						break;
					if (_kbhit()) {
						move = _getch();
						if (move == READY) {
							move = _getch();
							if (move == K_LEFT || move == K_RIGHT)
								break;
							else
								move = K_DOWN;
						}
						else
							if (move == PAUSE_CAPITAL || move == PAUSE || move == K_ESC) {
								exit = game_pause(game_win, box_win, board, fruit, header, mode, initialmove, *currentmove, options, score, len, total);
								if (exit)
									return ALIVE;
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
								//move = K_DOWN;
							}
							else move = K_DOWN;
					}
					else move = K_DOWN;
				}
				u = TRUE;
				if (exit == K_EXIT)
					u = FALSE;
				break;
			}
			case K_LEFT: {
				if (*currentmove == RIGHT)
					break;
				while (move == K_LEFT) {
					*currentmove = LEFT;
					command(board, &currenttime, options, initialmove, currentmove, fruit, game_win, box_win, header, score, &game_over, &time_is_up, len, total, &eat);
					if (time_is_up || game_over)
						break;
					if (_kbhit()) {
						move = _getch();
						if (move == READY) {
							move = _getch();
							if (move == K_UP || move == K_DOWN)
								break;
							else
								move = K_LEFT;
						}
						else
							if (move == PAUSE_CAPITAL || move == PAUSE || move == K_ESC) {
								exit = game_pause(game_win, box_win, board, fruit, header, mode, initialmove, *currentmove, options, score, len, total);
								if (exit)
									return ALIVE;
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
								//move = K_LEFT;
							}
							else
								move = K_LEFT;
					}
					else
						move = K_LEFT;
				}
				u = TRUE;
				if (exit == K_EXIT)
					u = FALSE;
				break;
			}
			case K_RIGHT: {
				if (*currentmove == LEFT)
					break;
				while (move == K_RIGHT) {
					*currentmove = RIGHT;
					command(board, &currenttime, options, initialmove, currentmove, fruit, game_win, box_win, header, score, &game_over, &time_is_up, len, total, &eat);
					if (time_is_up || game_over)
						break;
					if (_kbhit()) {
						move = _getch();
						if (move == READY) {
							move = _getch();
							if (move == K_UP || move == K_DOWN)
								break;
							else
								move = K_RIGHT;
						}
						else
							if (move == PAUSE_CAPITAL || move == PAUSE || move == K_ESC) {
								exit = game_pause(game_win, box_win, board, fruit, header, mode, initialmove, *currentmove, options, score, len, total, &eat);
								if (exit)
									return ALIVE;
								else {
									box_win = newwin(m + 2, x - 1, (row - m - 2) / 2, r + 1);
									box(box_win, 0, 0);
									wrefresh(box_win);
									print_score(box_win, score);
									print_time(box_win, ceil(currenttime.seconds), ceil(currenttime.minutes));
									wrefresh(box_win);
									exit = K_EXIT;
									continue;
								}
								//move = K_RIGHT;
							}
							else
								move = K_RIGHT;
					}
					else
						move = K_RIGHT;
				}
				u = TRUE;
				if (exit == K_EXIT)
					u = FALSE;
				break;
			}
			case K_UP: {
				if (*currentmove == DOWN)
					break;
				while (move == K_UP) {
					*currentmove = UP;
					command(board, &currenttime, options, initialmove, currentmove, fruit, game_win, box_win, header, score, &game_over, &time_is_up, len, total, &eat);
					if (time_is_up || game_over)
						break;
					if (_kbhit()) {
						move = _getch();
						if (move == READY) {
							move = _getch();
							if (move == K_LEFT || move == K_RIGHT)
								break;
							else move = K_UP;
						}
						else
							if (move == PAUSE_CAPITAL || move == PAUSE || move == K_ESC) {
								exit = game_pause(game_win, box_win, board, fruit, header, mode, initialmove, *currentmove, options, score, len, total);
								if (exit)
									return ALIVE;
								else {
									box_win = newwin(m + 2, x - 1, (row - m - 2) / 2, r + 1);
									box(box_win, 0, 0);
									wrefresh(box_win);
									print_score(box_win, score);
									print_time(box_win, ceil(currenttime.seconds), ceil(currenttime.minutes));
									wrefresh(box_win);
									exit = K_EXIT;
									continue;
								}
								//a = K_UP;
							}
							else
								move = K_UP;
					}
					else
						move = K_UP;
				}
				u = TRUE;
				if (exit == K_EXIT)
					u = FALSE;
				break;
			}
			}

		}

	}

	if (time_is_up) {
		timeisup(score, 1, len, total);
		return TIMEISUP;
	}
	if (game_over) {
		dead();
		return HITWALL;
	}
	return 0;
}