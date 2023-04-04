all: chip.o screen.o
	g++ -o main screen.o chip8.o -lSDL2

chip.o: chip8.hpp screen.hpp
	gcc -c chip8.cpp -lSDL2

screen.o: screen.hpp
	gcc -c screen.cpp -lSDL2

clean:
	rm -f *.o main