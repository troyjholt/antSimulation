#ifndef WORLD_HPP
#define WORLD_HPP

#include "tile.hpp"
#include "ant.hpp"
#include "Colony.hpp"
#include "DEFINITIONS.hpp"
#include <cmath>

//const int width = 256;//1024;
//const int height = 192;//768;
//const int tileSize = 4;
const float wTime = 5.0; //15.0
const int maxColonies = 5; // max allowed colonies per

/*-----------------------------------------------------------------------------
** THIS IS A WORLD CLASS CLASS
**---------------------------------------------------------------------------*/
class World
{
    public:
        //Colony * colonies;
        int numCol;
        
        //sf::CircleShape nest;
        int range; // distance of ants view range.
        int rangeWidth; // width of ants view range. 
        int foodReturned = 0;
        bool sightD = false; // shows ants vision to user
        bool showPher = true; // shows pheromones to user
        int antSize = 1;
        World(int numColonies, int level[], bool randStart);
        void simulate(sf::Time elapsed);
        void updateLevel(int level[HEIGHT * WIDTH]);
        void print();
        void draw(sf::RenderWindow &window, sf::Clock &clock);

        void antSimulate(sf::Time elapsed);
        void pherSimulate(sf::Time elapsed);
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