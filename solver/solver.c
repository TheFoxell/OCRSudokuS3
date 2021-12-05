#include <stdio.h>
#include <err.h>
#include "parseur.h"
#include <string.h>




int already_in_column(int grid[9][9],int x, int val)
{
	int i=0;
	while (i<9 && val!=grid[i][x])
        {
		i++;
        }
        return i != 9;
}

int already_in_line(int grid[9][9],int y, int val)
{
        int i=0;
        while (i<9 && val!=grid[y][i])
        {
                i++;
        }
        return i != 9;
}

int already_in_square(int grid[9][9], int x, int y, int val)
{
	x /= 3;
        y /= 3;
        x *= 3;
        y *= 3;
        int i=0;
        while (i<9 && val!=grid[y+i/3][x+i%3])
        {
        	i++;
        }
        return i != 9;
}

int solve_rec(int grid[9][9],int x, int y)
{
	if (y>8)
	{
		return 0;
	}

	int nextX = x + 1;
        int nextY = y;
        if (nextX==9)
        {
		nextX = 0;
                nextY++;
        }

	if (grid[y][x]!=0)
        {
        	return solve_rec(grid,nextX, nextY);
        }

        for (int i = 1; i < 10; i++)
        {
        	if (!already_in_column(grid,x,i)
		&&  !already_in_line(grid,y,i)
		&&  !already_in_square(grid,x,y,i))
        	{
			grid[y][x] = i;
                	if (solve_rec(grid,nextX,nextY))
                    	{
				return 0;
                    	}
                    	grid[y][x] = 0;
                }
        }
        return 1;
}

void solve(int grid[9][9])
{
	solve_rec(grid,0,0);
}


