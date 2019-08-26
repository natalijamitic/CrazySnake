#include "save_game.h"


_Bool savegame(Options *option, Move initialmove, Move currentmove, short **board, int score, Header header, Fruit fruit, int len, int total) {
	FILE *file;
	file = fopen("map.txt", "w");
	if (board == NULL)
		return 0;
	fprintf(file, "%d %d\n", option->size.row, option->size.col);
	for (int i = 0; i < option->size.row; i++) {
		for (int j = 0; j < option->size.col; j++) {
			fprintf(file, "%d ", board[i][j]);
		}
		fprintf(file, "\n");
	}
	fprintf(file, "%d\n", initialmove);
	fprintf(file, "%d\n", currentmove);
	fprintf(file, "%d\n", score);
	fprintf(file, "%f : %f\n", option->minutes, option->seconds);
	fprintf(file, "%d %d \n", option->size.row, option->size.col);
	fprintf(file, "%d \n", option->mode);
	fprintf(file, "(%d,%d) \n", fruit.fruit_row, fruit.fruit_column);
	fprintf(file, "%d %d \n", len, total);
	Pointer temp = header.tail;
	while (temp) {
		fprintf(file, "(%d,%d) ", temp->row, temp->column);
		temp = temp->next;
	}
	fprintf(file, "(-1,-1) ");
	fclose(file);
	return 1;
}
void save_stop(int stop) {
	FILE *save;
	save = fopen("Is_dead.txt", "w");
	fprintf(save, "%d", stop);
	fclose(save);

}
short** loadgame(Options *option, Move* initialmove, Move *currentmove, int *score, Header *header, Fruit *fruit, int *len, int *total) {
	FILE *file = fopen("map.txt", "r");
	short **board = NULL;
	fscanf(file, "%d %d\n", &option->size.row, &option->size.col);
	board = malloc(option->size.row * sizeof(short*));
	if (board == NULL)
		exit(EXIT_FAILURE);
	for (int i = 0; i <option->size.row; i++) {
		board[i] = malloc(option->size.col * sizeof(short));
		if (board[i] == NULL)
			exit(EXIT_FAILURE);
		for (int j = 0; j <option->size.col; j++) {
			fscanf(file, "%hd ", &board[i][j]);
		}

		fscanf(file, "\n");
	}
	fscanf(file, "%d\n", initialmove);
	fscanf(file, "%d\n", currentmove);
	fscanf(file, "%d\n", score);
	fscanf(file, "%lf : %lf\n", &option->minutes, &option->seconds);
	fscanf(file, "%d %d \n", &option->size.row, &option->size.col);
	fscanf(file, "%d \n", &option->mode);
	fscanf(file, "(%d,%d) \n", &fruit->fruit_row, &fruit->fruit_column);
	fscanf(file, "%d %d \n", len, total);
	Pointer temp = malloc(sizeof(Element));
	if (!temp)
		exit(EXIT_FAILURE);
	int x, y;
	fscanf(file, "(%d,%d) ", &x, &y);
	temp->row = x;
	temp->column = y;
	temp->next = NULL;
	header->tail = temp;
	header->head = temp;
	fscanf(file, "(%d,%d) ", &x, &y);
	while (x != -1) {
		temp = malloc(sizeof(Element));
		if (!temp)
			exit(EXIT_FAILURE);
		temp->row = x;
		temp->column = y;
		temp->next = NULL;
		header->head->next = temp;
		header->head = temp;
		fscanf(file, "(%d,%d) ", &x, &y);
	}
	fclose(file);
	return board;
}
int load_stop(void) {
	FILE *save;
	int stop;
	save = fopen("Is_dead.txt", "r");
	fscanf(save, "%d", &stop);
	fclose(save);
	return stop;
}

void save_options(Options *options) {
	FILE *game_options;
	game_options = fopen("options.txt", "w");
	fprintf(game_options, "%d %d\n", options->size.row, options->size.col);
	fprintf(game_options, "%d %d\n", options->mode, options->music);
	fprintf(game_options, "%lf : %lf\n", options->minutes, options->seconds);
	fclose(game_options);

}
void load_options(Options *options) {
	FILE *game_options;
	game_options = fopen("options.txt", "r");
	fscanf(game_options, "%d %d\n", &options->size.row, &options->size.col);
	fscanf(game_options, "%d %d\n", &options->mode, &options->music);
	fscanf(game_options, "%lf : %lf\n", &options->minutes, &options->seconds);
	fclose(game_options);

}