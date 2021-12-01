all:
	g++ -g -c -I ./Include ./Source/*.cpp
	g++ -g main.o Game.o world.o ant.o Colony.o TextureHolder.o -o sfml-app  -lsfml-graphics -lsfml-window -lsfml-system
clean:
	rm -rf sfml-app *.o