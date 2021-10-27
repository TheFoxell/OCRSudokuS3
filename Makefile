# Makefile

CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -O2 `pkg-config --cflags sdl`
LDFLAGS =
LDLIBS = -lm `pkg-config --libs sdl` -lSDL -lSDL_image

SRC = main.c NeuralNetwork/XOR.c NeuralNetwork/Matrix.c solver/draw.c solver/parseur.c solver/solver.c solver/pixel_operations.c GridCutout/gridcut.c GridCutout/griddetect.c simpleblackandwhite/gray.c rotation/rotation.c

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
