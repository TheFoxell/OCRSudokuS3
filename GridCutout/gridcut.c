#include <err.h>
#include <string.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include "griddetect.h"



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

    image_surface = load_image("image_02_bin2.jpg");
    screen_surface = image_surface;
    // TODO: Display the image.

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

    display_image(image_surface);
    display_image(screen_surface);
    
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
	      
	      display_image(newCase);

	      wait_for_keypressed();
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
