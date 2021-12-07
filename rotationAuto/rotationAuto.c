#include <string.h>                                                            
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "../GridCutout/gridcut.h"                                              
#include "../GridCutout/griddetect.h"                                           
#include "../rotation/rotation.h"
#include "../tool/tool_image.h"
#include "../tool/pixel_operations.h"


int nbrElmt(int histo[], int len)
{
  int nbr = 0;

  for(int i = 0; i < len; i++)
    {
      if(histo[i] > 0)
	nbr++;
    }

  return nbr;
}

void RotAndCut(char filename[], int sens)
{
  SDL_Surface* image;
  SDL_Surface* image2;
  
  init_sdl();
  
  image = load_image(filename);
  image2 = image;

  display_image(image);

  wait_for_keypressed();
  
  int width = image->w;
  int height = image->h;
  
  int * hCols = (int *) calloc(width, sizeof(int));
  int * hRows = (int *) calloc(height, sizeof(int));

  MakeHisto(image2, hCols, hRows);

  int angl = 0;

  while(nbrElmt(hCols, width)< width/65 && nbrElmt(hRows, height)< height/65)
    {
      image2 = rotation(image, angl += sens);

      width = image2->w;
      height = image2->h;
      
      hCols = realloc(hCols, (image2->w) * sizeof(int));
      hRows = realloc(hRows, (image2->h) * sizeof(int));

      MakeHisto(image2, hCols, hRows);
    }
  SDL_SaveBMP(image2, "image_rot.jpg");
  GridDetCut("image_rot.jpg");

  free(hCols);
  free(hRows);
}
