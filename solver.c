#include <stdio.h>
#include <err.h>
#include "parseur.h"
#include <string.h>

int grid[9][9];

int already_in_column(int x, int val)
{
	int i=0;
	while (i<9 && val!=grid[i][x])
        {
		i++;
        }
        return i != 9;
}

int already_in_line(int y, int val)
{
        int i=0;
        while (i<9 && val!=grid[y][i])
        {
                i++;
        }
        return i != 9;
}

int already_in_square(int x, int y, int val)
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

int solve_rec(int x, int y)
{
	if (y>8)
	{
		return 1;
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
        	return solve_rec(nextX, nextY);
        }

        for (int i = 1; i < 10; i++)
        {
        	if (!already_in_column(x,i)
		&&  !already_in_line(y,i)
		&&  !already_in_square(x,y,i))
        	{
			grid[y][x] = i;
                	if (solve_rec(nextX,nextY))
                    	{
				return 1;
                    	}
                    	grid[y][x] = 0;
                }
        }
        return 0;
}

void solve()
{
	solve_rec(0,0);
}

int main(int argc, char *argv[]) 
{
	if (argc!=2)
		err(1,"too many argument");
	 
	parser(grid,argv[1]);

	//ici le solver
	solve();

	recorder(grid, strcat(argv[1],".resultat"));
	return 0;
}
