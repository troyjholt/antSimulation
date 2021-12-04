#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "TileMap.cpp"
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>
#include <fstream>
#include <string>

class CreateState : public State
{
    public:
        CreateState(GameDataRef data);

        void Init();
        
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
    
    private:
        GameDataRef _data;
        int _level[HEIGHT * WIDTH];
        TileMap _map;
        sf::Sprite _wallButton;
        sf::Sprite _nestButton;
        sf::Sprite _foodButton;
        sf::Sprite _saveButton;

        int _brushSize = 10;
        bool _bWall = false;
        bool _bFood = false;
        bool _bNest = false;
};