#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include <math.h>


SDL_Surface* GlBlur(SDL_Surface* image)
{
  int width = image->w;
  int height = image->h;

  double g(int x, int y, double sigma)
  {
    return 1. / (2 * M_PI * sigma * sigma) *
      exp(-(x * x + y * y) / (2 * sigma * sigma));
  }

  double filtre[9][9];
  double sigma = 0.84089642;

  int x,y;
  for(y = -4; y <= 4;y++)
    for(x = -4 ; x <= 4; x++)
      filtre[x + 4][y + 4] = g(x,y,sigma);

  for(y = 0; y < 9; y++)
    {
      for (x = 0; x < 9; x++)
	printf("%.2f ", filtre[x][y]);
    }

  for(int x = 4; x < width - 4; x++)
    {
      for(int y = 4; y < height - 4;y++)
	{
	  double redVal = 0.0;
	  double greenVal = 0.0;
	  double blueVal = 0.0;

	  //Convolution step

	  for(int filtreX = -4; filtreX <= 4; filtreX++)
	    {
	      for(int filtreY = -4; filtreY <= 4; filtreY++)
		{
		  double filtreVal = filtre[filtreX + 4][filtreY + 4];

		   Uint32 pixel = get_pixel(image, x - filtreX, y - filtreY);
		   Uint8 r,g,b;
		   SDL_GetRGB(pixel, image->format, &r, &g, &b);	    
		   double newR = (double) r;
		   double newG = (double) g;
		   double newB = (double) b;

		   redVal += newR * filtreVal;
		   greenVal += newG * filtreVal;
		   blueVal += newB * filtreVal; 
		    
		}
	    }
	  Uint32 pixel2 = SDL_MapRGB(image->format, (Uint8) redVal, (Uint8) greenVal, (Uint8) blueVal);

	  put_pixel(image,x,y,pixel2);
	  
	}
    }
  return image;
}



int main()
{
  
  SDL_Surface* image_surface;
  SDL_Surface* screen_surface;

    // TODO: Initialize the SDL

    void init_sdl()
    {
      // Init only the video part.
      // If it fails, die with an error message.
      if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
    }

    init_sdl();

    
    SDL_Surface* load_image(char *path)
    {
      SDL_Surface *img;

      // Load an image using SDL_image with format detection.
      // If it fails, die with an error message.
      img = IMG_Load(path);
      if (!img)
        errx(3, "can't load %s: %s \n", path, IMG_GetError());

      return img;
    }


    SDL_Surface* display_image(SDL_Surface *img)
    {
      SDL_Surface *screen;

      // Set the window to the same size as the image
      screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
      if (screen == NULL)
	{
	  // error management
	  errx(1, "Couldn't set %dx%d video mode: %s\n",
	       img->w, img->h, SDL_GetError());
	}

      // Blit onto the screen surface
      if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

      // Update the screen
      SDL_UpdateRect(screen, 0, 0, img->w, img->h);

      // return the screen for further uses
      return screen;
    }
    
    // TODO: Wait for a key to be pressed.
    void wait_for_keypressed()
    {
      SDL_Event event;

      // Wait for a key to be down.
      do
	{
	  SDL_PollEvent(&event);
	} while(event.type != SDL_KEYDOWN);

      // Wait for a key to be up.
      do
	{
	  SDL_PollEvent(&event);
	} while(event.type != SDL_KEYUP);
    }

    
    void SDL_FreeSurface(SDL_Surface *surface);
    
    //SDL_Surface* newCase = NULL;

    
    image_surface = load_image("image_01.jpeg");
    screen_surface = image_surface;

    display_image(image_surface);
    display_image(screen_surface);

    wait_for_keypressed();
    
    GlBlur(image_surface);

    display_image(image_surface);
    display_image(screen_surface);

    wait_for_keypressed();

    
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);

      


    return 0;
}
