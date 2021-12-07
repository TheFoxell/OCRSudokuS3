all: main

main: 
	gcc -o nn.out main.c DigitRecognition.c nn.c dataLoader.c pixel_operations.c -lSDL_image -lSDL -lm -lSDL_gfx

.PHONY: clean

clean:
	${RM} ${OBJ}   # remove object files
	${RM} ${DEP}   # remove dependency files
	${RM} nn.out     # remove main program
