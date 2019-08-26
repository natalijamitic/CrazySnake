#include "preparation.h"
#include "Demo.h"

void prepare(Options *options, int *row, int *col) {
	// Handle to write to the console.
	HANDLE wHnd;
	HANDLE rHnd;
	initscr();
	refresh();
	getmaxyx(stdscr, *row, *col);
	if (*row < 30 || *col < 120) {
		*row = 30;
		*col = 120;
		resize_term(30, 120);

	}
	int m, n;
	m = *row - 2;
	n = *col - 22;
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleTitle("CRAZY SNAKE");
	SMALL_RECT windowSize = { 0, 0, *col, *row };
	SetConsoleWindowInfo(wHnd, 1, &windowSize);
	load_options(options);
	loading2(*row, *col);
	if (options->music == ON)
		PlaySound(TEXT("IdeZmija.wav"), GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC | SND_LOOP);
	else
		PlaySound(NULL, NULL, SND_ASYNC);

}

void new_game(Options options, Options *saved_options) {
	int	 score, stop = 0;
	int len, total = 0;
	short **board = NULL;
	Fruit fruit;
	Header header;
	Move initialmove, currentmove;
	score = 0, stop = 0;
	initialmove = STOPR;
	currentmove = RIGHT;
	board = set_game(options.size.row, options.size.col, &header, &fruit);
	wclear(stdscr);
	wrefresh(stdscr);
	len = shortest_path_length(board, header, fruit, options.size.row, options.size.col);
	stop = gameplay(board, &header, &fruit, &options, &initialmove, &currentmove, &score, &len, &total);
	save_stop(stop);
	wclear(stdscr);
	wrefresh(stdscr);
	wclear(stdscr);
	wrefresh(stdscr);
	*saved_options = options;
	delete_list(&header);
	delete_matrix(&board, options.size.row, options.size.col);
}

void continue_game() {
	Fruit fruit;
	Header header;
	Options saved_options;
	Move initialmove, currentmove;
	int stop = load_stop(), score;
	int len, total;

	if (stop != ALIVE) {
		print_continue();
		return;
	}
	short **board = loadgame(&saved_options, &initialmove, &currentmove, &score, &header, &fruit, &len, &total);
	wclear(stdscr);
	wrefresh(stdscr);
	stop = gameplay(board, &header, &fruit, &saved_options, &initialmove, &currentmove, &score, &len, &total);
	save_stop(stop);
	wclear(stdscr);
	wrefresh(stdscr);
	delete_list(&header);
	delete_matrix(&board, saved_options.size.row, saved_options.size.col);
}

void demo_game(Options options) {
	Fruit fruit;
	Header header;
	short **board;
	int score = 0;

	board = set_game(options.size.row, options.size.col, &header, &fruit);
	wclear(stdscr);
	wrefresh(stdscr);
	demo(board, &header, &fruit, &score, &options);
	delete_list(&header);
	delete_matrix(&board, options.size.row, options.size.row);

}