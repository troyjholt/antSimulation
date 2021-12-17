

#ifndef TILE_HPP
#define TILE_HPP
#include <iostream>
#include <SFML/Graphics.hpp>
/*-----------------------------------------------------------------------------
** THIS IS A TILE CLASS
**---------------------------------------------------------------------------*/
class Tile
{
    public:
        int type = 0;
        bool hasFood = false;
        int foodAmount = 0;

        int arrayPos;

        float toFoodAngle;
        float toHomeAngle;
        bool pherHome = false;
        bool pherFood = false;
        int pherHomeAmount = 0;
        int pherFoodAmount = 0;
        bool vision = false;

        //sf::Clock clock;
        sf::Time time;
};

#endif