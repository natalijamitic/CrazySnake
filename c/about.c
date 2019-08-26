#include <curses.h>
#include <stdio.h> 

void open_about(void) {
	clear();
	refresh();
	int c, row, col, x, y;
	getmaxyx(stdscr, row, col);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);

	WINDOW *about_win;
	about_win = newwin(row, col, 0, 0);
	box(about_win, 0, 0);

	y = 1; x = col / 2 - 6;
	WINDOW *box0_win;
	box0_win = newwin(3, 11, y, x);
	box(box0_win, 0, 0);
	wbkgd(box0_win, COLOR_PAIR(2));
	wattron(box0_win, A_BOLD | A_UNDERLINE | COLOR_PAIR(1));
	mvwprintw(box0_win, 1, 3, "ABOUT");
	wattroff(box0_win, A_BOLD | A_UNDERLINE | COLOR_PAIR(1));
	wrefresh(about_win);
	wrefresh(box0_win);

	y = 7; x = col / 2 - 40;
	mvwprintw(about_win, y, x, "Snake is a video game concept where the player maneuvers a line which grows in");
	mvwprintw(about_win, ++y, x, "length when eating food, with the line itself being a primary obstacle.");
	mvwprintw(about_win, y += 2, x, "The concept originated in the 1976 arcade game Blockade developed by Gremlin.");
	mvwprintw(about_win, ++y, x, "Nowadays there are over hundreds of versions of this game.");
	mvwprintw(about_win, y += 2, x, "This version of Snake game has been created as a homework assignment for");
	mvwprintw(about_win, ++y, x, "the subject Programming Practicum 2 at the Faculty of Electrical Engineering.");
	mvwprintw(about_win, y = 18, x = col - 40, "June 2018, Belgrade");

	x = col - 30, y = row - 2;
	mvwprintw(about_win, y, x, "Press ESC for menu page");

	c = wgetch(about_win);
	while (c != 27)
		c = wgetch(about_win);
	return;

}
