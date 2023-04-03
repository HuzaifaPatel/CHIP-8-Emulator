all: chip.o screen.o
	g++ -o main screen.o chip8.o -lSDL2

chip.o:
	gcc -c chip8


clean:
	rm *.o main