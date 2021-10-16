#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"

// TODO: Insert all the above functions.

//Uint32 pixel = get_pixel(image_surface, x, y);
//put_pixel(image_surface, x, y, pixel);
//Uint8 r, g, b;
//SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
//Uint32 pixel = SDL_MapRGB(image_surface->format, r, g, b);
//int width = image_surface->w;
//int height = image_surface->h;
//update_surface(screen_image, surface_image);

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
        errx(3, "can't load %s: %s", path, IMG_GetError());

      return img;
    }

    image_surface = load_image("image_01.jpeg");
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

    // TODO: Free the image surface.
    // TODO: Free the screen surface.
    void SDL_FreeSurface(SDL_Surface *surface);

    // SDL_FreeSurface(image_surface);
    // SDL_FreeSurface(screen_surface);

    
    SDL_Surface* newCase = NULL;
    
    void SetCase( int wCase, int hCase)
    {
      //int _x = x;
      //int _y = y;

      
      newCase = SDL_CreateRGBSurface(0,wCase,hCase,32,0,0,0,0);

      
      
      for(int i = 0; i < wCase; i++)
	for(int j = 0; j < hCase; j++)
	  {
	    Uint32 pixel = get_pixel(image_surface, i, j);
	    //_y++;
	    
	    put_pixel(newCase, i, j, pixel);
	    
	  }
      //_x++;
      
    }
    /*
    void GridCutout()
    {
      int width = image_surface->w;
      int height = image_surface->h;
      int wCase = width / 9;
      int hCase = height /9;

      SDL_Surface* Case = SetCase(0,0, wCase,hCase);
      
    }
    */
    //GridCutout();
    
    
    SetCase(111,111);

    if(newCase == NULL)
      {
	printf("Erreur création surface :%s", SDL_GetError());
	return EXIT_FAILURE;
      }

    SDL_SaveBMP(newCase, "Cases/test.jpeg");
    
    display_image(newCase);
    display_image(screen_surface);

    wait_for_keypressed();

    
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);

    return 0;
}
