#include "dataLoader.h"
#include <stdlib.h>

static void readImageFileHeader(FILE *imageFile, ImageFileHeader *ifh);
static void readLabelFileHeader(FILE *imageFile, LabelFileHeader *lfh);
static uint32_t flipBytes(uint32_t n);

void getImage(FILE *imageFile, Image* img){
    size_t result;
    result = fread(img, sizeof(*img), 1, imageFile);
    if(result!=1){
        printf("\nError when reading IMAGE file! Abort!\n");
        exit(1);
    }
}

uint8_t getLabel(FILE *labelFile){
    uint8_t label;
    size_t result;
    result = fread(&label, sizeof(uint8_t), 1, labelFile);
    if(result!=1){
        printf("\nError when reading LABEL file! Abort!\n");
        exit(1);
    }

    return label;
}

FILE* openImageFile(char *fileName, ImageFileHeader* imageFileHeader){
    FILE* imageFile;
    imageFile = fopen (fileName, "rb");
    if(imageFile == NULL){
        printf("Abort! Could not find MNIST IMAGE file: %s\n",fileName);
        exit(0);
    }

    readImageFileHeader(imageFile, imageFileHeader);
    return imageFile;
}

FILE* openLabelFile(char *fileName){
    FILE *labelFile;
    labelFile = fopen (fileName, "rb");
    if(labelFile == NULL){
        printf("Abort! Could not find MNIST LABEL file: %s\n",fileName);
        exit(0);
    }

    LabelFileHeader labelFileHeader;
    readLabelFileHeader(labelFile, &labelFileHeader);
    return labelFile;
}

static void readImageFileHeader(FILE *imageFile, ImageFileHeader *ifh){
    ifh->magicNumber =0;
    ifh->maxImages   =0;
    ifh->imgWidth    =0;
    ifh->imgHeight   =0;

    fread(&ifh->magicNumber, 4, 1, imageFile);
    ifh->magicNumber = flipBytes(ifh->magicNumber);

    fread(&ifh->maxImages, 4, 1, imageFile);
    ifh->maxImages = flipBytes(ifh->maxImages);

    fread(&ifh->imgWidth, 4, 1, imageFile);
    ifh->imgWidth = flipBytes(ifh->imgWidth);

    fread(&ifh->imgHeight, 4, 1, imageFile);
    ifh->imgHeight = flipBytes(ifh->imgHeight);
}

static void readLabelFileHeader(FILE *imageFile, LabelFileHeader *lfh){
    lfh->magicNumber = 0;
    lfh->maxLabels = 0;

    fread(&lfh->magicNumber, 4, 1, imageFile);
    lfh->magicNumber = flipBytes(lfh->magicNumber);

    fread(&lfh->maxLabels, 4, 1, imageFile);
    lfh->maxLabels = flipBytes(lfh->maxLabels);
}

static uint32_t flipBytes(uint32_t n){
    uint32_t b0,b1,b2,b3;

    b0 = (n & 0x000000ff) <<  24u;
    b1 = (n & 0x0000ff00) <<   8u;
    b2 = (n & 0x00ff0000) >>   8u;
    b3 = (n & 0xff000000) >>  24u;

    return (b0 | b1 | b2 | b3);
}

SDL_Surface* load_image(char *path)
{
    SDL_Surface *img;

    // Load an image using SDL_image with format detection.
    // If it fails, die with an error message.
    img = IMG_Load(path);
    if (!img)
        errx(3, "can't load %s: %s", path, IMG_GetError());

    return img;
}

Image* putPixels(char *path, Image* img)
{
    
    SDL_Surface* ImgSurface = load_image(path);
    
    double zoomx = 28  / (float)ImgSurface->w;
    double zoomy = 28 / (float)ImgSurface->h;
    
    SDL_Surface* sized = zoomSurface( ImgSurface, zoomx, zoomy, SMOOTHING_OFF );
    
    
    int i = 0;
    for (unsigned c = 0; c < 28; c++)
    {
    	for (unsigned l = 0; l < 28; l++)
    	{
    	    //Invert white and black
    	    /*Uint32 pixel = get_pixel(sized, l, c);
    	    Uint8 r, g, b;
    	    SDL_GetRGB(pixel, sized->format, &r, &g, &b);
	    if(r + g + b < 500)
	    {
	    	if (c <=5 || l <=5)
	    	{
	    		pixel = SDL_MapRGB(sized->format, 0, 0, 0);
	    		put_pixel(sized, l, c, pixel);
	    	}
	    	else
	    	{
	    		pixel = SDL_MapRGB(sized->format, 255, 255, 255);
	    		put_pixel(sized, l, c, pixel);
	    	}
	    }
	    else
	    {
	    	pixel = SDL_MapRGB(sized->format, 0, 0, 0);
	    	put_pixel(sized, l, c, pixel);
	    }*/
	    
	    
    	    img->pixels[i] = get_pixel(sized, l, c);
    	    i ++;
    	}
    }
    
    //SDL_SaveBMP(sized, "image");
    
    return img;
}

uint8_t getPixels(Image* img, int i)
{
    return img->pixels[i];
}
