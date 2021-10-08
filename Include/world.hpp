#ifndef WORLD_HPP
#define WORLD_HPP

#include "tile.hpp"
#include "ant.hpp"

const int width = 256;//1024;
const int height = 192;//768;
const int tileSize = 4;
const int antSize = 50;

/*-----------------------------------------------------------------------------
** THIS IS A WORLD CLASS CLASS
**---------------------------------------------------------------------------*/
class World
{
    public:
        Tile grid[width][height];
        //int colony[1] = {0};
        sf::Vector2f colPos;
        Ant ant[antSize];

        World();
        void simulate();
        void draw(sf::RenderWindow &window);

        void antSimulate();
        float antReverse(float angle);
/*         void antNextSpot();
        void antMove(); */
};

#endif