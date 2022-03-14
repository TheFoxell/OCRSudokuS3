#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include <math.h>




SDL_Surface* finalGrid = NULL;
SDL_Surface* image_surface;
SDL_Surface* screen_surface;

void MakeHisto(SDL_Surface* image, int hCols[], int hRows[])
{
  int width = image->w;
  int height = image->h;

  
  for(int x = 0; x < width;x++) //Histo of Columns
    {
      int sum = 0;
      for(int y = 0; y < height; y++)
	{
	  Uint32 pixel = get_pixel(image,x,y);

	  Uint8 r,g,b;
	  SDL_GetRGB(pixel, image->format, &r,&g,&b);

	  if(r + g + b < 500)
	      sum++;
	}
      if(sum > (width / 2.5)) //Detection cols
	{
	  for(int y = 0; y < height; y++)//Set line in red
	    {
	      Uint32 pixel = 0xFF0000FF;
	      put_pixel(image, x, y, pixel);
	    }
	  hCols[x] = sum;
	}
      else
	hCols[x] = 0;
    }

  for(int y = 0; y < height;y++) //Histo of Rows
    {
      int sum = 0;
      for(int x = 0; x < width; x++)
	{
	  Uint32 pixel = get_pixel(image,x,y);

	  Uint8 r,g,b;
	  SDL_GetRGB(pixel, image->format, &r,&g,&b);

	  if(r + g + b < 500)
	      sum++;
	}
      if(sum > (height / 2.5)) //Detection rows
	{
	  for(int x = 0; x < width; x++)//Set line in red
	    {
	      Uint32 pixel = 0xFF0000FF;
	      put_pixel(image, x, y, pixel);
	    }
	  hRows[y] = sum;
	}
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

void reSize(int wCase, int hCase, int x, int y)
    {

      finalGrid = SDL_CreateRGBSurface(0,wCase,hCase,32,0,0,0,0);

      int _x = x;
      int _y = y;
      
      
      for(int i = 0; i < wCase; i++)
	{
	for(int j = 0; j < hCase; j++)
	  {
	    //printf(" i:%u j:%u x:%u y:%u \n",i,j,_x,_y);
	    
	    Uint32 pixel = get_pixel(image_surface, _x, _y);
	    
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
  Find(hCols, width, paraListCols);
  Find(hRows, height, paraListRows);

  printf("%u %u \n", paraListCols[0], paraListCols[1]);
  printf("%u %u \n", paraListRows[0], paraListRows[1]);
 
  reSize(paraListCols[1], paraListRows[1], paraListCols[0], paraListRows[0]);

  SDL_SaveBMP(finalGrid, "grid.jpg");
  
  return image;
}



int main()
{

    // TODO: Initialize the SDL

    void init_sdl()
    {
      // Init only the video part.
      // If it fails, die with an error message.
      if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
    }

    init_sdl();

    
    SDL_Surface* load_image(char *path)
    {
      SDL_Surface *img;

      // Load an image using SDL_image with format detection.
      // If it fails, die with an error message.
      img = IMG_Load(path);
      if (!img)
        errx(3, "can't load %s: %s \n", path, IMG_GetError());

      return img;
    }

    
    SDL_Surface* display_image(SDL_Surface *img)
    {
      SDL_Surface *screen;

      // Set the window to the same size as the image
      screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
      if (screen == NULL)
	{
	  // error management
	  errx(1, "Couldn't set %dx%d video mode: %s\n",
	       img->w, img->h, SDL_GetError());
	}

      // Blit onto the screen surface
      if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

      // Update the screen
      SDL_UpdateRect(screen, 0, 0, img->w, img->h);

      // return the screen for further uses
      return screen;
    }
    
    // TODO: Wait for a key to be pressed.
    void wait_for_keypressed()
    {
      SDL_Event event;

      // Wait for a key to be down.
      do
	{
	  SDL_PollEvent(&event);
	} while(event.type != SDL_KEYDOWN);

      // Wait for a key to be up.
      do
	{
	  SDL_PollEvent(&event);
	} while(event.type != SDL_KEYUP);
    }
    
    
    void SDL_FreeSurface(SDL_Surface *surface);
    

    
    image_surface = load_image("image_02_bin2.jpg");
    screen_surface = image_surface;

    display_image(image_surface);
    display_image(screen_surface);

    wait_for_keypressed();

    
    GridDetect(image_surface);

    display_image(image_surface);
    display_image(screen_surface);

    wait_for_keypressed();

    display_image(finalGrid);

    wait_for_keypressed();

    
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);

      


    return 0;
}
