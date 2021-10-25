# include <string.h>
# include <stdio.h>
# include <err.h>
# include "NeuralNetwork/NeuralNetwork_XOR.h"
# include "solver/parseur.h"
# include "solver/solver.h"
# include "solver/draw.h"


int main(int argc, char** argv)
{
	if(argc >= 1)// at least must have one minimum argument
    	{
    		if(!strcmp(argv[1], "xor"))
            	{
                	TestForNeuralNetwork();
                	return 0;
            	}
        	       	
        	
        	
        	if(!strcmp(argv[1], "solver"))
		{
        		int grid[9][9];
        		
        		if (argc!=3)
				errx(1,"Usage: filename");
	 
			parser(grid,argv[2]);

			//solver here
			solve(grid);
			recorder(grid, strcat(argv[2],".resultat"));
			drawSudoku(grid, strcat(argv[2],".png"),2);
			return 0;
		}

        	//Not implemented
		/*
		if(argv[2] == "GridCutout")
        	{
        		GridCutout();
        		return 0;
        	}
        	
		if(argv[2] == "GridDetection")
        	{
            		GridDetection();
            		return 0;
        	}
        	*/
        	
        	//TODO: add binarization etc ...

        	printf("Unknown command.\n");
        	return 1;
        
        }
    	else
    	{
        printf("'./main' needs at least one argument.\n");
        return 1;
    	}
}
