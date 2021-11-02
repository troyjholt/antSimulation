#ifndef WORLD_HPP
#define WORLD_HPP

#include "tile.hpp"
#include "ant.hpp"
#include <SFML/System/Vector2.hpp>

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
        sf::CircleShape nest;

        World();
        void simulate(sf::Time elapsed);
        void draw(sf::RenderWindow &window);

        void antSimulate(sf::Time elapsed);
        void pherSimulate(sf::Time elapsed);
        float antReverse(float angle);
        float averageFoodAngle(int x, int y);
        float averageHomeAngle(int x, int y);
        void determineSpot(float angle, Ant &A);
        bool pherCheck(sf::Vector2f pos, bool food);
        void buildWalls(sf::Vector2i pos, int brushSize);
        void buildFood(sf::Vector2i pos, int brushSize);
        void buildErase(sf::Vector2i pos, int brushSize);
/*         void antNextSpot();
        void antMove(); */
};

#endif