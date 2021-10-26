

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
        bool Walkable = true;
        int foodAmount = 0;
        sf::RectangleShape shape;

        float toFoodAngle;
        float toHomeAngle;
        bool pherHome = false;
        bool pherFood = false;
        int pherHomeAmount = 0;
        int pherFoodAmount = 0;

        //sf::Clock clock;
        sf::Time time;
};

#endif