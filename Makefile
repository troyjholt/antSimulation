all:
	g++ -g -O3 -c -I ./Include ./Source/*.cpp
	g++ main.o world.o ant.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
clean:
	rm -rf sfml-app *.o