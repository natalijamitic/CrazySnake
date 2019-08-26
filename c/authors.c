#include <curses.h>
#include <stdio.h> 

void open_authors(void) {
	clear();
	refresh();
	int c, row, col, x, y;
	getmaxyx(stdscr, row, col);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);

	WINDOW *authors_win;
	authors_win = newwin(row, col, 0, 0);
	box(authors_win, 0, 0);

	y = 1; x = col / 2 - 7;
	WINDOW *box0_win;
	box0_win = newwin(3, 13, y, x);
	box(box0_win, 0, 0);
	wbkgd(box0_win, COLOR_PAIR(2));
	wattron(box0_win, A_BOLD | A_UNDERLINE | COLOR_PAIR(1));
	mvwprintw(box0_win, 1, 3, "AUTHORS");
	wattroff(box0_win, A_BOLD | A_UNDERLINE | COLOR_PAIR(1));
	wrefresh(authors_win);
	wrefresh(box0_win);

	y = 7; x = 9;
	wattron(authors_win, COLOR_PAIR(2));
	mvwprintw(authors_win, y, x, "*");
	mvwprintw(authors_win, y += 2, x, "*");
	mvwprintw(authors_win, y += 2, x, "*");
	mvwprintw(authors_win, y += 2, x, "*");
	wattroff(authors_win, COLOR_PAIR(2));
	y = 7;
	mvwprintw(authors_win, y, x += 2, "Mitic Natalija");
	mvwprintw(authors_win, y += 2, x, "Stijovic Dusan");
	mvwprintw(authors_win, y += 2, x, "Spehar Luka");
	mvwprintw(authors_win, y += 2, x, "Mentor: Jezdic Jakov");

	x = col - 30, y = row - 2;
	mvwprintw(authors_win, y, x, "Press ESC for menu page");



	c = wgetch(authors_win);
	while (c != 27)
		c = wgetch(authors_win);
	return;

}
