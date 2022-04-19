#include <stdbool.h>
#include <stdlib.h>

int check_line(char* line, int len, int dist)
{
	int		*table;

	table = (int *)calloc(len + 1 ,sizeof(int));
	while (len--)
	{
		if (*line == '.')
			;
		else if (table[(*line - '0')]++ > 0)
			return (false);
		line += dist;
	}
	free(table);
	return (true);
}

int check_area(char **area, int row, int col, int boardSize)
{
	int *table;
	int row_idx;
	int col_idx;

	table = (int *)calloc(boardSize + 1, sizeof(int));
	row_idx = -1;
	while (row_idx++ < 2)
	{
	col_idx = -1;
	while (col_idx++ < 2)
	{
		if (area[row + row_idx][col + col_idx] == '.')
			;
		else if(table[area[row + row_idx][col + col_idx] - '0']++ > 0)
		return (false);
	}
	}
	free(table);
	return (true);
}

bool isValidSudoku(char **board, int boardSize, int* boardColSize)
{
	int row;
	int col;

	row = 0;
	while (row < boardSize)
	if (check_line(&board[row++][0], boardSize, 1) == false)
	    return (false);
	col = 0;
	while (col < boardSize)
	if (check_line(&board[0][col++], boardSize, board[1] - board[0]) == false)
	    return (false);
	row = -1;
	while (row++ < 2)
	{
	col = -1;
	while (col++ < 2)
	    if (check_area(board, row * 3, col * 3, boardSize) == false)
		return (false);
	}
	return (true);
}
