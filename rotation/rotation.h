#ifndef	ROTATION_H
#define ROTATION_H

#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../tool/tool_image.h" 
#include "../tool/pixel_operations.h" 
#include <math.h>
#include <string.h>

void menuRotation(char filename[]);

SDL_Surface* rotation(SDL_Surface* image_surface, int angl);

#endif
