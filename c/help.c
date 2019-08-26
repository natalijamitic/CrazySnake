#include <curses.h>
#include <stdio.h> 
#include "options.h"

void print_help_next(WINDOW *help_win) {
	int row, col, x, y;
	getmaxyx(stdscr, row, col);
	box(help_win, 0, 0);
	wrefresh(help_win);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);

	y = 1; x = 2;
	WINDOW *box1_win;
	box1_win = newwin(3, 12, y, x);
	box(box1_win, 0, 0);
	wbkgd(box1_win, COLOR_PAIR(1));
	wattron(box1_win, A_BOLD | COLOR_PAIR(2));
	mvwprintw(box1_win, 1, 1, "DIFFICULTY");
	wattroff(box1_win, A_BOLD | COLOR_PAIR(2));
	wrefresh(box1_win);
	y = 4; x = 9;
	mvwprintw(help_win, y, x, "Easy - Slow Speed");
	mvwprintw(help_win, y += 2, x, "Medium - Normal Speed");
	mvwprintw(help_win, y += 2, x, "Difficult - Fast Speed");

	y += 2;
	x = 2;
	WINDOW *box2_win;
	box2_win = newwin(3, 8, y, x);
	box(box2_win, 0, 0);
	wbkgd(box2_win, COLOR_PAIR(1));
	wattron(box2_win, A_BOLD | COLOR_PAIR(2));
	mvwprintw(box2_win, 1, 1, "POINTS");
	wattroff(box2_win, A_BOLD | COLOR_PAIR(2));
	wrefresh(box2_win);
	y += 3; x = 9;
	mvwprintw(help_win, y, x, "Each Red Food +5 points");

	y += 2;
	x = 2;
	WINDOW *box3_win;
	box3_win = newwin(3, 6, y, x);
	box(box3_win, 0, 0);
	wbkgd(box3_win, COLOR_PAIR(1));
	wattron(box3_win, A_BOLD | COLOR_PAIR(2));
	mvwprintw(box3_win, 1, 1, "GOAL");
	wattroff(box3_win, A_BOLD | COLOR_PAIR(2));
	wrefresh(box3_win);
	y += 3; x = 9;
	mvwprintw(help_win, y, x, "Eat as much food as possible before the time runs out.");

	x = col - 35;
	y = row - 4;
	mvwprintw(help_win, y, x, "Press any key for previous page");
	mvwprintw(help_win, y += 2, x, "Press ESC for menu page");

	wrefresh(help_win);
}

char open_help_next(void) {
	clear();
	refresh();
	WINDOW *help_win;
	int row, col, c, x, y;
	getmaxyx(stdscr, row, col);
	help_win = newwin(row, col, 0, 0);
	print_help_next(help_win);

	c = wgetch(help_win);
	if (c)
		return c;
}

void print_help(WINDOW *help_win) {
	int row, col, x, y;

	getmaxyx(stdscr, row, col);
	box(help_win, 0, 0);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);

	y = 1; x = col / 2 - 5;
	WINDOW *box0_win;
	box0_win = newwin(3, 10, y, x);
	box(box0_win, 0, 0);
	wbkgd(box0_win, COLOR_PAIR(2));
	wattron(box0_win, A_BOLD | A_UNDERLINE | COLOR_PAIR(1));
	mvwprintw(box0_win, 1, 3, "HELP");
	wattroff(box0_win, A_BOLD | A_UNDERLINE | COLOR_PAIR(1));
	wrefresh(help_win);
	wrefresh(box0_win);

	y = 5; x = 2;
	WINDOW *box_win;
	box_win = newwin(3, 14, y, x);
	box(box_win, 0, 0);
	wbkgd(box_win, COLOR_PAIR(1));
	wattron(box_win, A_BOLD | COLOR_PAIR(2));
	mvwprintw(box_win, 1, 1, "INSTRUCTIONS");
	wattroff(box_win, A_BOLD | COLOR_PAIR(2));
	wrefresh(box_win);

	y = 8; x = 9;
	mvwprintw(help_win, y, x, "Use Arrow Keys To Move The Snake:");
	y += 2; x += 2;
	mvwprintw(help_win, y, x, "UP");
	y += 2;
	mvwprintw(help_win, y, x, "DOWN");
	y += 2;
	mvwprintw(help_win, y, x, "LEFT");
	y += 2;
	mvwprintw(help_win, y, x, "RIGHT");
	y += 5; x -= 2;
	mvwprintw(help_win, y, x, "PAUSE   P");
	y += 2;
	mvwprintw(help_win, y, x, "EXIT/BACK   ESC");

	y = 9; x = 35;
	WINDOW *n_win;
	n_win = newwin(5, 8, y, x);
	box(n_win, 0, 0);
	y += 2, x += 3;
	wrefresh(n_win);
	mvwprintw(help_win, y, x, "/\\");
	wrefresh(help_win);

	y = 14; x = 35;
	WINDOW *n_win2;
	n_win2 = newwin(5, 8, y, x);
	box(n_win2, 0, 0);
	y += 2, x += 3;
	mvwprintw(help_win, y, x, "\\/");
	wrefresh(n_win2);
	wrefresh(help_win);

	y = 14; x = 27;
	WINDOW *n_win3;
	n_win3 = newwin(5, 8, y, x);
	box(n_win3, 0, 0);
	y += 2, x += 4;
	mvwprintw(help_win, y, x, "<");
	wrefresh(n_win3);
	wrefresh(help_win);

	y = 14; x = 43;
	WINDOW *n_win4;
	n_win4 = newwin(5, 8, y, x);
	box(n_win4, 0, 0);
	y += 2, x += 3;
	mvwprintw(help_win, y, x, ">");
	wrefresh(n_win4);
	wrefresh(help_win);

	x = col - 35;
	y = row - 4;
	mvwprintw(help_win, y, x, "Press any key for next page");
	y += 2;
	mvwprintw(help_win, y, x, "Press ESC for menu page");
	wrefresh(help_win);

}

void open_help(void) {
	clear();
	refresh();
	int c, row, col;
	getmaxyx(stdscr, row, col);

	WINDOW *help_win;
	help_win = newwin(row, col, 0, 0);
	print_help(help_win);

	c = wgetch(help_win);
	while (c != K_ESC) {
		c = open_help_next();
		if (c != K_ESC) {
			clear();
			WINDOW *help2_win;
			help2_win = newwin(row, col, 0, 0);
			print_help(help2_win);
			c = wgetch(help2_win);
		}
	}

	return;

}
