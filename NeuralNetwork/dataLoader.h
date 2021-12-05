#include "config.h"
#include "pixel_operations.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>


typedef struct Image_{
    uint8_t pixels[IMAGE_SIZE];
} Image;

typedef struct ImageFileHeader_{
    uint32_t magicNumber;
    uint32_t maxImages;
    uint32_t imgWidth;
    uint32_t imgHeight;
} ImageFileHeader;

typedef struct LabelFileHeader_{
    uint32_t magicNumber;
    uint32_t maxLabels;
} LabelFileHeader;

void getImage(FILE *imageFile, Image* img);
uint8_t getLabel(FILE *labelFile);
FILE* openImageFile(char *fileName, ImageFileHeader* imageFileHeader);
FILE* openLabelFile(char *fileName);
SDL_Surface* load_image(char *path);
Image* putPixels(char *path, Image* img);
uint8_t getPixels(Image* img, int i);
