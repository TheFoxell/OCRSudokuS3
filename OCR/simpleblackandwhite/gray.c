#include <err.h>
#include <string.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../tool/pixel_operations.h"                                           
#include "../tool/tool_image.h"      


int grayscale(char filename[])
{
    // display an image
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;

    init_sdl();

    image_surface = load_image(filename);
    screen_surface = display_image(image_surface);

    // wait a key
    wait_for_keypressed();


    // browse the image
    int width = image_surface->w;
    int height = image_surface->h;

    //for each pixel calculation of its value, if greater than the threshold then white, if less then black
    for ( int i = 0 ; i < width ; i ++)
    {
	    for (int j = 0 ; j < height ; j++)
	    {
		    Uint32 pixel = get_pixel(image_surface, i, j);

		    Uint8 r, g, b;
	            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
			
		    int average= 0;
		    int m = (r + g + b)/3;
		    if (m > 128)
			average = 255;
		    else
			average = 0;

		    pixel = SDL_MapRGB(image_surface->format, average,
				    average, average);
		    
		    put_pixel(image_surface,i,j,pixel);

	    }
    }

    //redraw the surfaces
    update_surface(screen_surface, image_surface);

    SDL_SaveBMP(image_surface, "image_bin.jpg");
    
    //wait for a key0
    wait_for_keypressed();

    //free the surface
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface); 


    return 0;
}
