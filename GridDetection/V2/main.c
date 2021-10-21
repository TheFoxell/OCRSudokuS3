#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include <math.h>




//int histoRows[];
//int histoCols[];

void MakeHisto(SDL_Surface* image)
{
  int width = image->w;
  int height = image->h;
  int hCols[width];

  
  for(int x = 0; x < width;x++)
    {
      int sum = 0;
      for(int y = 0; y < height; y++)
	{
	  Uint32 pixel = get_pixel(image,x,y);

	  Uint8 r,g,b;
	  SDL_GetRGB(pixel, image->format, &r,&g,&b);

	  if(r + g + b < 500)
	      sum++;
	}
      hCols[x] = sum;
    }

  for(int i = 0; i < width; i++)
    {
      printf("%u ", hCols[i]);
    }
  
}
/*
SDL_Surface* GridDetect(SDL_Surface* image)
{
  int width = image->w;
  int height = image->h;

  
  return image;
}

*/

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

    
    image_surface = load_image("image_02_bin.jpg");
    screen_surface = image_surface;

    display_image(image_surface);
    display_image(screen_surface);

    wait_for_keypressed();

    
    MakeHisto(image_surface);

      //GridDetect(image_surface);

    display_image(image_surface);
    display_image(screen_surface);

    wait_for_keypressed();

    
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);

      


    return 0;
}
