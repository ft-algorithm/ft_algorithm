/*
    작은 네모 확인 :  i ~ i + 2, j ~ j + 2 끼리
    가로 확인 : i가 같은 애들끼리
    세로 확인 : j가 같은 애들끼리
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool	valid_square(char **board, int i, int j)
{
	int	check[9];
	int	row;
	int	col;

	row = 0;
	memset(check, 0, sizeof(int) * 9);
	while (row < 3)
	{
		col = 0;
		while (col < 3)
		{
			if (board[i + row][j + col] != '.')
			{
				if (check[board[i + row][j + col] - '0' - 1])
					return (false);
				check[board[i + row][j + col] - '0' - 1] = 1;
			}
			col++;
		}
		row++;
	}
	return (true);
}

bool	check_square(char **board)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (!valid_square(board, i * 3, j * 3))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	check_col(char **board)
{
	int	i;
	int	j;
	int	check[9];

	i = 0;
	while (i < 9)
	{
		j = 0;
		memset(check, 0, sizeof(int) * 9);
		while (j < 9)
		{
			if (board[i][j] != '.')
			{
				if (check[board[i][j] - '0' - 1])
					return (false);
				check[board[i][j] - '0' - 1] = 1;
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool	check_row(char **board)
{
	int	i;
	int	j;
	int	check[9];

	i = 0;
	while (i < 9)
	{
		j = 0;
		memset(check, 0, sizeof(int) * 9);
		while (j < 9)
		{
			if (board[j][i] != '.')
			{
				if (check[board[j][i] - '0' - 1])
					return (false);
				check[board[j][i] - '0' - 1] = 1;
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool isValidSudoku(char** board, int boardSize, int* boardColSize){
	if (!check_square(board))
		return (false);
	if (!check_col(board))
		return (false);
	if (!check_row(board))
		return (false);
	return (true);
}
