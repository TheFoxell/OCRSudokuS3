#ifndef	GRAYSCALE_H
#define GRAYSCALE_H

#include <string.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

void SDL_FreeSurface(SDL_Surface *surface);
void init_sdl();
SDL_Surface* display_image(SDL_Surface *img);
SDL_Surface* load_image(char *path);
void wait_for_keypressed();

#endif