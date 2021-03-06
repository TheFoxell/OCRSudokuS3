#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <math.h>
#include <string.h>
#include "../tool/tool_image.h"
#include "../tool/pixel_operations.h"

//maximum
int max( int a , int b)
{
  if (a < b)
  {
    return b;
  }
  return a;
}

//minimum
int min( int a , int b)
{
  if (a > b)
  {
    return b;
  }
  return a;
}

//rotation function
SDL_Surface* rotation(SDL_Surface* image_surface, int angl)
{
  //calculation of the sin and cos of the angle
  angl%=360;
  float radians = (2*3.1416*angl)/360;

  //calcul of the sin and cos of the angle
  float cosine = (float) cos(radians);
  float sine = (float) sin(radians);

  //calcul the size of the input image
  int width = image_surface->w;
  int height = image_surface->h;
    
  //calcul of the new surface according to the old one
  float x1 = (- height * sine);
  float y1 = (height*cosine);
  float x2 = (width*cosine - height*sine);
  float y2 = (height*cosine + width*sine);
  float x3 = (width*cosine);
  float y3= (width*sine);

  //Calcul for the size of the new image
  float minx=min(0,min(x1,min(x2,x3))); 
  float miny=min(0,min(y1,min(y2,y3))); 
  float maxx=max(x1,max(x2,x3)); 
  float maxy=max(y1,max(y2,y3));
  
  //create the new image
  SDL_Surface* new_img;

  new_img = SDL_CreateRGBSurface(0,fabsf(maxx)-minx,fabsf(maxy)-miny,
		  image_surface->format->BitsPerPixel,
		  image_surface->format->Rmask,
		  image_surface->format->Gmask,
		  image_surface->format->Bmask,
		  image_surface->format->Amask);

 


  //for each pixel of the new image, associate the corresponding pixel of the original image
    for ( int x = 0 ; x < new_img->w ; x ++)
    {
	    for (int y = 0 ; y < new_img->h ; y++)
	    {
	      int imgx = (int) ((x + minx) * cosine + (y + miny) * sine);
	      int imgy = (int) ((y + miny ) * cosine - (x +minx) *sine);
	      if (imgx >= 0 && imgx < width && imgy >= 0 && imgy < height)
		{
		  Uint32 pixel = get_pixel(image_surface, imgx, imgy);
		  put_pixel(new_img, x, y, pixel);
		}
	      else
		{
		  Uint32 pixel = 0xFFFFFFFF;
		  put_pixel(new_img, x, y, pixel);
		}
		    
			     
	    }
    }
   
    
    return new_img ;
 
}

void SDL_FreeSurface(SDL_Surface *surface);

int present(char filename[])
{
    // display an image
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;

    init_sdl();

    image_surface = load_image(filename);
    screen_surface = display_image(image_surface);

    // wait a key
    wait_for_keypressed();
    
   
    
    SDL_Surface* new_img = rotation(image_surface, 700);
    screen_surface = display_image(new_img);

    //redraw the surfaces
    //update_surface(screen_surface, image_surface);
    
    //wait for a key0
    wait_for_keypressed();

    //free the surface
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface); 


    return 0;
}

void menuRotation(char filename[])
{
        // display an image
        SDL_Surface* image_surface;
        SDL_Surface* screen_surface;
	SDL_Surface* new_img;
        init_sdl();

        image_surface = load_image(filename);
        screen_surface = display_image(image_surface);
	new_img=image_surface;
        SDL_Event event;
        int continu = 1;
        int angl=0;
        while(continu)
        {
                SDL_WaitEvent(&event);
                switch(event.type)
                {
                        case SDL_QUIT:
                                continu=0;
                                break;
                        case SDL_KEYDOWN:
                                switch(event.key.keysym.sym)
                                {
                                case(SDLK_s):
                                SDL_SaveBMP(new_img ,"rotation_image.jpg");
                                break;
                                case(SDLK_q):
                                continu=0;
                                break;
        	                case(SDLK_RIGHT):
                                new_img = rotation(image_surface,angl++);
                                screen_surface = display_image(new_img);
				break;
                                case(SDLK_LEFT):
                          	new_img = rotation(image_surface,angl--);
                                screen_surface = display_image(new_img);
                        	break;
				default:  
				break;
                                }
                                break;
                }

        }
        SDL_FreeSurface(image_surface);
        SDL_FreeSurface(screen_surface);

}
