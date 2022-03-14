#include <string.h>                                                             
#include <stdio.h>                                                              
#include <stdlib.h>                                                             
#include <err.h>                                                                
#include "../GridCutout/gridcut.h"                                             \
                                                                                
#include "../GridCutout/griddetect.h"                                          \
                                                                                
#include "../rotation/rotation.h"                                               
#include "../tool/tool_image.h"                                                 
#include "../tool/pixel_operations.h"
#include "rotationAuto.h"

int main(int argc, char** argv)                                                                      
{                                                                               
  /*                                                                            
    param : RotAndCut(name, sens);                                              
    sens = 1  : left rotation                                                   
    sens = -1 : right rotation                                                  
  */
  if(argc >= 1)
    {
      if(!strcmp(argv[1], "1"))
	RotAndCut("image_torotate1.jpg", 1);
      
      if(!strcmp(argv[1], "-1"))
	RotAndCut("image_torotate2.jpg", -1);     
    }    
}
