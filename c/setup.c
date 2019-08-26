#include <stdio.h>
#include <stdlib.h> 
#include "setup.h"
#include <time.h>	
#include "gameplay.h"
#define OBSTACLES_TYPES 31
//Center of line.
_Bool center(int l, int j) {
	if (l != j / 2 - 2 && l != j / 2 - 1 && l != j / 2 && l != j / 2 + 1 && l != j / 2 + 2)
		return 0;
	else
		return 1;

}
//Types of obstacles.
void diagonal_corners1(short ** board, int m, int n) {
	int start_r, start_c;
	int size_r = (m > 10 ? 4 : m <= 4 ? 0 : 2);
	int size_c = (n > 10 ? 8 : n <= 4 ? 0 : 1);
	//UP-LEFT CORNER

	for (start_r = 0, start_c = 0; start_c < size_c; board[start_r][start_c++] = OBSTACLE);
	for (start_r = 0, start_c = 0; start_r < size_r; board[start_r][start_c] = OBSTACLE, board[start_r++][start_c + 1] = OBSTACLE);

	//DOWN-RIGHT CORNER
	for (start_r = m - 1, start_c = n - 1; start_c > n - 1 - size_c; board[start_r][start_c--] = OBSTACLE);
	for (start_r = m - 1, start_c = n - 1; start_r > m - 1 - size_r; board[start_r][start_c] = OBSTACLE, board[start_r--][start_c - 1] = OBSTACLE);
}
void two_lines(short ** board, int m, int n) {
	int start_r, start_c;
	start_r = m / 3;
	start_c = n / 20;
	for (int l = 1; l < 2 * n / 3 && start_c<n - 3; l++) {
		l % 2 != 0 ? board[start_r][start_c] = OBSTACLE, board[start_r][start_c + 1] = OBSTACLE : 0;
		if (start_c >= n - 3)
			start_c %= n;
		else
			start_c += 2;
	}
	start_r = 2 * m / 3;
	start_c = n / 20;
	for (int l = 1; l < 2 * n / 3 && start_c<n - 2; l++) {
		l % 2 != 0 ? board[start_r][start_c] = OBSTACLE, board[start_r][start_c + 1] = OBSTACLE : 0;
		if (start_c >= n - 3)
			start_c %= n;
		else
			start_c += 2;
	}
	return;
}
void diagonal_corners2(short ** board, int m, int n) {
	int start_r, start_c;
	int size_r = (m > 10 ? 4 : m <= 4 ? 0 : 2);
	int size_c = (n > 10 ? 8 : n <= 4 ? 0 : 1);
	//DOWN-LEFT CORNER
	for (start_r = m - 1, start_c = 0; start_c < size_c; board[start_r][start_c++] = OBSTACLE);
	for (start_r = m - 1, start_c = 0; start_r > m - 1 - size_r; board[start_r][start_c] = OBSTACLE, board[start_r--][start_c + 1] = OBSTACLE);
	//UP-RIGHT CORNER
	for (start_r = 0, start_c = n - 1; start_c > n - 1 - size_c; board[start_r][start_c--] = OBSTACLE);
	for (start_r = 0, start_c = n - 1; start_r < size_r; board[start_r][start_c] = OBSTACLE, board[start_r++][start_c - 1] = OBSTACLE);
}
void col_with_holes(short **board, int m, int n) {
	//One column with empty spaces between obstacles.
	int start_r = 2 * m / 3;
	int start_c = n / 4;
	for (int l = 1; l < 2 * m / 3; l++) { l % 2 != 0 ? board[start_r][start_c] = OBSTACLE, board[start_r][start_c + 1 > n - 1 ? start_c : start_c + 1] = OBSTACLE : 0;	++start_r == m ? start_r = 0 : start_r; }

}
void first_and_last_row(short **board, int m, int n) {
	int  start_r = 0;
	for (int start_c = 1; start_c < n - 3; start_c++) {
		if (start_c % 2 == 0) {
			board[start_r][start_c] = OBSTACLE;
			board[start_r][start_c + 1] = OBSTACLE;
			board[m - 1][start_c] = OBSTACLE;
			board[m - 1][start_c + 1] = OBSTACLE;
			start_c += 2;
		}
	}
}
void one_line(short **board, int m, int n) {
	int start_r = m / 3;
	int start_c = n / 4;
	int j = n / 2;
	for (int l = 1; l < j; l++) { if (!center(l, j)) board[start_r][start_c] = OBSTACLE;	++start_c == n ? start_c = 0 : start_c; }

}
void first_and_last_column(short **board, int m, int n) {
	//First and last column.
	int start_c = 0;
	for (int start_r = 3; start_r < m - 3; start_r++) {
		board[start_r][start_c] = OBSTACLE;
		board[start_r][start_c + 1] = OBSTACLE;
		board[start_r][n - 1] = OBSTACLE;
		board[start_r][n - 2] = OBSTACLE;
	}
}
void fisrt_row(short **board, int m, int n) {
	//First row.
	for (int start_c = 0, start_r = 0; start_c < n; board[start_r][start_c++] = OBSTACLE);
}
void column_with_hole(short **board, int m, int n) {
	int start_c = 3 * n / 4, start_r;
	for (start_r = 0; start_r < m; start_r++)
		if (!center(start_r, m))
			board[start_r][start_c] = OBSTACLE;
	start_c = 3 * n / 4 + 1;
	if (start_c > n - 1)
		return;
	for (start_r = 0; start_r < m; start_r++)
		if (!center(start_r, m))
			board[start_r][start_c] = OBSTACLE;
}
void row_with_holes(short **board, int m, int n) {
	int start_r = m / 3, start_c = n / 5;
	for (int l = 1; l < 2 * n / 3; l++) {
		l % 2 != 0 ? board[start_r][start_c] = OBSTACLE, board[start_r][start_c + 1 > n - 1 ? start_c = 0 : start_c + 1] = OBSTACLE : 0;
		if (start_c + 2 > n - 3)
			start_c = 0;
		else start_c += 2;
		l += 2;
	}
}
void half_col_down(short **board, int m, int n) {
	int start_r = m / 2, start_c;
	for (start_c = n / 3; start_r < m; board[start_r++][start_c] = OBSTACLE);
	start_c = n / 3 + 1;
	start_r = m / 2;
	if (start_c > n - 1)
		return;
	for (; start_r < m; board[start_r++][start_c] = OBSTACLE);
}
void half_row_with_hole(short **board, int m, int n) {
	int start_c = n / 2;
	for (int start_r = 2 * m / 3; start_c < n; start_c++)
		if (!center(start_c, 3 * n / 2)) board[start_r][start_c] = OBSTACLE;
}
void half_col_up(short **board, int m, int n) {
	int start_c = 4 * n / 10;
	for (int start_r = 0; start_r <= 4 * m / 9; board[start_r][start_c] = OBSTACLE, board[start_r++][start_c + 1] = OBSTACLE);
}
void half_row_left(short **board, int m, int n) {
	int start_r = 2 * m / 3;
	for (int start_c = 0; start_c <= n / 2 - 2; board[start_r][start_c++] = OBSTACLE);
}
void half_row_right_up(short **board, int m, int n) {
	int start_r = m / 3;
	for (int start_c = n - 1; start_c >= n / 2 + 2; board[start_r][start_c--] = OBSTACLE);
}
void firs_row_in_the_middle(short **board, int m, int n) {
	int start_r = 0;
	int end_c = 7 * n / 12;
	for (int start_c = 4 * n / 12; start_c < end_c; board[start_r][start_c++] = OBSTACLE);
}
void row_with_holes_down_middle(short **board, int m, int n) {
	int start_r = 2 * m / 3, start_c = n / 5;
	for (int l = 1; l < 2 * n / 3; l++) {
		l % 2 != 0 ? board[start_r][start_c] = OBSTACLE, board[start_r][start_c + 1] = OBSTACLE : 0;
		if (start_c + 2 > n - 3)
			start_c = 0;
		else start_c += 2;
		l += 2;
	}
}
void row_down_middle(short **board, int m, int n) {
	int start_r = 2 * m / 3, start_c = n / 3;
	int j = n / 2;
	for (int l = 1; l < 3 * j / 4; l++) { board[start_r][start_c] = OBSTACLE;	++start_c == n ? start_c = 0 : start_c; }
}
void row_with_hole_in_middle(short **board, int m, int n) {
	int start_r = (m / 2 - 2) <= 0 ? 0 : m / 2 - 2;
	for (int start_c = 3; start_c < n - 3; start_c++) {
		if (!center(start_c, n))
			board[start_r][start_c] = OBSTACLE;
	}
}
void first_col_with_hole(short ** board, int m, int n) {
	int start_c = 0;
	for (int start_r = 3; start_r < m - 5; start_r++) {
		if (start_r != m / 2 && start_r != m / 2 - 1 && start_r != m / 2 + 1) {
			board[start_r][start_c] = OBSTACLE;
			board[start_r][start_c + 1] = OBSTACLE;
		}
	}
}
void last_row_with_hole(short**board, int m, int n) {
	int start_c;
	for (start_c = 3; start_c < n - 5; start_c++) {
		if (start_c != n / 2 && start_c != n / 2 - 1 && start_c != n / 2 + 1) {
			board[m - 1][start_c] = OBSTACLE;
		}
	}
}
void last_col_with_hole(short **board, int m, int n) {
	for (int start_r = 3; start_r < m - 5; start_r++) {
		if (start_r != m / 2 && start_r != m / 2 - 1 && start_r != m / 2 + 1) {
			board[start_r][n - 1] = OBSTACLE;
			board[start_r][n - 2] = OBSTACLE;
		}
	}
}
void first_row_with_hole(short **board, int m, int n) {
	int start_r = 0;
	for (int start_c = 3; start_c < n - 5; start_c++) {
		if (start_c != n / 2 && start_c != n / 2 - 1 && start_c != n / 2 + 1) {
			board[start_r][start_c] = OBSTACLE;

		}
	}
}
void stairs(short **board, int m, int n) {
	int start_r = m / 2, start_c;
	for (start_c = n / 10; start_r < m - 4 && start_c < n - 4; board[start_r][start_c] = OBSTACLE, board[start_r][start_c++] = OBSTACLE, board[start_r++][start_c++] = OBSTACLE);
	for (int l = n / 4; start_r < m - 1 && l>0 && start_c < n - 2; board[start_r][start_c] = OBSTACLE, board[start_r][++start_c] = OBSTACLE, l--);
	--start_r; start_c++;
	for (; start_r >= m / 2 && start_c < n - 1; board[start_r][start_c] = OBSTACLE, board[start_r--][++start_c] = OBSTACLE, start_c++ > n - 3 ? start_c = 0 : 1);

}
void square_in_the_middle(short **board, int m, int n) {
	int start_r = m / 2, start_c = n / 2;
	for (int i = m / 10; i > 0; i--) {
		for (int k = n / 10; k > 0; k--)
		{
			board[(start_r + m / 20 - i) % m][(start_c + n / 20 - k) % n] = OBSTACLE;
		}
	}
}
void square_left_up(short **board, int m, int n) {
	int start_r = m / 6, start_c = n / 6;
	for (int i = m / 11; i > 0; i--) {
		for (int k = n / 11; k > 0; k--)
		{
			board[(start_r + m / 20 - i) % m][(start_c + n / 20 - k) % n] = OBSTACLE;
		}
	}
}
void square_right_up(short **board, int m, int n) {
	int start_r = m / 6, start_c = 6 * n / 7;
	for (int i = m / 10; i > 0; i--) {
		for (int k = n / 10; k > 0; k--)
		{
			board[(start_r + m / 20 - i) % m][(start_c + n / 20 - k) % n] = OBSTACLE;
		}
	}
}
void square_right_down(short **board, int m, int n) {
	int 	start_r = 6 * m / 7, start_c = 6 * n / 7;
	for (int i = m / 10; i > 0; i--) {
		for (int k = n / 10; k > 0; k--)
		{
			board[(start_r + m / 20 - i) % m][(start_c + n / 20 - k) % n] = OBSTACLE;
		}
	}
}
void square_left_down(short **board, int m, int n) {
	int start_r = 6 * m / 7, start_c = n / 7;
	for (int i = m / 10; i > 0; i--) {
		for (int k = n / 10; k > 0; k--)
		{
			board[(start_r + m / 20 - i) % m][(start_c + n / 20 - k) % n] = OBSTACLE;
		}
	}
}
void zik_zak_left(short **board, int m, int n) {
	int start_r = 5, start_c = n - 3;
	for (; start_c>4 && start_r<m - 4; board[start_r][--start_c] = OBSTACLE, board[start_r++][--start_c] = OBSTACLE);
}
void zik_zak_right(short **board, int m, int n) {
	int start_r = 3 * m / 4;
	for (int start_c = 4 * n / 5; start_r > 2 && start_c > 2; board[start_r][--start_c] = OBSTACLE, board[start_r--][--start_c] = OBSTACLE);
}
//Different maps.
void angle_center(short ** board, int m, int n) {
	two_lines(board, m, n);
	diagonal_corners1(board, m, n);
	diagonal_corners2(board, m, n);
	return;
}
void coordinate_axis(short ** board, int m, int n) {
	int start_r, start_c;
	start_r = m / 2;
	for (start_c = 0; start_c < n; board[start_r][start_c++] = OBSTACLE);
	start_c = n / 2;
	for (start_r = 0; start_r < m; board[start_r][start_c] = OBSTACLE, board[start_r++][start_c + 1] = OBSTACLE);
	return;
}
void down_tree_part(short ** board, int m, int n) {
	int start_r, start_c;
	start_r = m / 2;
	start_c = 0;
	//Middle row.
	for (int start_c = 0; start_c < n; board[start_r][start_c++] = OBSTACLE);
	//Two column.
	for (start_c = n / 3; start_r < m; board[start_r][start_c] = OBSTACLE, board[start_r++][start_c + 1] = OBSTACLE);
	start_r = m / 2;
	for (start_c = 2 * n / 3; start_r < m; board[start_r][start_c] = OBSTACLE, board[start_r++][start_c - 1] = OBSTACLE);
	return;
}
void spiral(short ** board, int m, int n) {
	int start_r, start_c;
	start_r = 2 * m / 3;
	for (start_c = 0; start_c <= n / 2 - 2; board[start_r][start_c++] = OBSTACLE);
	start_r = m / 3;
	for (start_c = n - 1; start_c >= n / 2 + 2; board[start_r][start_c--] = OBSTACLE);
	start_c = n / 2 - 2;
	for (start_r = 0; start_r <= m / 2 - 2; board[start_r][start_c] = OBSTACLE, board[start_r++][start_c + 1] = OBSTACLE);
	start_c = n / 2 + 2;
	for (start_r = m - 1; start_r > m / 2 + 2; board[start_r][start_c] = OBSTACLE, board[start_r--][start_c - 1] = OBSTACLE);
}
void wuthout_obstacles(short ** board, int m, int n) {
	return;
}
void messy(short ** board, int m, int n) {
	int start_r, start_c;
	diagonal_corners1(board, m, n);
	diagonal_corners2(board, m, n);
	//Down part row.
	start_r = 3 * m / 4;
	start_c = 0;
	for (int start_c = 0; start_c < n; board[start_r][start_c++] = OBSTACLE);
	start_r = 3 * m / 4;
	for (start_c = 5 * n / 8; start_r < m; board[start_r][start_c] = OBSTACLE, board[start_r++][start_c - 1] = OBSTACLE);
	firs_row_in_the_middle(board, m, n);
	//Up part row
	start_r = 4 * m / 9;
	start_c = 0;
	for (int start_c = 0; start_c <= 4 * n / 10; board[start_r][start_c++] = OBSTACLE);
	start_c = 4 * n / 10;
	for (start_r = 0; start_r <= 4 * m / 9; board[start_r][start_c] = OBSTACLE, board[start_r++][start_c + 1] = OBSTACLE);
	start_r = 4 * m / 9;
	for (int start_c = 6 * n / 10; start_c <= n - 1; board[start_r][start_c++] = OBSTACLE);
	return;
}
int set_obstacles(short ** board, int m, int n, int guess) {
	//int guess = (int)((double)rand() / (RAND_MAX + 1) *OBSTACLES_TYPES + 1);
	//scanf_s("%d", &guess);
	switch (guess) {
	case 1:
		angle_center(board, m, n);
		break;
	case 2:
		coordinate_axis(board, m, n);
		break;
	case 3:
		wuthout_obstacles(board, m, n);
		break;
	case 4:
		down_tree_part(board, m, n);
		break;
	case 5:
		spiral(board, m, n);
		break;
	case 6:
		two_lines(board, m, n);
		break;
	case 7:
		messy(board, m, n);
		break;
	}
	return guess;
}
//Choose obstacles.
void random_obstacles(short ** board, int m, int n, Header *header) {
	int guess;
	int start_r, start_c;
	int size_r = (m > 10 ? 4 : m <= 4 ? 0 : 2);
	int size_c = (n > 10 ? 8 : n <= 4 ? 0 : 1);
	//srand(time(NULL));
	int count = 5, next = 1, counter = 0;
	int used[5] = { 0 };
	int incompatible[OBSTACLES_TYPES] = { 0 };
	if (n < 35 && m<25) {
		count = 3;
		incompatible[29] = TRUE;
		incompatible[30] = TRUE;
		incompatible[23] = TRUE;
		incompatible[8] = TRUE;
		incompatible[3] = TRUE;
		incompatible[26] = TRUE;

	}
	FILE * obstacles = fopen("Obstacles.txt", "w");
	guess = (int)((double)rand() / (RAND_MAX + 1) * 100);
	//guess = 1;
	if (guess > 70 && guess <78  && n>42 && m>25) {
		set_obstacles(board, m, n, guess % 70);
		return;
	}
	while (count > 0) {
		do {
			guess = (int)((double)rand() / (RAND_MAX + 1) *(OBSTACLES_TYPES + 1));
		} while (used[0] == guess || used[1] == guess || used[2] == guess || used[3] == guess || used[3] == guess);
		used[counter++] = guess;
		//guess = 19;
		//scanf("%d", &guess);
		fprintf(obstacles, "%d ", guess);
		switch (guess) {
		case 1: {
			diagonal_corners1(board, m, n);
			break;
		}
		case 2: {
			diagonal_corners1(board, m, n);
			break;

		}
		case 3: {
			if (!incompatible[23] && !incompatible[29] && !incompatible[30]) {
				col_with_holes(board, m, n);
				incompatible[3] = TRUE;
			}
			else {
				count++; counter--;
			}
			break;

		}
		case 4: {
			if (!incompatible[6]) {
				first_and_last_row(board, m, n);
				incompatible[4] = TRUE;
			}
			else {
				count++;
				counter--;
			}
			break;
		}
		case 5: {
			if (!incompatible[29] && !incompatible[30]) {
				one_line(board, m, n);
				incompatible[5] = TRUE;

			}
			else {
				count++; counter--;
			}
			break;
		}
		case 6: {
			if (!incompatible[4]) {
				first_and_last_column(board, m, n);
				incompatible[6] = TRUE;
			}
			else {
				count++;
				counter--;
			}
			break;
		}
		case 7: {
			fisrt_row(board, m, n);
			break;
		}
		case 8: {
			if (!incompatible[23] && !incompatible[16] && !incompatible[29] && !incompatible[30]) {
				column_with_hole(board, m, n);
				incompatible[8] = TRUE;
			}
			else {
				count++;
				counter--;
			}
			break;

		}
		case 9: {
			if (!incompatible[29] && !incompatible[30]) {
				row_with_holes(board, m, n);
				incompatible[9] = TRUE;
			}
			break;
		}
		case 10: {
			if (!incompatible[13] && !incompatible[29] &&!incompatible[23]) {
				half_col_down(board, m, n);
				incompatible[10] = TRUE;
			}
			else {
				count++; counter--;
			}
			break;
		}
		case 11: {
			if (!incompatible[23] && !incompatible[30]) {
				half_row_with_hole(board, m, n);
				incompatible[11] = TRUE;

			}
			else {
				count++; counter--;
			}
			break;
		}
		case 12: {
			if (!incompatible[29]) {
				half_col_up(board, m, n);
				incompatible[29] = TRUE;
			}
			else {
				count++; counter--;
			}
			break;
		}
		case 13: {
			if (!incompatible[10] && !incompatible[23] && !incompatible[29]) {
				half_row_left(board, m, n);
				incompatible[13] = TRUE;
			}
			else {
				count++; counter--;
			}
			break;
		}
		case 14: {
			if (!incompatible[30]) {
				half_row_right_up(board, m, n);
				incompatible[14] == TRUE;
			}
			else {
				count++; counter--;
			}
			break;
		}
		case 15: {
			firs_row_in_the_middle(board, m, n);
			break;
		}
		case 16: {
			if (!incompatible[23] && !incompatible[8] && !incompatible[29] && !incompatible[30]) {
				row_with_holes_down_middle(board, m, n);
				incompatible[16] = TRUE;
			}
			else {
				count++; counter--;
			}
			break;
		}
		case 17: {
			if (!incompatible[23] && !incompatible[29] && !incompatible[30]) {
				row_down_middle(board, m, n);
				incompatible[17] = TRUE;
			}
			else {
				count++; counter--;
			}
			break;
		}
		case 18: {
			if (!incompatible[29] && !incompatible[30]) {
				row_with_hole_in_middle(board, m, n);
				incompatible[18] = TRUE;
			}
			else {
				count++; counter--;
			}
			break;
		}
		case 19: {
			first_col_with_hole(board, m, n);
			break;
		}
		case 20: {
			last_row_with_hole(board, m, n);
			break;
		}
		case 21: {
			if (!incompatible[23]) {
				last_col_with_hole(board, m, n);
				incompatible[21] = TRUE;
			}
			break;
		}
		case 22: {
			first_row_with_hole(board, m, n);
			break;
		}
		case 23: {
			if (!incompatible[16] && !incompatible[11] && !incompatible[13] && !incompatible[3] && !incompatible[8] && !incompatible[17] && !incompatible[29] && !incompatible[30] &&!incompatible[10] && !incompatible[21]) {
				stairs(board, m, n);
				incompatible[23] = TRUE;
			}
			else {
				count++; counter--;
			}
			break;
		}
		case 24: {
			square_in_the_middle(board, m, n);
			break;
		}
		case 25: {
			square_left_up(board, m, n);
			break;
		}
		case 26: {
			if (!incompatible[26])
			square_left_up(board, m, n);
			break;
		}
		case 27: {
			square_right_down(board, m, n);
			break;
		}
		case 28: {
			square_left_down(board, m, n);
			break;
		}
		case 29: {
			if (!incompatible[23] && !incompatible[16] && !incompatible[11] && !incompatible[13] && !incompatible[3] && !incompatible[8] && !incompatible[9] && !incompatible[17] && !incompatible[30] && !incompatible[18] && !incompatible[5] && !incompatible[10] && !incompatible[16] && !incompatible[17]) {
				zik_zak_left(board, m, n);
				incompatible[29] = TRUE;
			}
			else {
				count++; counter--;
			}
			break;
		}
		case 30: {
			if (!incompatible[23] && !incompatible[16] && !incompatible[11] && !incompatible[13] && !incompatible[3] && !incompatible[8] && !incompatible[9] && !incompatible[17] && !incompatible[29] && !incompatible[18] && !incompatible[3] && !incompatible[5] && !incompatible[11] && !incompatible[14] && !incompatible[17]) {
				zik_zak_right(board, m, n);
				incompatible[30] = TRUE;
			}
			else {
				count++; counter--;
			}
			break;
		}
		}
		count--;
	}
	fclose(obstacles);
}
void set_snake(short ** board, int m, int n, Header *header) {
	int snake_size = MAX;
	int start_c, start_r;
	Pointer temp;

	start_r = m - 2; start_c = 2;

	header->head = malloc(sizeof(Element));
	if (header->head == NULL)
		exit(EXIT_FAILURE);
	header->head->column = start_c;
	header->head->row = start_r;
	header->head->next = NULL;
	header->tail = header->head;
	board[start_r][start_c] = SNAKE;
	start_c >= n - 1 ? start_c %= n : start_c++;
	for (int i = 2; i <= snake_size; i++) {
		temp = malloc(sizeof(Element));
		if (temp == NULL)
			exit(EXIT_FAILURE);
		temp->column = start_c;
		temp->row = start_r;
		header->head->next = temp;
		temp->next = NULL;
		header->head = header->head->next;
		board[start_r][start_c] = SNAKE;
		start_c >= n - 1 ? start_c %= n : start_c++;
	}
}
//Use to find empty_position on map.
int empty_position(short **board, int m, int n) {
	int free = 0;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if (board[i][j] == FREE)
				free = 1;
	return free;
}
//Use to randomly generate fruit on map.
Fruit generate_fruit(short **board, int m, int n) {
	int fruit_r;
	int fruit_c;
	if (!empty_position(board, m, n)) {
		fruit_r = -1;
		fruit_c = -1;
	}
	else {
		do {

			fruit_r = (int)((double)rand() / (RAND_MAX + 1) * m);
			fruit_c = (int)((double)rand() / (RAND_MAX + 1) * n);

		} while (board[fruit_r][fruit_c] != 0);
		board[fruit_r][fruit_c] = FRUIT;
	}
	Fruit fruit = { fruit_r,fruit_c };
	return fruit;
}
//Use to initialize game map. 
short **set_game(int m, int n, Header *header, Fruit *fruit) {

	short **board = malloc(m * sizeof(short*));
	if (board == NULL)
		exit(EXIT_FAILURE);
	for (int i = 0; i < m; i++) {
		board[i] = calloc(n, sizeof(short));
		if (board[i] == NULL)
			exit(EXIT_FAILURE);
	}
	random_obstacles(board, m, n, header);
	int guess = 1;
	set_snake(board, m, n, header);
	*fruit = generate_fruit(board, m, n);
	return board;
}
void delete_list(Header *header)
{
	Pointer temp = header->tail;
	while (temp)
	{
		header->tail = header->tail->next;
		free(temp);
		temp = header->tail;
	}
}
void delete_matrix(short ***board, int m, int n) {
	for (int i = 0; i < m; i++)
		free((*board)[i]);
	free(*board);
}

