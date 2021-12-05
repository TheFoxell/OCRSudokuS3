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

int main()                                                                      
{                                                                               
  /*                                                                            
    param : RotAndCut(name, sens);                                              
    sens = 1  : left rotation                                                   
    sens = -1 : right rotation                                                  
  */                                                                            
                                                                                
  RotAndCut("image_torotate1.jpg", -1);                                         
}    
