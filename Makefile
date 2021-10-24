 Makefile

CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -O2 `pkg-config --cflags sdl2`
LDFLAGS =
LDLIBS = -lm `pkg-config --libs sdl2` -lSDL2 -lSDL2_image

SRC = main.c GridCutout/pixel_operations.c GridDetection/pixel_operations.c NeuralNetwork/NeuralNetwork_XOR.c NeuralNetwork/Tools.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: main

main: ${OBJ}

run: all
	./main

.PHONY: clean

clean:
	${RM} ${OBJ}   # remove object files
	${RM} ${DEP}   # remove dependency files
	${RM} main     # remove main program

-include ${DEP}

# END