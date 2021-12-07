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
#include "../rotationAuto/rotationAuto.h"
#include "../solver/solver.h"
//#include "../NeuralNetwork/DigitRecognition.h"

void Run(char filename[])
{

  init_sdl();

  //SDL_Surface* image = load_image(filename);

  grayscale(filename); //Binarisation image

  
  RotAndCut("image_bin.jpg",-1);
  
  //int mat[9][9] = RecognizeDigit("Cases");

  typedef int Matrice[9][9];

  Matrice mat2 =
    {
     {0,2,0,0,0,0,6,0,9},
     {8,5,7,0,6,4,2,0,0},
     {0,9,0,0,0,1,0,0,0},
     {0,1,0,6,5,0,3,0,0},
     {0,0,8,1,0,3,5,0,0},
     {0,0,3,0,2,9,0,8,0},
     {0,0,0,4,0,0,0,6,0},
     {0,0,2,8,7,0,1,3,5},
     {1,0,6,0,0,0,0,2,0},
    };
    
  /*
    if(!solve(mat2, 0,0))
    {
    RotAndCut("image_bin.jpg",1);
    mat = RecognizeDigit("Cases")
    }
  */
  
  solve(mat2);

  drawSudoku(mat2,"SudokuSolve",5);
  
  
}
