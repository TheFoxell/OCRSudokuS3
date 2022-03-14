# include <string.h>
# include <stdio.h>
# include <err.h>
# include <SDL.h>
# include "../tool/tool_image.h"
# include "SDL/SDL_ttf.h"
# include "../Run/run.h"

struct Button
{
	SDL_Rect rect;
	//TTF_Font *police;
	int font_size;
	float coef;
	//SDL_Surface *text;
	char label[100];
};


void draw_square(SDL_Surface* screen,int x, int y, int h, int w, int size,Uint32 color )
{
	SDL_Rect r;
        r.x=x;
        r.y=y;
        r.h=size;
        r.w=w;
	SDL_FillRect(screen, &r, color);
	r.w=size;
	r.h=h;
        SDL_FillRect(screen, &r, color);
	r.x+=w-size;
	SDL_FillRect(screen, &r, color);
	r.x-=w-size;
	r.y+=h-size;
	r.w=w;
        r.h=size;
	SDL_FillRect(screen, &r, color);
}
	

int mouse_in(SDL_Rect rect)
{
	int x, y;

	SDL_PumpEvents();  // make sure we have the latest mouse state.
	
	SDL_GetMouseState(&x, &y);
	return x>=rect.x && x<rect.x+rect.w && y>=rect.y && y<rect.y+rect.h;
	
}

void reverse_color(SDL_Surface* img, SDL_Rect rect)
{
	int width = img->w;
	int height = img->h;
	for(int i =rect.x;i<rect.x+rect.w && i<width;i++)
	{
		for(int j=rect.y;j<rect.y+rect.h && j<height;j++)
			{
				if(get_pixel(img, i, j)==0xffffff)
					put_pixel(img, i, j, 0x000000);
				else
					put_pixel(img, i, j, 0xffffff);
			}
	}
}

void write_labels(SDL_Surface *fond, SDL_Surface *text, SDL_Rect rect,int gap_x,int gap_y)
{
	rect.x+=gap_x;
        rect.y+=gap_y;
	SDL_BlitSurface(text, NULL, fond, &rect);
}



struct Button init_button(int font_size, int x, int y, char* string)
{	
	struct Button button;
	button.font_size=font_size;
	snprintf(button.label,100,"%s",string);

	TTF_Font *police = TTF_OpenFont("DisposableDroidBB.ttf", button.font_size);

	SDL_Color color;
	color.r=255;
        color.b=255;
        color.g=255;
	SDL_Surface *text = TTF_RenderText_Solid(police, string, color);

	button.coef= button.font_size/40;
	button.rect.x=x+5*button.coef;
        button.rect.y=y+20*button.coef;
        button.rect.h=text->h+10*button.coef;
        button.rect.w=text->w+40*button.coef;
	TTF_CloseFont(police);
	SDL_FreeSurface(text);
	return button;
}
void draw_button(SDL_Surface *screen, struct Button *button)
{
	SDL_Color color;
        color.r=255;
        color.b=255;
        color.g=255;
	TTF_Font *police = TTF_OpenFont("DisposableDroidBB.ttf", button->font_size);
        SDL_Surface *text = TTF_RenderText_Solid(police, button->label, color);

        draw_square(screen, button->rect.x, button->rect.y, button->rect.h, button->rect.w, 5, 0xffffff);

        write_labels(screen, text, button->rect, 20*button->coef,5*button->coef);
	TTF_CloseFont(police);
	SDL_FreeSurface(text);
}

int main(/*int argc, char **argv*/)
{
	SDL_Surface *screen_surface,/*text,*/  *fond;
	SDL_Rect rect;
	struct Button start;
	rect.x=1;
	//TTF_Font *police;
	init_sdl();

	
	if(TTF_Init() == -1)
	{
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
    		exit(EXIT_FAILURE);
	}
	SDL_Color color;
	color.r=255;
	color.b=255;
	color.g=255;

	//start=init_button();
	fond=SDL_CreateRGBSurface(0, 750, 750, 32, 0, 0, 0, 0);


	
	start=init_button(40,335,600,"START");
	start.rect.x=fond->w/2-start.rect.w/2;
	draw_button(fond, &start);


	draw_square(fond, 100, 50, 550, 550, 10, 0xffffff);	
	/*
	police = TTF_OpenFont("DisposableDroidBB.ttf", start.font_size);
	text = TTF_RenderText_Solid(police, start.label, color);

	draw_square(fond, start.rect.x, start.rect.y, start.rect.h, start.rect.w, 5,SDL_MapRGB(fond->format,255,255,255));
		
	write_labels(fond, text, start.rect, 20*start.coef,5*start.coef);
	*/
	

	SDL_Event event;
        int continuer = 1;
	int need_to_change=0;
	int back_is_black= 1;
	int a;
	screen_surface=display_image(fond);
	while (continuer)
    	{
        	SDL_WaitEvent(&event);
        	switch(event.type)
        	{
            		case SDL_QUIT:
                		continuer = 0;
                		break;
			case SDL_MOUSEBUTTONDOWN:
				a=(int)&event.button;
				if(a==SDL_BUTTON_LEFT&&mouse_in(start.rect))
					Run("my_image.jpg");
        			break;
		}
		if (mouse_in(start.rect))
		{

			if (back_is_black)
			{
				reverse_color(fond, start.rect);
				need_to_change=1;
				back_is_black=0;
			}
		
		}
		else
		{
			if (!back_is_black)
			{
				reverse_color(fond, start.rect);
				need_to_change=1;
				back_is_black=1;
			}
		}
		if (need_to_change)
		{
			screen_surface=display_image(fond);
			need_to_change=0;
		}
	
	}
    	// Free the screen surface.
	//TTF_CloseFont(police);
	TTF_Quit();
	SDL_FreeSurface(screen_surface);
	SDL_FreeSurface(fond);
    	//SDL_FreeSurface(text);
    	SDL_Quit();
	return 0;
}
