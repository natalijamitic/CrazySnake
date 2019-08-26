#include <curses.h>
#include <stdio.h> 
#include "options.h"

char *choices[] = {
	"NEW GAME",
	"CONTINUE",
	"DEMO MODE",
	"HIGH SCORES",
	"OPTIONS",
	"HELP",
	"ABOUT",
	"AUTHORS",
	"EXIT",
};
int n_choices = sizeof(choices) / sizeof(char *);

void print_menu(WINDOW *menu_win, int highlight, int row, int col) {
	int x, y, i;

	x = 10;
	y = (row - 20) / 2;
	box(menu_win, 0, 0);
	wrefresh(menu_win);
	crazy_snake(row, col);
	for (i = 0; i < n_choices; ++i) {
		if (highlight == i + 1) /* Highlight the present choice */ {
			start_color();
			init_pair(1, COLOR_GREEN, COLOR_MAGENTA);
			wattron(menu_win, COLOR_PAIR(1) | A_BOLD);
			mvwprintw(menu_win, y, x, "%s", choices[i]);
			wattroff(menu_win, COLOR_PAIR(1) | A_BOLD);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choices[i]);
		y += 2;
	}
	wrefresh(menu_win);
}

int open_menu(int row, int col) {
	WINDOW *menu_win;

	int highlight = 1, choice = 0;
	int choose;
	initscr();
	clear();
	noecho();
	cbreak();
	curs_set(0);

	menu_win = newwin(row, col, 0, 0);
	keypad(menu_win, TRUE);
	refresh();

	print_menu(menu_win, highlight, row, col);

	while (TRUE) {
		choose = wgetch(menu_win);
		switch (choose) {
		case KEY_UP:
			if (highlight == 1)
				highlight = n_choices;
			else
				--highlight;
			break;
		case KEY_DOWN:
			if (highlight == n_choices)
				highlight = 1;
			else
				++highlight;
			break;
		case ENTER:
			choice = highlight;
			break;
		case K_ESC:
			choice = K_ESC;
			break;
		}
		print_menu(menu_win, highlight, row, col);
		if (choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}
	if (choice == K_ESC)
		return 9;
	return highlight;
}
