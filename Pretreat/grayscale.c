#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../tool/pixel_operations.h"
#include "../tool/tool_image.h"
#include "tresholding.h"

void SDL_FreeSurface(SDL_Surface *surface);

int main()
{
    // display an image
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;

    init_sdl();

    image_surface = load_image("my_image.jpg");
    screen_surface = display_image(image_surface);

    // wait a key
    wait_for_keypressed();


    // browse the image
    int width = image_surface->w;
    int height = image_surface->h;

    for ( int i = 0 ; i < width ; i ++)
    {
	    for (int j = 0 ; j < height ; j++)
	    {
		    Uint32 pixel = get_pixel(image_surface, i, j);

		    Uint8 r, g, b;
	            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);

		    int average = 0.3*r + 0.59*g + 0.11*b;

		    pixel = SDL_MapRGB(image_surface->format, average,
				    average, average);
		    
		    put_pixel(image_surface,i,j,pixel);

	    }
    }

    //redraw the surfaces
    update_surface(screen_surface, blackwhite(image_surface));
    
    //wait for a key0
    wait_for_keypressed();

    //free the surface
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface); 


    return 0;
}
