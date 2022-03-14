# include <string.h>
# include <stdio.h>
# include <err.h>
# include "NeuralNetwork/XOR.h"
# include "solver/parseur.h"
# include "solver/solver.h"
# include "solver/draw.h"
# include "GridCutout/gridcut.h"
# include "GridCutout/griddetect.h"
# include "rotation/rotation.h"
# include "simpleblackandwhite/gray.h"
# include "tool/tool_image.h"
# include "tool/pixel_operations.h"



int main(int argc, char** argv)
{
	if(argc >= 1)// at least must have one minimum argument
    	{
    		if(!strcmp(argv[1], "xor"))
            	{
			if (argc > 2)
				errx(1,"Too many args");

			XOR();
                	return 0;
            	}
        	       	
        	
        	
        	if(!strcmp(argv[1], "solver"))
		{
        		int grid[9][9];
        		
        		if (argc!=3)
				errx(1,"Usage: solver \"filename\"");
	 
			parser(grid,argv[2]);

			//solver here
			solve(grid);
			recorder(grid, strcat(argv[2],".resultat"));
			drawSudoku(grid, strcat(argv[2],".png"),8);
			return 0;
		}

		if(!strcmp(argv[1], "GridCutout"))
        	{
			if (argc > 2)
				errx(1,"Too many args");

        		GridDetCut();
        		return 0;
		}
/*		
		if(!strcmp(argv[1], "rotation"))
        	{
			if (argc!=3)
				errx(1,"Usage: rotation \"filename\"");

        		menuRotation(argv[2]);
        		return 0;
		} //Work in progress...
*/		
		if(!strcmp(argv[1], "grayscale"))
        	{
			if (argc > 2)
				errx(1,"Too many args");

        		grayscale();
        		return 0;
		}
		

        	printf("Unknown command.\n");
        	return 1;
        
        }
    	else
    	{
        printf("'./main' needs at least one argument.\n");
        return 1;
    	}
}
