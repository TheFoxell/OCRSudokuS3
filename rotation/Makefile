# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS= -lm
LDLIBS= `pkg-config --libs sdl SDL_image` -lm

all: main

main: pixel_operations.c rotation.c


clean:
	${RM} *.o
	${RM} *.d
	${RM} main

# END
