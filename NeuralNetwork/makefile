all: main

main: 
	gcc -o nn.out DigitRecognition.c nn.c dataLoader.c pixel_operations.c -lSDL_image -lSDL -lm

.PHONY: clean

clean:
	${RM} ${OBJ}   # remove object files
	${RM} ${DEP}   # remove dependency files
	${RM} nn.out     # remove main program
