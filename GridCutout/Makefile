# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl SDL_image`

all: gridcut

gridcut: gridcut.o pixel_operations.o

gridcut.o: pixel_operations.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} gridcut

# END
