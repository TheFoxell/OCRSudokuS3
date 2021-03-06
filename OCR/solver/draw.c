#include "stdio.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "err.h"
#include "../tool/tool_image.h"

SDL_Surface* image_surface;
SDL_Surface* screen_surface;

int numbers[10][7]=
{
	{//0
	14, 17, 19, 21, 25, 17, 14
	},
	{//1
	4, 12, 4, 4, 4, 4, 14	
	},
	{//2
	14, 17, 1, 2, 4, 8, 31
	},
	{//3
	31, 2, 4, 2, 1, 17, 14
	},
	{//4
	2, 6, 10, 18, 31, 2, 2
	},
	{//5
	31, 16, 30, 1, 1, 17, 14
	},
	{//6
	6, 8, 16, 30, 17, 17, 14
	},
	{//7
	31, 1, 2, 4, 8, 8, 8
	},
	{//8 
	14, 17, 17, 14, 17, 17, 14
	},
	{//9
	14, 17, 17, 15, 1, 2, 12
	}
};




void menu(char filename[])
{
	SDL_Event event;
	int continu = 1;
	while(continu)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				continu=0;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case(SDLK_s):
						SDL_SaveBMP(image_surface,filename);
						break;
					case(SDLK_q):
						continu=0;
						break;
					default:
						break;
				}
				do
				{
					SDL_PollEvent(&event);
				} while(event.type != SDL_KEYUP);
				break;
		}

	}

}

void drawSquare(SDL_Surface *img, size_t size, size_t x, size_t y);

void drawGrid(SDL_Surface *img,size_t size)
{
	//size_t width = img->w;
	//size_t depth =img->h;
	for(size_t i =0;i<4 ;i++)
		for(size_t j =0;j<95*size ;j++)
		{
			drawSquare(img, size*2, j,(31*i)*size);
			drawSquare(img, size*2, (31*i)*size,j);
		}
	for(size_t x=0;x<3;x++)
		for(size_t i =0;i<2 ;i++)
                	for(size_t j =0;j<95*size ;j++)
			{
				drawSquare(img, size, j,(31*x+11+10*i)*size);
                        	drawSquare(img, size, (31*x+11+10*i)*size,j);
			}
}

void drawNumber(SDL_Surface *img,size_t size ,size_t index,size_t x, size_t y)
{
	for(size_t i=0;i<7;i++)
	{
		for(size_t j=0;j<5;j++)
		{

			if((numbers[index][i]>>(4-j))&1)
			{
				drawSquare(img, size, x+j*size,y+i*size);
				//put_pixel(img, j+x, i+y, SDL_MapRGB(img->format,255,255,255));
			}
		}
	}
}

void drawSquare(SDL_Surface *img, size_t size, size_t x, size_t y)
{
	size_t width = img->w;
        size_t depth =img->h;
	for(size_t i=0; i<size && i+y<width;i++)
		for(size_t j=0; j<size && j+x<depth; j++)
		{
			put_pixel(img, j+x, i+y, SDL_MapRGB(img->format,255,255,255));
		}
}

void drawSudoku(int grid[9][9], char filename[],size_t size)
{

        init_sdl();
	image_surface = create_image(95*size,95*size);
        drawGrid(image_surface,size);

	
	for(size_t i =0; i<9;i++)
		for(size_t j =0; j<9;j++)
                	drawNumber(image_surface,size,grid[j][i],(4+i/3+i*10)*size,(3+j/3+j*10)*size);
	// Display the image.
        screen_surface=display_image(image_surface);
    // Wait for a key to be pressed.
	
	menu(filename);
        //wait_for_keypressed();
        //SDL_SaveBMP(image_surface,filename);
    	//IMG_SavePNG(image_surface, "out.png");
	// Free the image surface.
        SDL_FreeSurface(image_surface);
    // Free the screen surface.
        SDL_FreeSurface(screen_surface);
}

