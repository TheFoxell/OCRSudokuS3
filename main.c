int main(int argc, char** argv)
{
	if(argc > 1)// at least must have one minimum argument
    	{
    		if(argv[2] == "xor")
            	{
                	TestForNeuralNetwork();
                	return 0;
            	}
        	       	
        	if(argv[2] == "GridCutout")
        	{
        		GridCutout();
        		return 0;
        	}
        	
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