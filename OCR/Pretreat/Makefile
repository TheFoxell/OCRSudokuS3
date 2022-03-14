# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl SDL_image`

all: display grayscale

display: display.o
grayscale: ../tool/pixel_operations.o ../tool/tool_image.o grayscale.o tresholding.o

grayscale.o: ../tool/pixel_operations.h ../tool/tool_image.h tresholding.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} display
	${RM} grayscale

# END
