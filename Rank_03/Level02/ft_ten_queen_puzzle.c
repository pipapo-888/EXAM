#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// void print_solution(int board[4])
// {
//     char str[5];
//     int i;

//     i = 0;
//     while (i < 4)
//     {
//         str[i] = board[i] + '0';
//         i++;
//     }
//     str[i] = '\n';
//     write(1, str, 5);
// }

// int is_safe(int board[4], int row, int col)
// {
//     int i;

//     i = 0;
//     while (i < row)
//     {
//         if (board[i] == col || (board[i] - i) == (col - row)
//             || (board[i] + i) == (col + row))
//             return (0);
//         i++;
//     }
//     return (1);
// }

// void solve(int board[], int row)
// {
//     int col;

//     if (row == 4)
//     {
//         print_solution(board);
//         return ;
//     }
//     col = 0;
//     while (col < 4)
//     {
//         if (is_safe(board, row, col))
//         {
//             board[row] = col;
//             solve(board, row + 1);
//         }
//         col++;
//     }
// }
// void ft_four_queens_puzzle(void)
// {
//     int board[4];
//     solve(board, 0);
// }

// N_QUEEN

// int	is_safe(int board[], int row, int col)
// {
// 	for (int i = 0; i < row; i++)
// 	{
// 		if (board[i] == col || (board[i] - i) == (col - row) || (board[i]
// 				+ i) == (col + row))
// 			return (0);
// 	}
// 	return (1);
// }

// void	print_board(int board[], int n)
// {
// 	for (int i = 0; i < n; i++)
// 	{
// 		printf("%d", board[i]);
// 	}
// 	printf("\n");
// }

// void	s(int board[], int row, int n)
// {
// 	int	col;

// 	if (row == n)
// 	{
// 		print_board(board, n);
// 		return ;
// 	}
// 	col = 0;
// 	while (col < n)
// 	{
// 		if (is_safe(board, row, col))
// 		{
// 			board[row] = col;
// 			s(board, row + 1, n);
// 		}
// 		col++;
// 	}
// }

// void	ft_n_queen(int n)
// {
// 	int	board[n];
// 	s(board, 0, n);
// }

// int	main(int argc, char **argv)
// {
// 	int	n;

// 	if (argc != 2)
// 		return (0);
// 	n = atoi(argv[1]);
// 	ft_n_queen(n);
// 	// ft_four_queens_puzzle();
// }


// int is_safe(int board[], int row, int col)
// {
// 	for (int i = 0; i < row; i++)
// 	{
// 		if (board[i] == col || (board[i] - i) == (col - row) || (board[i] + i) == (col + row))
// 			return (0);
// 	}
// 	return (1);
// }

// void s(int board[], int row, int n)
// {
// 	if (row == n)
// 	{
// 		for (int i = 0; i < n; i++)
// 			printf("%d", board[i]);
// 		printf("\n");
// 		return ;
// 	}
// 	int col = 0;
// 	while (col < n)
// 	{
// 		if (is_safe(board, row, col))
// 		{
// 			board[row] = col;
// 			s(board, row + 1, n);
// 		}
// 		col++;
// 	}
// }

// void ft_n_queen(int n)
// {
// 	int board[n];
// 	s(board, 0, n);
// }

// int main(int argc, char **argv)
// {
// 	int n;

// 	if (argc != 2 || argv[1][0] == '\0')
// 		return (1);
// 	n = atoi(argv[1]);
// 	ft_n_queen(n);

// }

int is_safe(int board[], int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		if (board[i] == col || (board[i] - i) == (col - row) || (board[i] + i) == (col + row))
			return (0);
	}
	return (1);
}

void dfs(int board[], int row, int n)
{
	if (row == n)
	{
		for(int i = 0; i < n; i++)
		{
			printf("%d", board[i]);
		}
		printf("\n");
		return ;
	}
	for (int col = 0; col < n; col++)
	{
		if (is_safe(board, row, col))
		{
			board[row] = col;
			dfs(board, row + 1, n);
		}
	}
}

void ft_nqueen(int n)
{
	int board[n];
	dfs(board, 0, n);
}


int main(int ac, char **av)
{
	if (ac != 2 || av[1][0] == '\0')
		return (1);
	int n = atoi(av[1]);
	ft_nqueen(n);




	return (0);
}