all:
	g++ -pg -c -I ./Include ./Source/*.cpp
	g++ -pg main.o Game.o StateMachine.o AssetManager.o GameState.o CreateState.o MapChoiceState.o InputManager.o SplashState.o MainMenuState.o Colony.o Ant.o Food.o AntRenderer.o PheromoneRenderer.o -o sfml-app  -lsfml-graphics -lsfml-window -lsfml-system
clean:
	rm -rf sfml-app *.o