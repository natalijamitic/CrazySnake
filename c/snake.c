#include "preparation.h"

int main() {
	srand(time(NULL));
	int option = NEW_GAME, optionchoice = 0;
	int row, col;
	DWORD dwWidth = GetSystemMetrics(SM_CXSCREEN);
	DWORD dwHeight = GetSystemMetrics(SM_CYSCREEN);
	Options options, saved_options;
	prepare(&options, &row, &col);
	while (!QUIT) {
		option = open_menu(row, col);
		switch (option) {
		case NEW_GAME:
			//load_options(&options);
			new_game(options, &saved_options);
			break;
		case CONTINUE:
			continue_game();
			break;
		case DEMO:
			//load_options(&options);
			demo_game(options);
			break;
		case HIGHSCORE:
			print_Highscore();
			break;
		case OPTIONS:
			//load_options(&options);
			makeoptionchoice(&options);
			save_options(&options);
			break;
		case HELP:
			open_help();
			break;
		case ABOUT:
			open_about(); 
		case AUTHORS:
			open_authors();
			break;
		case EXIT:
			open_exit();
			break;

		}
	}
	refresh();
	getch();
	endwin();
	return 0;

}
