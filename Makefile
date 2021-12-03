all:
	g++ -g -c -I ./Include ./Source/*.cpp
	g++ -g main.o Game.o world.o ant.o Colony.o StateMachine.o AssetManager.o GameState.o CreateState.o MapChoiceState.o InputManager.o SplashState.o MainMenuState.o -o sfml-app  -lsfml-graphics -lsfml-window -lsfml-system
clean:
	rm -rf sfml-app *.o