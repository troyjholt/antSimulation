#pragma once


#include "DEFINITIONS.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

class Food
{
    public:
        Food(int X, int Y );

        sf::Sprite foodSprite;
        int posX;
        int posY;
        //int pos;
        int foodAmount = FOOD_DEFAULT_AMOUNT;

        void SpawnFood(int X, int Y);
        int RemoveFood(int carryCapacity);
        bool CheckSpot(int X, int Y);

    private:

};