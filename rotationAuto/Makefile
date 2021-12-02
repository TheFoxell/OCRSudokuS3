# Makefile

CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -O2 `pkg-config --cflags sdl`
LDFLAGS =
LDLIBS = -lm `pkg-config --libs sdl` -lSDL -lSDL_image

SRC = main.c ../GridCutout/gridcut.c ../GridCutout/griddetect.c ../rotation/rotation.c ../tool/tool_image.c ../tool/pixel_operations.c

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
