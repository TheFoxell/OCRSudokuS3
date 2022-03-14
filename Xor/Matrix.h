#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Matrix object declaration
struct Matrix
{
        // Size of the matrix
        int rows;
        int columns;

        // Pointer to the matrix
        double *mat;
};

// Create a matrix; return the matrix
struct Matrix CreateMatrix(int rows, int colums);

// Function to change a value in a matrix
void ChangeMatrix(struct Matrix matrix, int x, int y, float val);

// Function to navigate in the matrix; return matrix(x, y)
double NavMatrix(struct Matrix matrix, int x, int y);

void InitMatrix(struct Matrix matrix);

void InitMatrixZero(struct Matrix matrix);

// Print the matrix
void PrintMatrix(struct Matrix matrix);

double Random();

#endif
