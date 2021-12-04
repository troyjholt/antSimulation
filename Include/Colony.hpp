#pragma once

#include "Game.hpp"
//#include "GameState.hpp"
//#include "State.hpp"
#include "Ant.hpp"
#include "tile.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Colony
{
    public:
        Colony(GameDataRef data, int ID);

        void drawColony();
        void colonySimulate(float dt);
        
        int id;
        int colSize = COLONY_START_SIZE;

    private:
        GameDataRef _data;

        int range = 8; // distance of ants view range.
        int rangeWidth = 45; // width of ants view range.
        int foodReturned = 0;
        int carryCapacity = 1;
        int speed = ANT_DEFAULT_SPEED;

        std::vector<Ant *> _ants;
        Ant *ant;
        sf::Vector2f colPos;

        Tile grid[WIDTH * HEIGHT];

        sf::Texture antTexture;
        sf::Texture antFoodTexture;

        //void antSimulate(sf::Time elapsed);
        //void pherSimulate(sf::Time elapsed);
        float findAngle(Ant &A);
        float antReverse(float angle);
        float antBounce(Ant &A, int X, int Y);
};