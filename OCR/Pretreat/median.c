#include <SDL/SDL.h>
#include "../tool/pixel_operations.h"

void sGrayscale(Uint32 grayscale[], int i, int j)
{
        Uint32 tmp = grayscale[i];
        grayscale[i] = grayscale[j];
        grayscale[j] = tmp;
}

Uint32 Median(Uint32 grayscale[])
{
        for (int i = 0; i < 8; i++)
        {
                Uint32 min = i;
                for (int j = i+1; j < 9; j++) if (grayscale[j] < grayscale[min]) min = j;
                sGrayscale(grayscale, i, min);
        }

        return grayscale[4];
}


Uint32 NewPixel(SDL_Surface *image, int x, int y)
{
        int iArr = 0;
        Uint32 grayscale[9];
        for (int i = -1; i < 2; i++)
        {
                for (int j = -1; j < 2; j++)
                {
                        grayscale[iArr] = get_pixel(image, x+i, y+j);
                        iArr++;
                }
        }

        return Median(grayscale);
}

SDL_Surface* noise(SDL_Surface *image)
{
	int w;
	int h;
	w = image -> w;
	h = image -> h;
	for (int i = 1; i < w-1; i++)
	{
		for (int j = 1; j < h-1; j++) put_pixel(image, i, j, NewPixel(image, i, j));
	}
	return image;
}

