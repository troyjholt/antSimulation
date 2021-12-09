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
        void pheromoneSimulate(float dt);
        
        int id;
        int colSize = COLONY_START_SIZE;

        std::vector<Ant *> _ants; // list of colony ants
        Ant *ant;

    private:
        GameDataRef _data;

        int range = 30; // distance of ants view range.
        int rangeWidth = 45; // width of ants view range.
        int foodReturned = 0; // keeps track of food returned to spawn new ant.
        int carryCapacity = 1; // colonies carrying capacity
        float speed = ANT_DEFAULT_SPEED; // speed that colony ants can move.
        float pherDisolveSpeed = PHEROMONE_DEFAULT_DISSOLVE;


        sf::Vector2f colPos;

        Tile grid[WIDTH * HEIGHT];

        sf::Texture antTexture;
        sf::Texture antFoodTexture;

        sf::Sprite nest;
        sf::Texture nestTexture;

        //void antSimulate(sf::Time elapsed);
        //void pherSimulate(sf::Time elapsed);
        float findAngle(Ant &A);
        float antReverse(float angle);
        float antBounce(Ant &A, int X, int Y);
};