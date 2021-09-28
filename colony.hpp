#include <iostream>
//#include <vector>
#include <SFML/Graphics.hpp>
#include "ant.hpp"
#include "world.hpp"
#ifndef COLONY_HPP
#define COLONY_HPP

class Colony
{
    public:
        int size = 200;
        int antHill[2] = {20, 20};//{((rand() % 1080) + 1),((rand() % 1920) + 1)};
        Ant ant[200];
        //sf::RectangleShape antRender;
        int getSize();
        void simulate(World &world);
        void render(sf::RenderWindow &window);
        int antSize(int i);
        float * getPosition(int i);

        Colony();
};

Colony::Colony()
{
    for(int i = 0; i < size; i++)
    {
        ant[i].setPosition(antHill[0] + 25, antHill[1] + 25);
    }
} 

int Colony::getSize()
{
    return size;
}

int Colony::antSize(int i)
{
    return ant[i].getSize();
}

float * Colony::getPosition(int i)
{
    return ant[i].getPosition();
}

void Colony::simulate(World &world)
{
    //std::cout << antHill[0] << ' ' << antHill[1] << std::endl;
    for(int i = 0; i < size; i++)
    {
        ant[i].simulate(world);
    }
}

void Colony::render(sf::RenderWindow &window)
{
    for(int i = 0; i < size;i++)
    {
        float * pos = getPosition(i);
        //std::cout << i << " = " << pos[0] << " " << pos[1] << std::endl;
        ant[i].antRender.setSize(sf::Vector2f(antSize(i), antSize(i)));
        ant[i].antRender.setPosition(pos[0], pos[1]);
        ant[i].antRender.setFillColor(sf::Color(100,250,50));
        window.draw(ant[i].antRender);
        //window.draw(antHill);
    }
}



#endif