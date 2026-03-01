#include <unistd.h>

void print_solution(int board[4])
{
    char str[5];
    int i;

    i = 0;
    while (i < 4)
    {
        str[i] = board[i] + '0';
        i++;
    }
    str[i] = '\n';
    write(1, str, 5);
}

int is_safe(int board[4], int row, int col)
{
    int i;

    i = 0;
    while (i < row)
    {
        if (board[i] == col || (board[i] - i) == (col - row)
            || (board[i] + i) == (col + row))
            return (0);
        i++;
    }
    return (1);
}

void solve(int board[], int row)
{
    int col;

    if (row == 4)
    {
        print_solution(board);
        return ;
    }
    col = 0;
    while (col < 4)
    {
        if (is_safe(board, row, col))
        {
            board[row] = col;
            solve(board, row + 1);
        }
        col++;
    }
}
void ft_four_queens_puzzle(void)
{
    int board[4];
    solve(board, 0);
}

void s(int board[], int row, int n)
{
	int col;
	if (row == n)
	
}

void ft_n_queen(int n)
{
	int board[n];
	s(board, 0, n);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	int n = atoi(argv[1]);



	// ft_four_queens_puzzle();
	
}
