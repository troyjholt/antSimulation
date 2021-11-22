#ifndef WORLD_HPP
#define WORLD_HPP

#include "tile.hpp"
#include "ant.hpp"
#include <cmath>

const int width = 256;//1024;
const int height = 192;//768;
const int tileSize = 4;
const float wTime = 5.0; //15.0
const int maxAntSize = 1000;



/*-----------------------------------------------------------------------------
** THIS IS A WORLD CLASS CLASS
**---------------------------------------------------------------------------*/
class World
{
    public:
        Tile grid[width][height];
        //int colony[1] = {0};
        sf::Vector2f colPos;
        Ant ant[maxAntSize];
        sf::CircleShape nest;
        int range; // distance of ants view range.
        int rangeWidth; // width of ants view range. 
        int foodReturned = 0;
        bool sightD = false; // shows ants vision to user
        bool showPher = true; // shows pheromones to user
        int antSize = 1;
        World();
        void simulate(sf::Time elapsed);
        void draw(sf::RenderWindow &window);

        void antSimulate(sf::Time elapsed);
        void pherSimulate(sf::Time elapsed);
        float antReverse(float angle);
        float averageFoodAngle(Ant A);
        float averageHomeAngle(Ant A);
        float antBounce(Ant A, int X, int Y);
        bool pherCheck(Ant A);
        void buildWalls(sf::Vector2i pos, int brushSize);
        void buildFood(sf::Vector2i pos, int brushSize);
        void buildErase(sf::Vector2i pos, int brushSize);
        void showVision(Ant A);
        void sightDraw();
        void pherDraw(); // for seeing
/*         void antNextSpot();
        void antMove(); */
};

#endif