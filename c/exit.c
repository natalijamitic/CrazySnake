#include <curses.h>
#include <stdio.h> 
#include "options.h"
void print_exit(WINDOW *exit_win, int highlight) {
	int row, col, x, y;

	getmaxyx(stdscr, row, col);
	box(exit_win, 0, 0);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_MAGENTA);

	y = (row - 7) / 2 - 2; x = (col - 46) / 2;
	WINDOW *box1_win;
	box1_win = newwin(7, 46, y, x);
	box(box1_win, 0, 0);
	wbkgd(box1_win, COLOR_PAIR(2));
	wattron(box1_win, A_BOLD | COLOR_PAIR(1));
	mvwprintw(box1_win, 1, 3, "Are you sure you want to exit this game?");
	wattroff(box1_win, A_BOLD | COLOR_PAIR(1));
	wrefresh(exit_win);
	wrefresh(box1_win);

	y += 3; x += 10;
	WINDOW *yes_win;
	yes_win = newwin(3, 10, y, x);
	box(yes_win, 0, 0);
	wbkgd(yes_win, COLOR_PAIR(1));
	wattron(yes_win, A_BOLD);
	if (highlight == 1)
		wattron(yes_win, COLOR_PAIR(3));
	mvwprintw(yes_win, 1, 3, "YES");
	if (highlight == 1)
		wattroff(yes_win, COLOR_PAIR(3));
	wattroff(yes_win, A_BOLD);
	wrefresh(exit_win);
	wrefresh(yes_win);

	x += 15;
	WINDOW *no_win;
	no_win = newwin(3, 10, y, x);
	box(no_win, 0, 0);
	wbkgd(no_win, COLOR_PAIR(1));
	wattron(no_win, A_BOLD);
	if (highlight == 2)
		wattron(no_win, COLOR_PAIR(3));
	mvwprintw(no_win, 1, 4, "NO");
	if (highlight == 2)
		wattroff(no_win, COLOR_PAIR(3));
	wattroff(no_win, A_BOLD);
	wrefresh(exit_win);
	wrefresh(no_win);


	wrefresh(exit_win);
}

void open_exit(void) {
	clear();
	noecho();
	cbreak();
	int choose, row, col, x, y, highlight = 1, choice = 0;
	getmaxyx(stdscr, row, col);

	WINDOW *exit_win;
	exit_win = newwin(row, col, 0, 0);
	box(exit_win, 0, 0);
	keypad(exit_win, TRUE);
	refresh();

	print_exit(exit_win, highlight);

	while (TRUE) {
		choose = wgetch(exit_win);
		switch (choose) {
		case KEY_LEFT:
			if (highlight == 1)
				highlight = 2;
			else
				--highlight;
			break;
		case KEY_RIGHT:
			if (highlight == 2)
				highlight = 1;
			else
				++highlight;
			break;
		case ENTER:
			choice = highlight;
			break;
		case K_ESC:
			choice = BACK3;
		}
		print_exit(exit_win, highlight);
		if (choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}

	if (choice == 1)
		exit(1);
	else if (choice == 2 || choice == K_ESC)
		return;
}
