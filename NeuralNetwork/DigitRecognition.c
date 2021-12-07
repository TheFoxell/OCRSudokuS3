#include "DigitRecognition.h"

int DigitRecognition(int command, uint8_t matrix[9][9])
{
    Network network;
    initNetwork(&network);
    
    	if(command == 2) //Train and test the Neural Network with MNIST database showing accuracy
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
    	
    	if(command == 1) //Train and find value of the input images
        {
			
		Network network;
    		initNetwork(&network);
    		

		for(int i=0; i<TRAINING_EPOCHS; ++i)
    			trainNetwork(&network);
    		
    		for(int l = 0; l < 9; l++)
    		{
    			printf("\n");
    			for(int c = 0; c < 9; c++)
    			{
    				int sizePath = 1024;
  				char path[sizePath];
  				snprintf(path, sizePath, "../GridCutout/Cases/%d%d", l, c);
    				matrix[l][c] = findDigit(&network, path);
    				printf("%hhu ", matrix[c][l]);
    			}
		}
			
    		return 0;
    	}
    	
    	if(command == 3) //Train and find value of test input images
        {
			
		Network network;
    		initNetwork(&network);
    		

		for(int i=0; i<TRAINING_EPOCHS; ++i)
    			trainNetwork(&network);
    		
    		for (int digit = 1; digit <10; digit++)
    		{
    			int sizePath = 1024;
  			char path[sizePath];
  			snprintf(path, sizePath, "Test/%d.png", digit);
    			printf("%hhu ", findDigit(&network, path));
    		}
    		
    		return 0;
    	
    	}
    			
                	
   
    
}
