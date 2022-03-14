#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../tool/pixel_operations.h"

//Returns the histogram of the pixel values
Uint8* histogram(SDL_Surface *img)
{
  static Uint8 histo[256];

  
    for (int i = 0; i < img->w; i++)
      {
	for (int j = 0; j < img->h; j++)
	  {
	    Uint32 pixel = get_pixel(img, i, j);
	    Uint8 color;
	    SDL_GetRGB(pixel, img->format, &color, &color, &color);
	    histo[color] += 1;
	  }
      }

    return histo;
}

int* average(Uint8* histo, int size)
{
    int coef = 0;
    static int data[2] = {0,0};
    for (int i = 0; i < size; i++)
    {
	    coef+=i;
	    data[0] += histo[i];
	    data[1] += i*histo[i];
    }
    if (size > 1)
    {
	    data[1] /= coef;
    }
    return data;
}

float variance(Uint8* histo, int size, int* data)
{
    float moyen = data[1];
    float var = 0;
    for (int i = 0; i < size; i++) var += histo[i]*(i-moyen)*(i-moyen);
    return var/data[0];
}

float varianceintraclasse(Uint8* class1, Uint8* class2, int size1)
{

    int* data1 = average(class1, size1+1);
    int* data2 = average(class2, 256-size1);
    int nbpixel = data1[0]+data2[0];
    float rsl = ((float)data1[0]/(float)nbpixel)*variance(class1, size1+1, data1)+((float)data2[0]/(float)nbpixel)*variance(class2, 256-size1, data2);

    return rsl;
}

int otsu(Uint8* histo)
{
    float vw = -1;
    int vw_t = 0;
    for (int t = 0; t<255; t++)
    {
        Uint8 hist2[255-t];
	Uint8 hist1[t+1];
    	for (int i = 0; i < 256; i++) 
	{
		if (i <= t) hist1[i] = histo[i];
		else hist2[i-t-1] = histo[i];	
	}
	float vw_tmp = varianceintraclasse(hist1, hist2, t);
	if (vw_tmp < vw || vw < 0)
	{
		vw = vw_tmp;
		vw_t = t;
	}
    }
    return vw_t;
}

SDL_Surface* blackwhite(SDL_Surface* image)
{
    int seuil = otsu(histogram(image));
    for (int i = 0; i < image->w; i++)
      {
	for (int j = 0; j < image->h; j++)
	  {
	    Uint32 pixel = get_pixel(image, i, j);
	    Uint8 grey;
	    SDL_GetRGB(pixel, image->format, &grey, &grey, &grey);
	  
	    if (grey > seuil) grey = 255;
	    else grey = 0;
	    pixel = SDL_MapRGB(image->format, grey, grey, grey);

	    put_pixel(image, i, j, pixel);
	  }
      } 
    return image;
}

