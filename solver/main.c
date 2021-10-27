# include <string.h>
# include <stdio.h>
# include <err.h>
# include "parseur.h"
# include "solver.h"

int main(int argc, char **argv)
{
	int grid[9][9];
        		
	if (argc!=2)
		errx(1,"Usage: solver \"filename\"");
	 
	parser(grid,argv[1]);

	solve(grid);
	recorder(grid, strcat(argv[1],".resultat"));
	drawSudoku(grid, strcat(argv[1],".png"),8);
	return 0;
}
