#include <err.h>
#include <string.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "griddetect.h"
#include "gridcut.h"
# include "../tool/tool_image.h"
# include "../tool/pixel_operations.h"



int GridDetCut(char filename[])
{
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;

    // TODO: Initialize the SDL

    init_sdl();

    image_surface = load_image(filename);
    screen_surface = image_surface;
    // TODO: Display the image.

    display_image(image_surface);
    display_image(screen_surface);
    

    wait_for_keypressed();


    
    void SDL_FreeSurface(SDL_Surface *surface);


    

    
    SDL_Surface* newCase = NULL;
    
    void SetCase(int wCase, int hCase, int x, int y)
    {

      newCase = SDL_CreateRGBSurface(0,wCase,hCase,32,0,0,0,0);

      int _x = x;
      int _y = y;
      
      
      for(int i = 0; i < wCase; i++)
	{
	for(int j = 0; j < hCase; j++)
	  {
	    //printf(" i:%u j:%u x:%u y:%u \n",i,j,_x,_y);
	    
	    Uint32 pixel = get_pixel(image_surface, _x, _y);
	    
	    put_pixel(newCase, i, j, pixel);

   
	    
	    _y += 1;
	    
	    if(_y == (y + hCase))
	      {
		_y = y;
		_x += 1;
	      }
	  }
	}
    }
 



    

    void GridCutout(SDL_Surface *image)
    {
      
      int width = image->w;
      int height = image->h;
      int wCase = width / 9;
      int hCase = height /9;

      int width2 = wCase * 9;
      int height2 = hCase * 9;

      int m1 = 0;
      int m2 = 0;

      
      for(int i = 0; i < width2; i += wCase)
	{
	  for(int j = 0; j < height2; j += hCase)
	    {
	      SetCase(wCase,hCase,i,j);

	      char str[13] = "Cases/";
	      str[6] = m1 + '0';
	      str[7] = m2 + '0';

	      
	      SDL_SaveBMP(newCase, str );
	      
	      m2 += 1;
	      if(m2 == 9)
		{
		  m2 = 0;
		}
	    }
	  m1 += 1;
	}
    }
    
    image_surface = GridDetect(image_surface);
    GridCutout(image_surface);
    
    
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);
    SDL_FreeSurface(newCase);

    return 0;
}
