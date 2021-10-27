# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl SDL_image`

all: main

main: solver.c parseur.c draw.c pixel_operations.c

draw: pixel_operations.o draw.o

draw.o: pixel_operations.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} main
	${RM} main

# END
