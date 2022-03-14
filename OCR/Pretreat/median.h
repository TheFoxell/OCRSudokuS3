#ifndef MEDIAN_H
#define MEDIAN_H

void sGrayscale(Uint32 grayscale[], int i, int j);
Uint32 Median(Uint32 grayscale[]);
Uint32 NewPixel(SDL_Surface *image, int x, int y);
SDL_Surface* noise(SDL_Surface *image);

#endif
