#include "DigitRecognition.h"

int main(int argc, char** argv)
{
	uint8_t matrix[9][9];
	DigitRecognition(strtol(argv[1], NULL, 10), matrix);
	return 0;
}