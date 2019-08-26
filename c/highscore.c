#include <stdio.h>
#include <string.h>
#include <curses.h>
#include "options.h"

void print_Highscore_underline(int placetounderline) {
	FILE *file_pointer = fopen("Highscore.txt", "r");
	int place, score;
	char player[21];
	char xor = 255;
	int row, col, y, x, c;
	getmaxyx(stdscr, row, col);
	WINDOW *score_win;
	score_win = newwin(row, col, 0, 0);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);

	y = 1; x = col / 2 - 6;
	WINDOW *box0_win;
	box0_win = newwin(3, 12, y, x);
	box(box0_win, 0, 0);
	wbkgd(box0_win, COLOR_PAIR(2));
	wattron(box0_win, A_BOLD | A_UNDERLINE | COLOR_PAIR(1));
	mvwprintw(box0_win, 1, 3, "TOP 10");
	wattroff(box0_win, A_BOLD | A_UNDERLINE | COLOR_PAIR(1));
	wrefresh(score_win);
	wrefresh(box0_win);

	x = col - 35;
	y = row - 2;
	mvwprintw(score_win, y, x, "Press ESC for menu page");
	wrefresh(score_win);

	y = 5, x = col / 3;
	wattron(score_win, A_BOLD | COLOR_PAIR(2));
	mvwprintw(score_win, y, x, "RANK");
	x += 15; int t = x;
	x = col / 2 - 2;
	mvwprintw(score_win, y, x, "NAME");
	x = t + 30;
	mvwprintw(score_win, y, x, "SCORE");
	wattroff(score_win, A_BOLD | COLOR_PAIR(2));
	wrefresh(score_win);

	y = 7; x = col / 3; t = 1;

	while (fscanf(file_pointer, "%d.%d/%20s%*c", &place, &score, player) != EOF)
	{
		place ^= xor;
		score ^= xor;
		for (int i = 0; i < strlen(player); i++)
			player[i] ^= xor;

		if (place == placetounderline)
			wattron(score_win, A_BOLD | A_UNDERLINE | COLOR_PAIR(1));
		mvwprintw(score_win, y, x, "%d.", place);
		mvwprintw(score_win, y, x + 15, player);
		mvwprintw(score_win, y, x + 45, "%d", score);
		wrefresh(score_win);
		if (place == placetounderline)
			wattroff(score_win, A_BOLD | A_UNDERLINE | COLOR_PAIR(1));
		y += 2;
		//printw("%d.  %d  %s\n", place, score, player);
		//refresh();
	}

	c = wgetch(score_win);
	while (!(c == K_ESC || c == ENTER)) {
		c = wgetch(score_win);
	}
	if (c == K_ESC || c == ENTER)
		return;

}

void print_Highscore()
{
	FILE *file_pointer = fopen("Highscore.txt", "r");
	int place, score;
	char player[21];
	char xor = 255;
	int row, col, y, x, c;
	getmaxyx(stdscr, row, col);
	WINDOW *score_win;
	score_win = newwin(row, col, 0, 0);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);

	y = 1; x = col / 2 - 6;
	WINDOW *box0_win;
	box0_win = newwin(3, 12, y, x);
	box(box0_win, 0, 0);
	wbkgd(box0_win, COLOR_PAIR(2));
	wattron(box0_win, A_BOLD | A_UNDERLINE | COLOR_PAIR(1));
	mvwprintw(box0_win, 1, 3, "TOP 10");
	wattroff(box0_win, A_BOLD | A_UNDERLINE | COLOR_PAIR(1));
	wrefresh(score_win);
	wrefresh(box0_win);

	x = col - 35;
	y = row - 2;
	mvwprintw(score_win, y, x, "Press ESC for menu page");
	wrefresh(score_win);

	y = 5, x = col / 3;
	wattron(score_win, A_BOLD | COLOR_PAIR(2));
	mvwprintw(score_win, y, x, "RANK");
	x += 15; int t = x;
	x = col / 2 - 2;
	mvwprintw(score_win, y, x, "NAME");
	x = t + 30;
	mvwprintw(score_win, y, x, "SCORE");
	wattroff(score_win, A_BOLD | COLOR_PAIR(2));
	wrefresh(score_win);

	y = 7; x = col / 3; t = 1;

	while (fscanf(file_pointer, "%d.%d/%20s%*c", &place, &score, player) != EOF)
	{
		place ^= xor;
		score ^= xor;
		for (int i = 0; i < strlen(player); i++)
			player[i] ^= xor;

		if (t == 1)
			wattron(score_win, A_BOLD | COLOR_PAIR(1));

		mvwprintw(score_win, y, x, "%d.", place);
		mvwprintw(score_win, y, x + 15, player);
		mvwprintw(score_win, y, x + 45, "%d", score);
		wrefresh(score_win);

		if (t == 1)
			wattroff(score_win, A_BOLD | COLOR_PAIR(1));
		y += 2;
		t++;
		//printw("%d.  %d  %s\n", place, score, player);
		//refresh();
	}

	c = wgetch(score_win);
	while (!(c == K_ESC || c == ENTER)) {
		c = wgetch(score_win);
	}
	if (c == K_ESC || c == ENTER)
		return;
}

void file_copy(FILE *file1, FILE *file2)
{
	char ch;
	while ((ch = fgetc(file2)) != EOF)
		fputc(ch, file1);
}
static void xor_file()
{
	FILE *file_pointer;
	FILE *temp_file;
	int place, old_score, scores_left, temp;
	char player[21], new_player[21];
	char xor = 255;

	file_pointer = fopen("Highscore.txt", "r");
	temp_file = fopen("Temp.txt", "w");

	while (1)
	{
		if (fscanf(file_pointer, "%d.%d/%20s%*c", &place, &old_score, player) == EOF) break;

		place ^= xor;
		old_score ^= xor;
		for (int i = 0; i < strlen(player); i++)
			player[i] ^= xor;

		fprintf(temp_file, "%d.%d/%s\n", place, old_score, player);
	}

	fclose(file_pointer);
	fclose(temp_file);

	file_pointer = fopen("Highscore.txt", "w");
	temp_file = fopen("Temp.txt", "r");

	file_copy(file_pointer, temp_file);

	fclose(file_pointer);
	fclose(temp_file);
}

int topTen(int new_score)
{
	int placetoreturn = 0;
	FILE *file_pointer;
	FILE *temp_file;
	int place, old_score, scores_left, temp;
	char player[21], new_player[21];
	char xor = 255;


	file_pointer = fopen("Highscore.txt", "r");
	temp_file = fopen("Temp.txt", "w");

	while (1)
	{
		if (fscanf(file_pointer, "%d.%d/%20s%*c", &place, &old_score, player) == EOF) break;

		place ^= xor;
		old_score ^= xor;
		for (int i = 0; i < strlen(player); i++)
			player[i] ^= xor;

		if (old_score < new_score) break;
		else
		{
			place ^= xor;
			old_score ^= xor;
			for (int i = 0; i < strlen(player); i++)
				player[i] ^= xor;

			fprintf(temp_file, "%d.%d/%s\n", place, old_score, player);
		}
	}

	if (!feof(file_pointer))
	{
		scores_left = 10 - place;

		WINDOW* highscore_win;
		int row, col, x, y, c;

		wclear(stdscr);
		wrefresh(stdscr);
		getmaxyx(stdscr, row, col);
		y = (row - 7) / 2 - 2; x = (col - 46) / 2;
		highscore_win = newwin(7, 46, y, x);
		box(highscore_win, 0, 0);
		init_pair(11, COLOR_GREEN, COLOR_BLACK);
		init_pair(22, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(33, COLOR_GREEN, COLOR_MAGENTA);
		
		bkgd(COLOR_PAIR(22));
		refresh();
		wbkgd(highscore_win, COLOR_PAIR(22));
		wattron(highscore_win, A_BOLD | COLOR_PAIR(11));
		mvwprintw(highscore_win, 2, 11, "You are in the Top 10.");
		mvwprintw(highscore_win, 4, 3, "Enter your name:");
		wattroff(highscore_win, A_BOLD | COLOR_PAIR(11));
		wrefresh(highscore_win);
		echo();
		move((row - 7) / 2 - 2 + 4, (col - 46) / 2 + 13 + 8);
		refresh();
		int check;
		check = scanw("%20s", new_player);	
		noecho();
		refresh();
		if (check < 1) {
			new_player[0] = 'N';
			new_player[1] = 'a';
			new_player[2] = 't';
			new_player[3] = 'a';
			new_player[4] = 'l';
			new_player[5] = 'i';
			new_player[6] = 'j';
			new_player[7] = 'a';
			new_player[8] = 0;
		}

		placetoreturn = place;
		place ^= xor;
		old_score ^= xor;
		new_score ^= xor;
		for (int i = 0; i < strlen(new_player); i++)
			new_player[i] ^= xor;
		for (int i = 0; i < strlen(player); i++)
			player[i] ^= xor;

		fprintf(temp_file, "%d.%d/%s\n", place, new_score, new_player);

		while (scores_left--)
		{
			temp = (place ^ xor)+1;
			temp ^= xor;

			fprintf(temp_file, "%d.%d/%s\n", temp, old_score, player);
			fscanf(file_pointer, "%d.%d/%20s%*c", &place, &old_score, player);
		}

		fclose(file_pointer);
		fclose(temp_file);

		file_pointer = fopen("Highscore.txt", "w");
		temp_file = fopen("Temp.txt", "r");

		file_copy(file_pointer, temp_file);
	}

	fclose(file_pointer);
	fclose(temp_file);
	return placetoreturn;
}
