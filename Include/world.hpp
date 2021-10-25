#ifndef WORLD_HPP
#define WORLD_HPP

#include "tile.hpp"
#include "ant.hpp"

const int width = 256;//1024;
const int height = 192;//768;
const int tileSize = 4;
const int antSize = 1;

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
        sf::CircleShape nest;

        World();
        void simulate();
        void draw(sf::RenderWindow &window);

        void antSimulate();
        void pherSimulate();
        float antReverse(float angle);
        void buildWalls(sf::Vector2i pos);
/*         void antNextSpot();
        void antMove(); */
};

#endif