#ifndef OTSU_H
#define OTSU_H

Uint8* histogram(SDL_Surface* image_surface);
int* average(Uint8* hist, int size);
float variance(Uint8* hist, int size, int* data);
float varianceintraclasse(Uint8* class1, Uint8* class2, int size1);
int otsu(Uint8* hist);
SDL_Surface* blackwhite(SDL_Surface* image);

#endif
