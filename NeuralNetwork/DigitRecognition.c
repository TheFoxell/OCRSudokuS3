#include "nn.h"
#include <err.h>

int main(int argc, char** argv)
{
    Network network;
    initNetwork(&network);
    
    if(argc >= 1) //At least must have one minimum argument
    {
    	if(!strcmp(argv[1], "test")) //Train and test the Neural Network with MNIST database showing accuracy
            {
		if (argc > 2)
			errx(1,"Too many args");
		
		Network network;
    		initNetwork(&network);
    		
		testNetwork(&network);
			
    		for(int i=0; i<TRAINING_EPOCHS; ++i){
        		printf("Training epoch %i/%i\n", i + 1, TRAINING_EPOCHS);
        		trainNetwork(&network);
        		testNetwork(&network);
    		}
    			
                return 0;
            }
    	
    	if(!strcmp(argv[1], "find")) //Train and find value of the input images
        {
		if (argc > 2)
			errx(1,"Too many args");
			
		Network network;
    		initNetwork(&network);
    		
    		int result[9][9];

		for(int i=0; i<TRAINING_EPOCHS; ++i)
    			trainNetwork(&network);
    		
    		printf("number is : %hhu", findDigit(&network, "10.png"));
    		
    		/*for(int l = 0; l < 9; l++)
    		{
    			for(int c = 0; c < 9; c++)
    			{
    				int sizePath = 1024;
  				char path[sizePath];
  				snprintf(path, sizePath, "./Cases/%d%d.png", l, c);
    				result[l][c] = findDigit(&network, path);
    			}
		}*/
    		return 0;
    	}
    			
                	
    }
    
    else
    {
        printf("'./DigitRecognition' needs at least one argument.\n");
        return 1;
    }
    
    
}
