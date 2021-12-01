#ifndef COLONY_HPP
#define COLONY_HPP
#include <iostream>
#include "ant.hpp"
#include "tile.hpp"
//#include <SFML/Graphics.hpp>
/*-----------------------------------------------------------------------------
** THIS IS A COLONY CLASS
**---------------------------------------------------------------------------*/
const int maxAntSize = 5000;
const int width = 256;//1024;
const int height = 192;//768;
const int tileSize = 4;
const int startSize = 50;



class Colony
{
    public:
        int id;
        int colSize = startSize;
        int range = 8; // distance of ants view range.
        int rangeWidth = 45; // width of ants view range.
        int foodReturned = 0; 
        Ant ant[maxAntSize];
        sf::Vector2f colPos;
        Tile grid[width * height];

        sf::Texture antTexture;
        sf::Texture antFoodTexture;


        void antSimulate(sf::Time elapsed);
        void pherSimulate(sf::Time elapsed);
        float findAngle(Ant A);
        float antReverse(float angle);
        float antBounce(Ant A, int X, int Y);
};

#endif