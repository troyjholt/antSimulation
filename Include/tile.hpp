

#ifndef TILE_HPP
#define TILE_HPP
#include <iostream>
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
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

        //float toFoodAngle;
        //float toHomeAngle;

        bool pherHome[NUM_COLONIES][1];// = false;
        bool pherFood[NUM_COLONIES][1];// = false;
        float pherHomeAmount[NUM_COLONIES][1];// = 0;
        float pherFoodAmount[NUM_COLONIES][1];// = 0;
        
        bool vision = false;

        float timeCheck = 0.0f;

        //sf::Clock clock;
        //sf::Time time;
};

#endif