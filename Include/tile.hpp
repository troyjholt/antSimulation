

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
};

#endif