#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include "griddetect.h"
#include <math.h>



//SDL_Surface* finalGrid = NULL;
//SDL_Surface* image_surface;
//SDL_Surface* screen_surface;

void MakeHisto(SDL_Surface* image, int hCols[], int hRows[])
{
  int width = image->w;
  int height = image->h;

  
  for(int x = 0; x < width;x++) //Histo of Columns
    {
      int sum = 0;
      int max = 0;
      for(int y = 0; y < height; y++)
	{
	  Uint32 pixel = get_pixel(image,x,y);

	  Uint8 r,g,b;
	  SDL_GetRGB(pixel, image->format, &r,&g,&b);

	  if(r + g + b < 500)
	      sum++;
	  else
	    {
	      if(sum > max)
		max = sum;
	      sum = 0;
	      }
	}
      if(max > (width / 4)) //Detection cols
	  hCols[x] = max;
      else
	hCols[x] = 0;
    }

  for(int y = 0; y < height;y++) //Histo of Rows
    {
      int sum = 0;
      int max = 0;
      for(int x = 0; x < width; x++)
	{
	  Uint32 pixel = get_pixel(image,x,y);

	  Uint8 r,g,b;
	  SDL_GetRGB(pixel, image->format, &r,&g,&b);

	  if(r + g + b < 500)
	      sum++;
	  else
	    {
	      if(sum > max)
		max = sum;
	      sum = 0;
	      }
	}
      if(max > (height / 4)) //Detection rows
	hRows[y] = max;
      else
	hRows[y] = 0;
    }
  //for(int i = 0; i < width; i++)
  //printf("%u ",hCols[i]);
  
}

void Find(int histo[], int size, int paraList[])
{
  //Find first index and the size of width or height

  
  int find = 0;

  int indexDebut = 0;
  int indexFin = 0;

  int taille = 0;

  int i = 0;
  
  while(find == 0)
    {
      if(histo[i] != 0)
	{
	  indexDebut = i;
	  find = 1;
	}
      i++;
    }
  
  i = size;
  find = 0;

  while(find == 0)
    {
      if(histo[i] != 0)
	{
	  indexFin = i;
	  find = 1;
	}
      i--;
    }

  taille = indexFin - indexDebut;

  paraList[0] = indexDebut;
  paraList[1] = taille;
}

void reSize(int wCase, int hCase, int x, int y,SDL_Surface* finalGrid,SDL_Surface* image)
    {

      int _x = x;
      int _y = y;
      
      
      for(int i = 0; i < wCase; i++)
	{
	for(int j = 0; j < hCase; j++)
	  {
	    //printf(" i:%u j:%u x:%u y:%u \n",i,j,_x,_y);
	    
	    Uint32 pixel = get_pixel(image, _x, _y);
	    
	    put_pixel(finalGrid, i, j, pixel);

   
	    
	    _y += 1;
	    
	    if(_y == (y + hCase))
	      {
		_y = y;
		_x += 1;
	      }
	  }
	}
    }


SDL_Surface* GridDetect(SDL_Surface* image)
{
  int width = image->w;
  int height = image->h;
  
  int hCols[width];
  int hRows[height];

  int paraListCols[2];
  int paraListRows[2];


  MakeHisto(image,hCols,hRows);
  Find(hCols, width-1, paraListCols);
  Find(hRows, height-1, paraListRows);

  printf("%u %u \n", paraListCols[0], paraListCols[1]);
  printf("%u %u \n", paraListRows[0], paraListRows[1]);


   SDL_Surface* finalGrid = SDL_CreateRGBSurface(0,paraListCols[1], paraListRows[1],32,0,0,0,0);
 
  reSize(paraListCols[1], paraListRows[1], paraListCols[0], paraListRows[0], finalGrid, image);

  SDL_SaveBMP(finalGrid, "grid.jpg");
  
  return finalGrid;
}
