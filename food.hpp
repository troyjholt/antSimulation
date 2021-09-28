#include <iostream>
#include <SFML/Graphics.hpp>
#ifndef FOOD_HPP
#define FOOD_HPP

class Food
{
    public:
        int amount = 10;
        int position[2] = {400,400};
        int size = 5;
        sf::Color color = sf::Color(255,255,0);
        Food();
};

Food::Food()
{

}



#endif