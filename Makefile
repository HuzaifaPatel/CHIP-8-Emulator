all: chip8.o screen.o main.o
	g++ -o main screen.o chip8.o main.o -lSDL2 -g3

chip.o: chip8.hpp screen.hpp
	g++ -c chip8.cpp -lSDL2 -g3

screen.o: screen.hpp
	g++ -c screen.cpp -lSDL2 -g3

main.o: chip8.hpp screen.hpp
	g++ -c main.cpp -lSDL2 -g3

clean:
	rm -f *.o main