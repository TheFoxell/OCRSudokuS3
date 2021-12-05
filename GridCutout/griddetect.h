#ifndef GRID_DETECT_H_
#define GRID_DETECT_H_

#include <stdlib.h>
#include <SDL.h>

SDL_Surface* GridDetect(SDL_Surface* image);

void MakeHisto(SDL_Surface* image, int hCols[], int hRows[]);

#endif
