#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
//#include "Colony.hpp"
//#include "world.hpp"
#include "TileMap.cpp"
//#include "AntRenderer.hpp"
#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"

#include "Food.hpp"
//#include "Food.hpp"
//#include "SplashState.hpp"


struct GameData
{
    StateMachine machine;
    sf::RenderWindow window;
    AssetManager assets;
    InputManager input;

    std::string level;
    std::vector<Food> food;
};

typedef std::shared_ptr<GameData> GameDataRef;

//const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

class Game
{
    public:
        Game(int width, int height, std::string title );
        
    
    public:
        int             maxSize = 20;
        int             smallSize = 1;
        int             brushSize = 10;
        bool            start = false;
        bool            bWall = false;
        bool            bFood = false;
        bool            bErase = false;

    private:
        const float     dt = 1.0f / 60.0f;
        sf::Clock       _clock;
        GameDataRef     _data = std::make_shared<GameData>();
        
        void             run();
};

#endif
