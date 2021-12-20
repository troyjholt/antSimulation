#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "DEFINITIONS.hpp"
#include "Colony.hpp"
#include "Food.hpp"
#include "AntRenderer.hpp"
//#include "FoodRenderer.hpp"
//#include "PheromoneRenderer.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>





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
        //int _level[WIDTH * HEIGHT];

        TileMap _map;
        AntRenderer _ar;
        //FoodRenderer _fr;
        

        std::vector<Colony *> _colony;
        //FoodData _food = std::make_shared<std::vector<Food>>();

        //Food food;
        Colony *colony;

        

        bool _start = false;
};