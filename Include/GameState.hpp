#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include <iostream>
#include <fstream>
#include <string>

class GameState : public State
{
    public:
        GameState(GameDataRef data);

        void Init();
        
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
    
    private:
        GameDataRef _data;
        
        //sf::Texture _backgroundTexture;
        //sf::Sprite _background;
        int _level[height * width];
        TileMap _map;

};