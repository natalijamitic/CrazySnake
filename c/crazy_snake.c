#include <curses.h>
#include <stdio.h> 

void crazy_snake(int row, int col) {
	int x, y;
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	WINDOW *menuu_win;
	menuu_win = newwin(16, 70, row / 2 - 8, (col - 25)/2-35+25);
	x = 1;
	y = 0;

	wattron(menuu_win, COLOR_PAIR(1));
	mvwprintw(menuu_win, y, x,   "        _ _ _                           _ _ _              _	");
	wattroff(menuu_win, COLOR_PAIR(1));

	wattron(menuu_win, COLOR_PAIR(2));
	mvwprintw(menuu_win, ++y, x, "	/  _ _ |                        /  _ _ |           | |	");
	wattroff(menuu_win, COLOR_PAIR(2));

	wattron(menuu_win, COLOR_PAIR(1));
	mvwprintw(menuu_win, ++y, x, "	| |      _ _  __ _ _ _ _   _    | |_ _  _ __   __ _| | __ __ ");
	wattroff(menuu_win, COLOR_PAIR(1));
	
	wattron(menuu_win, COLOR_PAIR(2));
	mvwprintw(menuu_win, ++y, x, "	| |     / _ |/ _` | _  / | | |  \\_ _   \\ '_ \\ / _` | |/ / _ \\");
	wattroff(menuu_win, COLOR_PAIR(2));
	
	wattron(menuu_win, COLOR_PAIR(1));
	mvwprintw(menuu_win, ++y, x, "	| |_ _ | |  | (_| |/  /| |_| |   _ _ | | | | | (_| |   /  __/");
	wattroff(menuu_win, COLOR_PAIR(1));
	
	wattron(menuu_win, COLOR_PAIR(2));
	mvwprintw(menuu_win, ++y, x, "       \\_ _ _ |_|  \\__,_ / _ _\\_ _, |  |_ _ _ /_| |_|\\__,_|_|\\_\\___|");
	wattroff(menuu_win, COLOR_PAIR(2));

	wattron(menuu_win, COLOR_PAIR(1));
	mvwprintw(menuu_win, ++y, x, "	                           / |");
	wattroff(menuu_win, COLOR_PAIR(1));

	wattron(menuu_win, COLOR_PAIR(2));
	mvwprintw(menuu_win, ++y, x, "	                        |___ /");
	wattroff(menuu_win, COLOR_PAIR(2));
	y += 2;
	x += 13;



	wattron(menuu_win, COLOR_PAIR(1));
	mvwprintw(menuu_win, ++y, x, "                     .-=-.          .--.");
	mvwprintw(menuu_win, ++y, x, "         __        .'     '.       /  \" )");
	mvwprintw(menuu_win, ++y, x, " _     .'  '.     /   .-.   \\     /  .-'\\");
	mvwprintw(menuu_win, ++y, x, "( \\   / .-.  \\   /   /   \\   \\   /  /    ^");
	mvwprintw(menuu_win, ++y, x, " \\ `-` /   \\  `-'   /     \\   `-`  /");
	mvwprintw(menuu_win, ++y, x, "  `-.-`     '.____.'       `.____.'");
	wattroff(menuu_win, COLOR_PAIR(1));

	wattron(menuu_win, COLOR_PAIR(2));
	mvwprintw(menuu_win, y = 11, x += 38, "\"");
	mvwprintw(menuu_win, ++y, x += 2, "\\");
	mvwprintw(menuu_win, ++y, ++x, "^");
	wattroff(menuu_win, COLOR_PAIR(2));


	wrefresh(menuu_win);
//	wrefresh(menu_win);

	/*
	  "  _ _ _                           _ _ _              _	"
	  "	| _ _ |                         |  _ _ |           | |	"
	  "	| |      _ _  __ _ _ _ _   _    | |_ _  _ __   __ _| | __ __ "
	  "	| |     / _ |/ _` | _  / | | |  |_ _ _ | '_ \ / _` | |/ / _ \"
	  "	| |_ _ | |  | (_| |/  /| |_| |   _ _ | | | | | (_| |   /  __/"
	  " |_ _ _ |_|  \__,_ / _ _\_ _, |  |_ _ _ |_| |_|\__,_/_|\_\___|"
	  "	                           / |"
	  "	                       |___ /"
	  
	  
	  
	                      .-=-.          .--.
              __        .'     '.       /  " )
      _     .'  '.     /   .-.   \     /  .-'\
     ( \   / .-.  \   /   /   \   \   /  /    ^
      \ `-` /   \  `-'   /     \   `-`  /
       `-.-`     '.____.'       `.____.'

	  */

//	wrefresh(menu_win);




}