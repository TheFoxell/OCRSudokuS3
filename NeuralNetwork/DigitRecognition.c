#include "DigitRecognition.h"

uint8_t DigitRecognition(char command)
{
    Network network;
    initNetwork(&network);
    
    if(command) //At least must have one minimum argument
    {
    	if(command == "test")) //Train and test the Neural Network with MNIST database showing accuracy
            {
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
    	
    	if(command == "finddigit")) //Train and find value of the input images
        {
			
		Network network;
    		initNetwork(&network);
    		
    		uint8_t result[9][9];

		for(int i=0; i<TRAINING_EPOCHS; ++i)
    			trainNetwork(&network);
    		
    		for(int l = 0; l < 9; l++)
    		{
    			printf("\n");
    			for(int c = 0; c < 9; c++)
    			{
    				int sizePath = 1024;
  				char path[sizePath];
  				snprintf(path, sizePath, "../GridCutout/Cases2/%d%d", l, c);
    				result[l][c] = findDigit(&network, path);
    				printf("%hhu ", result[l][c]);
    			}
		}
		
		
    		return result;
    	}
    			
                	
    }
    
    else
    {
        printf("'./DigitRecognition' needs at least one argument.\n");
        return 1;
    }
    
    
}
