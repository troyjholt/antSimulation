#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include "Colony.hpp"
#include "world.hpp"
#include "TileMap.cpp"
#include "TextureHolder.hpp"

const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);



class Game
{
    public:Game();
        void             run();
    
    public:
        int maxSize = 20;
        int smallSize = 1;
        int brushSize = 10;
        bool start = false;
        bool bWall = false;
        bool bFood = false;
        bool bErase = false;

    private:
        void             processEvents();
        void             update(sf::Time deltaTime);
        void             handleMouseInput(sf::Event::MouseButtonEvent b, bool isPressed);
        void             handleKeyboardInput(sf::Keyboard::Key key, bool isPressed);
        void             render();

    private:
        sf::RenderWindow mWindow;
        //sf::CircleShape  mPlayer;
};

#endif
