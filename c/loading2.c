#include <curses.h>
#include <stdio.h> 

void loading2_part2(WINDOW* load_win, int i, int x, int y) {
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);

	if (i % 4 == 0) {
		wattron(load_win, COLOR_PAIR(1));
		mvwprintw(load_win, y, x, "LOADING     ");
		wattroff(load_win, COLOR_PAIR(1));
		
	}
	else if (i % 4 == 1) {
		wattron(load_win, COLOR_PAIR(1));
		mvwprintw(load_win, y, x, "LOADING");
		wattroff(load_win, COLOR_PAIR(1));
		int t = x + 7;
		wattron(load_win, COLOR_PAIR(2));
		mvwprintw(load_win, y, t, ".    ");
		wattroff(load_win, COLOR_PAIR(2));

	}
	else if (i % 4 == 2) {
		wattron(load_win, COLOR_PAIR(1));
		mvwprintw(load_win, y, x, "LOADING");
		wattroff(load_win, COLOR_PAIR(1));
		int t = x + 7;
		wattron(load_win, COLOR_PAIR(2));
		mvwprintw(load_win, y, t, "..   ");
		wattroff(load_win, COLOR_PAIR(2));
	}
	else {
		wattron(load_win, COLOR_PAIR(1));
		mvwprintw(load_win, y, x, "LOADING");
		wattroff(load_win, COLOR_PAIR(1));
		int t = x + 7;
		wattron(load_win, COLOR_PAIR(2));
		mvwprintw(load_win, y, t, "...");
		wattroff(load_win, COLOR_PAIR(2));
	}
}

void loading2(int row, int col) {
	WINDOW *load_win;

	int c, y, x;
	initscr();
	clear();
	noecho();
	cbreak();
	curs_set(0);
	start_color();

	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);

	load_win = newwin(row, col, 0, 0);
	box(load_win, 0, 0);

	y = row / 2 - 3;
	x = col / 2 - 5;

	int y1 = y + 2, y2 = y1 + 1;
	int x1 = x - 59/2, x2 = x1 + 59;
	
	wattron(load_win, COLOR_PAIR(2));
	mvwprintw(load_win, y2, x2, "*");
	wattroff(load_win, COLOR_PAIR(2));
	wrefresh(load_win);
	
	for (int j = 0; j < 47; j++) {
		loading2_part2(load_win, j, x, y);
		wattron(load_win, COLOR_PAIR(1));
		mvwprintw(load_win, y1, x1, "           oo");
		mvwprintw(load_win, y2, x1, ". __/\\_/\\_/`'");
		wattron(load_win, COLOR_PAIR(1));
		wattron(load_win, COLOR_PAIR(2));
		mvwprintw(load_win, y2, x1, ".");
		wattroff(load_win, COLOR_PAIR(2));
		wrefresh(load_win);
		x1++;
		for (int i = 0; i < 40000000; i++);
	}
		

	wrefresh(load_win);


	


	/*
				   oo
	. . . __/\_/\_/`'
	*/
}