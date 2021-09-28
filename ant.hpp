#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include "world.hpp"
//#include <ctime>
//#include <vector>
#ifndef ANT_HPP
#define ANT_HPP

#define PI 3.14159265

class Ant
{
    public:
        int size = 2;
        float position[2] = {100.0f, 100.0f};
        bool hasFood = false;

        float angle = rand() % 360 + 1;
        float distance = 1.0f;
        float speed = 1.0f;

        int pheromoneTicker = 0;
        sf::RectangleShape antRender;
        
        int getSize();
        float * getPosition();
        void setPosition(int x, int y);
        void calcMovement(World &world);
        void simulate(World &world);
        void checkFood(World &world);
        void pheromone(World &world);
        Ant();
        Ant(int x, int y);
};

Ant::Ant()
{
    // do nothing
}

Ant::Ant(int x, int y)
{
    position[0] = x;
    position[1] = y;
}

int Ant::getSize()
{
    return size;
}

float * Ant::getPosition()
{
    return position;
}

void Ant::setPosition(int x, int y)
{
    //std::cout << "x = " << x << "\n" << "y = " << y << std::endl;
    position[0] = x;
    position[1] = y;
}

// 1|2|3
// 8|A|4
// 7|6|5
void Ant::calcMovement(World &world)
{
    int Y = (int)position[1];
    int X = (int)position[0];
    Tile tile = world.getTile(X,Y);
    if((tile.type == 2) && (tile.foodIntensity > 0) && (!hasFood))
    {
        angle = tile.foodAngle;
    }
    else if((tile.type == 2) && (tile.homeIntensity > 0) && (hasFood))
    {
        angle = tile.homeAngle;
    }
    else if(tile.type == 4)
    {
        if(hasFood)
        {
            hasFood = false;
        }
        angle = angle - 180;
        if(angle < 0)
            angle += 360;
    }

    float rad = angle / 57.2958;
    float y = speed * cos(rad);
    float x = speed * sin(rad);

    //std::cout << "old X = " << position[1] <<  " speed = " << speed << " cos(angle) = " << cos(angle);
    
    position[1] = position[1] + y;
    
    //std::cout << " new x = " << position[1] << std::endl;
    
    position[0] = position[0] + x;
    x = position[0];
    y = position[1];

    //std::cout << position[1] << std::endl;
    if(x > 1919.0)
    {
        x = 1919.0;
        angle = 270;
    }
    if(x < 0.0)
    {
        x = 0.0;
        angle = 90;
    }
    if(y > 1079.0)
    {
        y = 1079.0;
        angle = 180;
    }
    if(y < 0.0)
    {
        y = 0.0;
        angle = 0;
    }
    position[0] = x;
    position[1] = y;
    
    float temp = rand() % 21 - 10;
    angle = angle + temp; 
    
    if(angle > 360)
    {
        angle -= 360;
    }
    if(angle < 0)
    {
        angle += 360;
    }
}

void Ant::checkFood(World &world)
{
    int y = (int)position[1];
    int x = (int)position[0];
    int check = world.getType(x,y);
    //std::cout << check << std::endl;
    if(check == 1)
    {
        hasFood = true;
        angle = angle - 180; 
        if(angle < 0)
        {
            angle += 360;
        }
        //std::cout << "An ant has food!" << std::endl;
    }
}

void Ant::pheromone(World &world)
{
    if(pheromoneTicker == 0)
    {
            int y = (int)position[1];// / world.tileSize;
            int x = (int)position[0];// / world.tileSize;
        world.pheromone(hasFood, x, y, angle);
        pheromoneTicker = 0;
    }
    else
    {
        pheromoneTicker--;
    }
}

void Ant::simulate(World &world)
{
    calcMovement(world);
    checkFood(world);
    pheromone(world);
    //std::cout << position[0]  << " " << position[1] << std::endl;
}

#endif