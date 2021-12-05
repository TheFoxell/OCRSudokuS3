#include <err.h>
#include <string.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../GridCutout/gridcut.h"
#include "../GridCutout/griddetect.h"
#include "../tool/pixel_operations.h"
#include "../tool/tool_image.h"
#include "../rotation/rotation.h"
#include "../simpleblackandwhite/gray.h"
#include "../rotationAuto/RotAndCut.h"
#include "../solver/solver.h"


int Run(char filename[])
{
  SDL_Surface* image;
  SDL_Surface* result;

  init_sdl();

  image = load_image(filename);
  result = image;

  grayscale(filename); //Binarisation image

  
  RotAndCut("image_bin.jpg",-1);
  
  int mat[9][9] = RecognizeDigit("Cases");
  if(!solver(mat, 0,0))
    {
      RotAndCut("image_bin.jpg",1);
      mat = RecognizeDigit("Cases")
    }

  drawSudoku(mat,"SudokuSolve",5);
  
  
}
