#ifndef _setup_h_
#define _setup_h_
#define SPECIAL 100
#define MAX 3
typedef enum { FREE, SNAKE, OBSTACLE, FRUIT } Object;
//Part of snake.
typedef struct element {
	int column, row;
	struct element * next;
}Element;
//Pointer on part of snake.
typedef Element * Pointer;
//Position of fruit.
typedef struct {
	int fruit_row, fruit_column;
} Fruit;
//Information about the snake position.
typedef struct {
	Pointer head, tail;
} Header;
void diagonal_corners1(short ** board, int m, int n);
void diagonal_corners2(short ** board, int m, int n);
void col_with_holes(short **board, int m, int n);
void first_and_last_row(short **board, int m, int n);
void one_line(short **board, int m, int n);
void first_and_last_column(short **board, int m, int n);
void fisrt_row(short **board, int m, int n);
void column_with_hole(short **board, int m, int n);
void row_with_holes(short **board, int m, int n);
void half_col_down(short **board, int m, int n);
void half_row_with_hole(short **board, int m, int n);
void half_col_up(short **board, int m, int n);
void half_row_left(short **board, int m, int n);
void half_row_right_up(short **board, int m, int n);
void firs_row_in_the_middle(short **board, int m, int n);
void row_with_holes_down_middle(short **board, int m, int n);
void row_down_middle(short **board, int m, int n);
void row_with_hole_in_middle(short **board, int m, int n);
void first_col_with_hole(short ** board, int m, int n);
void last_row_with_hole(short**board, int m, int n);
void last_col_with_hole(short **board, int m, int n);
void first_row_with_hole(short **board, int m, int n);
void stairs(short **board, int m, int n);
void square_in_the_middle(short **board, int m, int n);
void square_left_up(short **board, int m, int n);
void square_right_up(short **board, int m, int n);
void square_right_down(short **board, int m, int n);
void square_left_down(short **board, int m, int n);
void zik_zak_left(short **board, int m, int n);
void angle_center(short **, int, int n);
//Coordinate axis.
void coordinate_axis(short **, int, int);
//Wall around the map.
void down_tree_part(short **, int, int);
void spiral(short **, int, int);
//Two lines in center of map.
void two_lines(short **, int, int);
//No obstacles.
void wuthout_obstacles(short **, int, int);
void messy(short **, int, int n);
//Set obstacles.
int set_obstacles(short **, int, int, int);
_Bool center(int l, int j);
//Types of Obstacles.
//Choose random obstacles.
void random_obstacles(short ** board, int m, int n, Header *header);
//Make fruit for score.
Fruit generate_fruit(short **, int, int);
void set_snake(short ** board, int m, int n, Header *);
//Check if there is empty position on map.
int empty_position(short **, int, int);
//Types of obsacles.
// Set game map.
short ** set_game(int, int, Header *, Fruit *);
//Delete list.
void delete_list(Header *);
//Delete matrix.
void delete_matrix(short *** board, int m, int n);
#endif
