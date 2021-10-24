# include <string.h>
# include "NeuralNetwork/NeuralNetwork_XOR.h"


int main(int argc, char** argv)
{
	if(argc >= 1)// at least must have one minimum argument
    	{
    		if(!strcmp(argv[1], "xor"))
            	{
                	TestForNeuralNetwork();
                	return 0;
            	}
        	       	
        	/*if(argv[2] == "GridCutout")
        	{
        		GridCutout();
        		return 0;
        	}
        	
        	if(argv[2] == "solver")
        	{
        		main();
        		return 0;
        	}*/
        	
        	//Not implemented
		/*if(argv[2] == "GridDetection")
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