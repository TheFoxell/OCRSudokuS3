#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"

//histogram of the different gray values of the image
int histogram(SDL_Surface *img)
{
  static Uint8 hist[256];

  
    for (int i = 0; i < img->w; i++)
      {
	for (int j = 0; j < img->h; j++)
	  {
	    Uint32 pixel = get_pixel(img, i, j);
	    Uint8 color;
	    SDL_GetRGB(pixel, img->format, &color, &color, &color);
	    hist[color] += 1;
	  }
      }

    return hist;
}


