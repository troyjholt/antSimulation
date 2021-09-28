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
        int size = 4;
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
        void checkSpaces(World &world, int x, int y);
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

void Ant::checkSpaces(World &world, int x, int y)
{
    Tile tile;// = world.getTile(x,y);
    int temp = 0;
    int holder = 0;
/*     if(world.getTile(x,y).type == 4)
    {
        if(hasFood)
        {
            hasFood = false;
        }
        angle = angle - 180;
        if(angle < 0)
            angle += 360;
        
        return;
    } */
    if(hasFood)
    {
        for(int i = x - 1; i <= x + 1; i++)
        {
            for(int j = y - 1; j <= y + 1; j++)
            {
                tile = world.getTile(i,j);
                if(tile.homeIntensity > 0)
                {
                    temp = temp + tile.homeAngle;
                    holder++;
                }
                if(tile.type == 4)
                {
                    if(hasFood)
                    {
                        hasFood = false;
                    }
                    angle = angle - 180;
                    if(angle < 0)
                        angle += 360;
        
                    return;
                }
            }
        }
    }
    else
    {
        for(int i = x - 1; i <= x + 1; i++)
        {
            for(int j = y - 1; j <= y + 1; j++)
            {
                tile = world.getTile(i,j);
                if(tile.foodIntensity > 0)
                {
                    temp = temp + tile.foodAngle;
                    holder++;
                }
                if(tile.type == 4)
                {
                    if(hasFood)
                    {
                        hasFood = false;
                    }
                    angle = angle - 180;
                    if(angle < 0)
                        angle += 360;
        
                    return;
                }
            }
        }
    }
    //std::cout << angle << ' ' << temp << ' ' << holder << std::endl;
    if((temp > 0) && (holder > 0))
        angle = temp / holder;
/*     if((tile.type == 2) && (tile.foodIntensity > 0) && (!hasFood))
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
    } */
}

void Ant::calcMovement(World &world)
{
    int X = (int)position[0];
    int Y = (int)position[1];
    checkSpaces(world, X, Y);

    float temp = rand() % 11 - 5;
    angle = angle + temp; 
    
    if(angle > 360)
    {
        angle -= 360;
    }
    if(angle < 0)
    {
        angle += 360;
    }

    float rad = angle / 57.2958;
    float y = speed * cos(rad);
    float x = speed * sin(rad);

    position[0] = position[0] + x;
    position[1] = position[1] + y;


    //x = position[0];
    //y = position[1];

    if(position[0] > 1919.0)
    {
        position[0] = 1919.0;
        angle = 270;
    }
    if(position[0] < 0.0)
    {
        position[0] = 0.0;
        angle = 90;
    }
    if(position[1] > 1079.0)
    {
        position[1] = 1079.0;
        angle = 180;
    }
    if(position[1] < 0.0)
    {
        position[1] = 0.0;
        angle = 0;
    }
    //setPosition(x,y);
    //position[0] = x;
    //position[1] = y;
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
    else
    {
        pheromone(world);
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
    //pheromone(world);
    //std::cout << position[0]  << " " << position[1] << std::endl;
}

#endif