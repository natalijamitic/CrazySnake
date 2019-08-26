#include <curses.h>
#include <stdio.h> 
#include "options.h"
#include <synchapi.h>
#include "highscore.h"
#pragma comment(lib, "winmm.lib")
#include <windows.h>
#include "save_game.h"

char *choices2[] = {
	"GAME DURATION",
	"MAP SIZE",
	"SNAKE SPEED",
	"DELETE HIGHSCORES",
	"MUSIC",
	"BACK",
};
int n_choices2 = sizeof(choices2) / sizeof(char *);

char *snakespeed[] = {
	"SLOW",
	"NORMAL",
	"FAST",
	"BACK",
};
int speed_choices = sizeof(snakespeed) / sizeof(char *);

char *music[] = {
	"ON",
	"OFF",
	"BACK",
};
int music_choices = sizeof(music) / sizeof(char*);

char *duration[] = {
	"MIN:",
	"SEC:",
	"BACK",
};
int duration_choices = sizeof(duration) / sizeof(char*);

char *size[] = {
	"WIDTH:",
	"HEIGHT:",
	"BACK",
};
int size_choices = sizeof(size) / sizeof(char*);

void print_options(WINDOW *option_win, int highlight) {
	int x, y, i, row, col;
	getmaxyx(stdscr, row, col);
	x = ENTER;
	y = (row - 20) / 2;
	box(option_win, 0, 0);
	wrefresh(option_win);
	crazy_snake(row, col);
	for (i = 0; i < n_choices2; ++i) {
		if (highlight == i + 1) /* Highlight the present choice */ {
			start_color();
			init_pair(1, COLOR_GREEN, COLOR_MAGENTA);
			wattron(option_win, COLOR_PAIR(1) | A_BOLD);
			mvwprintw(option_win, y, x, "%s", choices2[i]);
			wattroff(option_win, COLOR_PAIR(1) | A_BOLD);
		}
		else
			mvwprintw(option_win, y, x, "%s", choices2[i]);
		y += 2;
	}
	wrefresh(option_win);
}

int open_options(void) {

	clear();
	refresh();
	WINDOW *option_win;

	int highlight = 1, choice = 0;
	int choose, row, col;


	getmaxyx(stdscr, row, col);
	option_win = newwin(row, col, 0, 0);
	keypad(option_win, TRUE);
	wrefresh(option_win);

	print_options(option_win, highlight);
	//crazy_snake(row, col);

	while (1) {
		choose = wgetch(option_win);
		switch (choose) {
		case KEY_UP:
			if (highlight == 1)
				highlight = n_choices2;
			else
				--highlight;
			break;
		case KEY_DOWN:
			if (highlight == n_choices2)
				highlight = 1;
			else
				++highlight;
			break;
		case ENTER:
			choice = highlight;
			break;
		case K_ESC:
			break;
		}
		if (choose == K_ESC)
			break;
		print_options(option_win, highlight);
		if (choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}

	if (choose == K_ESC)
		return BACK6;
	else return highlight;

}

void print_snake_speed(WINDOW *speed_win, int highlight, int underline) {
	int x, y, i, row, col;
	getmaxyx(stdscr, row, col);
	x = ENTER;
	y = (row - 20) / 2;
	box(speed_win, 0, 0);
	wrefresh(speed_win);
	crazy_snake(row, col);
	for (i = 0; i < speed_choices; ++i) {
		if (highlight == i + 1) /* Highlight the present choice */ {
			start_color();
			init_pair(1, COLOR_GREEN, COLOR_MAGENTA);
			wattron(speed_win, COLOR_PAIR(1) | A_BOLD);
			if (i == underline - 1)
				wattron(speed_win, A_UNDERLINE);
			mvwprintw(speed_win, y, x, "%s", snakespeed[i]);
			wattroff(speed_win, COLOR_PAIR(1) | A_BOLD);
			if (i == underline - 1)
				wattroff(speed_win, A_UNDERLINE);
		}
		else {
			if (i == underline - 1)
				wattron(speed_win, A_UNDERLINE);
			mvwprintw(speed_win, y, x, "%s", snakespeed[i]);
			if (i == underline - 1)
				wattroff(speed_win, A_UNDERLINE);
		}
		y += 2;
	}
	wrefresh(speed_win);
}

void snake_speed(Options *options) {
	clear();
	refresh();
	WINDOW *speed_win;
	int highlight = 1, choice = 0, choose = 0;
	int  row, col;

	getmaxyx(stdscr, row, col);
	speed_win = newwin(row, col, 0, 0);
	keypad(speed_win, TRUE);
	wrefresh(speed_win);

	int underline = options->mode;

	print_snake_speed(speed_win, highlight, underline);

	while (1) {
		choose = wgetch(speed_win);
		switch (choose) {
		case KEY_UP:
			if (highlight == 1)
				highlight = speed_choices;
			else
				--highlight;
			break;
		case KEY_DOWN:
			if (highlight == speed_choices)
				highlight = 1;
			else
				++highlight;
			break;
		case ENTER:
			choice = highlight;
			break;
		case K_ESC:
			break;
		}
		if (choose == K_ESC)
			break;
		print_snake_speed(speed_win, highlight, underline);
		if (choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}

	if (choose == K_ESC)
		return;

	switch (highlight) {
	case EASY:
		options->mode = EASY;
		save_options(options);
		return;
	case MEDIUM:
		options->mode = MEDIUM;
		save_options(options);
		return;
	case HARD:
		options->mode = HARD;
		save_options(options);
		return;
	case BACK4:
		return;
	}
}

void print_music(WINDOW *music_win, int highlight, int underline) {
	int x, y, i, row, col;
	getmaxyx(stdscr, row, col);
	x = 10;
	y = (row - 20) / 2;
	box(music_win, 0, 0);
	wrefresh(music_win);
	crazy_snake(row, col);
	for (i = 0; i < music_choices; ++i) {
		if (highlight == i + 1) /* Highlight the present choice */ {
			start_color();
			init_pair(1, COLOR_GREEN, COLOR_MAGENTA);
			wattron(music_win, COLOR_PAIR(1) | A_BOLD);
			if (i == underline - 1)
				wattron(music_win, A_UNDERLINE);
			mvwprintw(music_win, y, x, "%s", music[i]);
			wattroff(music_win, COLOR_PAIR(1) | A_BOLD);
			if (i == underline - 1)
				wattroff(music_win, A_UNDERLINE);

		}
		else {
			if (i == underline - 1)
				wattron(music_win, A_UNDERLINE);
			mvwprintw(music_win, y, x, "%s", music[i]);
			if (i == underline - 1)
				wattroff(music_win, A_UNDERLINE);
		}
		y += 2;
	}
	wrefresh(music_win);

}

void open_music(Options *options) {
	clear();
	refresh();
	WINDOW *music_win;

	int highlight = 1, choice = 0;
	int choose, row, col;

	getmaxyx(stdscr, row, col);
	music_win = newwin(row, col, 0, 0);
	keypad(music_win, TRUE);
	wrefresh(music_win);
	int underline = options->music;

	print_music(music_win, highlight, underline);

	while (1) {
		choose = wgetch(music_win);
		switch (choose) {
		case KEY_UP:
			if (highlight == 1)
				highlight = music_choices;
			else
				--highlight;
			break;
		case KEY_DOWN:
			if (highlight == music_choices)
				highlight = 1;
			else
				++highlight;
			break;
		case ENTER:
			choice = highlight;
			break;
		case K_ESC:
			break;
		}
		if (choose == K_ESC)
			break;
		print_music(music_win, highlight, underline);
		if (choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}

	if (choose == K_ESC)
		return;

	switch (highlight) {
	case ON:
		options->music = ON;
		PlaySound(TEXT("IdeZmija.wav"), GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC | SND_LOOP);
		save_options(options);
		return;
	case OFF:
		options->music = OFF;
		PlaySound(NULL, NULL, SND_ASYNC);
		save_options(options);
		return;
	case BACK3:
		return;
	}

}

void print_duration(WINDOW * duration_win, int highlight) {
	int x, y, i, row, col;
	getmaxyx(stdscr, row, col);
	x = 10;
	y = (row - 20) / 2;
	box(duration_win, 0, 0);
	wrefresh(duration_win);
	crazy_snake(row, col);
	mvwprintw(duration_win, row - 4, 5, "Press Enter to choose what you want to change. Type duration you want. Press Enter again.");
	mvwprintw(duration_win, row - 3, 5, "Minutes go from 0 to 99, seconds from 0 to 59.");
	wrefresh(duration_win);
	for (i = 0; i < duration_choices; ++i) {
		if (highlight == i + 1) /* Highlight the present choice */ {
			start_color();
			init_pair(1, COLOR_GREEN, COLOR_MAGENTA);
			wattron(duration_win, COLOR_PAIR(1) | A_BOLD);
			mvwprintw(duration_win, y, x, "%s", duration[i]);
			wattroff(duration_win, COLOR_PAIR(1) | A_BOLD);
		}
		else
			mvwprintw(duration_win, y, x, "%s", duration[i]);
		y += 2;
	}

	mvwprintw(duration_win, row - 4, 5, "Press Enter to choose what you want to change. Type duration you want. Press Enter again.");
	mvwprintw(duration_win, row - 3, 5, "Minutes go from 0 to 99, seconds from 0 to 59.");
	wrefresh(duration_win);

}

int game_duration(Options *options, WINDOW *duration_win) {

	int highlight = 1, choice = 0, choose;

	print_duration(duration_win, highlight);

	while (1) {
		choose = wgetch(duration_win);
		switch (choose) {
		case KEY_UP:
			if (highlight == 1)
				highlight = duration_choices;
			else
				--highlight;
			break;
		case KEY_DOWN:
			if (highlight == duration_choices)
				highlight = 1;
			else
				++highlight;
			break;
		case ENTER:
			choice = highlight;
			break;
		case K_ESC:
			break;
		}
		if (choose == K_ESC)
			break;
		print_duration(duration_win, highlight);
		if (choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}

	if (choose == K_ESC)
		return BACK3;

	return highlight;

}

void game_duration_choice(Options *options) {
	int option;
	double min, sec;
	clear();
	refresh();
	WINDOW *duration_win;
	int choose, row, col, br = 1;

	getmaxyx(stdscr, row, col);
	duration_win = newwin(row, col, 0, 0);
	keypad(duration_win, TRUE);
	wrefresh(duration_win);

	min = options->minutes;
	sec = options->seconds;

	mvwprintw(duration_win, (row - 20) / 2, 15, "%.0f   ", min);
	mvwprintw(duration_win, (row - 20) / 2 + 2, 15, "%.0f   ", sec);
	wrefresh(duration_win);


	while (1) {
		option = game_duration(options, duration_win);
		noecho();
		switch (option) {
		case MINUTES:
			echo();
			mvwprintw(duration_win, (row - 20) / 2, 15, "  ");
			wrefresh(duration_win);
			mvprintw((row - 20) / 2, 15, "  ");
			refresh();
			move((row - 20) / 2, 15);
			refresh();
			scanw("%lf", &min);
			if (min > 99)
				min = 99;
			if (min < 0)
				min = 0;
			if (min == 0 && sec == 0) {
				sec = 1;
				mvwprintw(duration_win, (row - 20) / 2 + 2, 15, "%.0f           ", sec);
				options->seconds = sec;
				wrefresh(duration_win);

			}
			mvwprintw(duration_win, (row - 20) / 2, 15, "%.0f           ", min);
			wrefresh(duration_win);
			options->minutes = min;
			noecho();
			save_options(options);
			break;
		case SECONDS:
			echo();
			mvwprintw(duration_win, (row - 20) / 2 + 2, 15, "  ");
			wrefresh(duration_win);
			mvprintw((row - 20) / 2 + 2, 15, "  ");
			refresh();
			move((row - 20) / 2 + 2, 15);
			refresh();
			scanw("%lf", &sec);
			if (sec > 59)
				sec = 59;
			if (sec < 0)
				sec = 0;
			if (min == 0 && sec == 0)
				sec = 1;
			mvwprintw(duration_win, (row - 20) / 2 + 2, 15, "%.0f          ", sec);
			options->seconds = sec;
			wrefresh(duration_win);
			noecho();
			save_options(options);
			break;
		case BACK3:
			noecho();
			return;
		}
	}

}

void print_size(WINDOW * size_win, int highlight) {
	int x, y, i, row, col;
	getmaxyx(stdscr, row, col);
	x = 10;
	y = (row - 20) / 2;
	box(size_win, 0, 0);
	wrefresh(size_win);
	crazy_snake(row, col);
	mvwprintw(size_win, row - 4, 5, "Press Enter to choose what you want to change. Type size you want. Press Enter again.");
	mvwprintw(size_win, row - 3, 5, "Width goes from 20 to %d lines, height from 20 to %d.", col - 22, row - 2);
	wrefresh(size_win);
	for (i = 0; i < size_choices; ++i) {
		if (highlight == i + 1) /* Highlight the present choice */ {
			start_color();
			init_pair(1, COLOR_GREEN, COLOR_MAGENTA);
			wattron(size_win, COLOR_PAIR(1) | A_BOLD);
			mvwprintw(size_win, y, x, "%s", size[i]);
			wattroff(size_win, COLOR_PAIR(1) | A_BOLD);
		}
		else
			mvwprintw(size_win, y, x, "%s", size[i]);
		y += 2;
	}

	mvwprintw(size_win, row - 4, 5, "Press Enter to choose what you want to change. Type size you want. Press Enter again.");
	mvwprintw(size_win, row - 3, 5, "Width goes from 20 to %d lines, height from 20 to %d.", col - 22, row - 2);
	wrefresh(size_win);

}

int game_size(Options *options, WINDOW *size_win) {

	int highlight = 1, choice = 0, choose;

	print_size(size_win, highlight);

	while (TRUE) {
		choose = wgetch(size_win);
		switch (choose) {
		case KEY_UP:
			if (highlight == 1)
				highlight = size_choices;
			else
				--highlight;
			break;
		case KEY_DOWN:
			if (highlight == size_choices)
				highlight = 1;
			else
				++highlight;
			break;
		case ENTER:
			choice = highlight;
			break;
		case K_ESC:
			break;
		}
		if (choose == K_ESC)
			break;
		print_size(size_win, highlight);
		if (choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}

	if (choose == K_ESC)
		return BACK3;

	return highlight;

}

void game_size_choice(Options *options) {
	int option;
	int rowsize, colsize;
	clear();
	refresh();
	WINDOW *size_win;
	int choose, row, col, br = 1;

	getmaxyx(stdscr, row, col);
	size_win = newwin(row, col, 0, 0);
	keypad(size_win, TRUE);
	wrefresh(size_win);

	rowsize = options->size.row;
	colsize = options->size.col;

	mvwprintw(size_win, (row - 20) / 2, 20, "%d   ", colsize);
	mvwprintw(size_win, (row - 20) / 2 + 2, 20, "%d   ", rowsize);
	wrefresh(size_win);

	while (TRUE) {
		option = game_size(options, size_win);
		noecho();
		switch (option) {
		case ROW_SIZE:
			echo();
			mvwprintw(size_win, (row - 20) / 2, 20, "   ");
			wrefresh(size_win);
			mvprintw((row - 20) / 2, 20, "   ");
			refresh();
			move((row - 20) / 2, 20);
			refresh();
			scanw("%d", &colsize);
			if (colsize > col - 22)
				colsize = col - 22;
			if (colsize < 20)
				colsize = 20;
			mvwprintw(size_win, (row - 20) / 2, 20, "%d   ", colsize);
			wrefresh(size_win);
			options->size.col = colsize;
			noecho();
			save_options(options);
			break;
		case COLUMN_SIZE:
			echo();
			mvwprintw(size_win, (row - 20) / 2 + 2, 20, "   ");
			wrefresh(size_win);
			mvprintw((row - 20) / 2 + 2, 20, "   ");
			refresh();
			move((row - 20) / 2 + 2, 20);
			refresh();
			scanw("%d", &rowsize);
			if (rowsize > row - 2)
				rowsize = row - 2;
			if (rowsize < 20)
				rowsize = 20;
			mvwprintw(size_win, (row - 20) / 2 + 2, 20, "%d   ", rowsize);
			options->size.row = rowsize;
			wrefresh(size_win);
			noecho();
			save_options(options);
			break;
		case BACK3:
			noecho();
			return;
		}
	}

}

void delete_top10() {
	WINDOW *delete_win;
	int row, col, choose, y, x;
	wclear(stdscr);
	wrefresh(stdscr);

	FILE *blank_file;
	FILE *score_file;
	blank_file = fopen("Blank.txt", "r");
	score_file = fopen("Highscore.txt", "w");
	file_copy(score_file, blank_file);
	fclose(blank_file);
	fclose(score_file);
	init_pair(111, COLOR_GREEN, COLOR_BLACK);
	init_pair(222, COLOR_MAGENTA, COLOR_BLACK);

	getmaxyx(stdscr, row, col);
	y = (row - 7) / 2 - 2; x = (col - 46) / 2;
	delete_win = newwin(5, 46, y, x);
	box(delete_win, 0, 0);
	keypad(delete_win, TRUE);
	wbkgd(delete_win, COLOR_PAIR(222));
	wattron(delete_win, A_BOLD | COLOR_PAIR(111));
	mvwprintw(delete_win, 2, 5, "Highscore list successfully deleted.");
	wattroff(delete_win, A_BOLD | COLOR_PAIR(111));
	wrefresh(delete_win);

	while (TRUE) {
		choose = wgetch(delete_win);
		switch (choose) {
		case K_ESC:
			return;
		case ENTER:
			return;
		}

	}

}

void makeoptionchoice(Options *options) {
	int option;

	while (TRUE) {
		option = open_options();

		switch (option) {
		case DURATION:
			game_duration_choice(options);
			break;
		case MAP_SIZE:
			game_size_choice(options);
			break;
		case SNAKE_SPEED:
			snake_speed(options);
			break;
		case CLEAR_HIGHSCORE:
			delete_top10();
			break;
		case MUSIC:
			open_music(options);
			break;
		case BACK6:
			return;
		}
	}
}