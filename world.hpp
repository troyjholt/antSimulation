#include <iostream>
#include <SFML/Graphics.hpp>
#ifndef WORLD_HPP
#define WORLD_HPP

const float trailSize = 0.005f;
const int tileSize = 4;
const float foodTrail = 0.005f;

class Tile
{
    public:
        sf::Color color = sf::Color(75,75,75);
        sf::RectangleShape trender;
        int type = 0;
        float homeIntensity = 0.0f;
        float foodIntensity = 0.0f;
        int amount = 0;
        float foodAngle = 0.0;
        float homeAngle = 0.0;
        void setType(int i);
        void setFoodIntensity();
        void setHomeIntensity();

};

// 1 = food
// 2 = way to home
// 3 = way to food
// 4 = home
void Tile::setType(int i)
{
    //std::cout << i << std::endl;
    if(type == 1)
    {
        amount = 20;
        type = i;
    }
    else if(type == 4)
    {
        // do nothing;
    }
    else
    {
        type = i;
    }
}

void Tile::setFoodIntensity()
{
    foodIntensity = 1.0f;
}

void Tile::setHomeIntensity()
{
    homeIntensity = 1.0f;
}

/*-----------------------------------------------------------------------------
** THIS IS A WORLD CLASS CLASS
**---------------------------------------------------------------------------*/
class World
{
    public:
        int amount = 10;
        //int tileSize = 2;
        int width = 1920 / tileSize; //960; //480;
        int height = 1080 / tileSize; //540;//270;
        int food = 0;
        sf::Color gridColor = sf::Color(75,75,75);
        sf::Color foodColor = sf::Color(255,255,0);
        sf::Color homeColor = sf::Color(0,255,0);
        Tile grid[960][540];
        //sf::RectangleShape frender[10];
        int getType(int x, int y);
        Tile getTile(int x, int y);
        void setType(int x, int y, int i);
        void pheromone(bool hasFood, int x, int y, float angle);
        void render(sf::RenderWindow &window);
        World();
};

World::World()
{
    for(int i = 0; i < 10; i++)
    {
        grid[100 + i][100].type = 1;
        for(int j = 0; j < 10; j++)
        {
            grid[i][j].type = 4;
        }
    }
}

int World::getType(int x, int y)
{
    //std::cout << x << ' ' << y << std::endl;
    return grid[x / tileSize][y / tileSize].type;
}

Tile World::getTile(int x, int y)
{
    return grid[x / tileSize][y / tileSize];
}

void World::setType(int x, int y, int i)
{
    // something here possibly
}

void World::pheromone(bool hasFood, int x, int y, float angle)
{
    angle = angle - 180;
    if(angle < 0)
    {
        angle += 360;
    }

    if(hasFood)
    {
        grid[x/tileSize][y/tileSize].setType(2);
        grid[x/tileSize][y/tileSize].setFoodIntensity();
        grid[x/tileSize][y/tileSize].foodAngle = angle;

    }
    else
    {
        grid[x/tileSize][y/tileSize].setType(2);
        grid[x/tileSize][y/tileSize].setHomeIntensity();
        grid[x/tileSize][y/tileSize].homeAngle = angle;
    }
}

void World::render(sf::RenderWindow &window)
{
    //sf::RectangleShape frender[food];
    int f = 0;
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
/*             if(grid[x][y].type == 0)
            {
                grid[x][y].trender.setFillColor(gridColor);
                grid[x][y].trender.setSize(sf::Vector2f(tileSize,tileSize));
                grid[x][y].trender.setPosition(x * tileSize, y * tileSize);
                window.draw(grid[x][y].trender);
            } */
            if(grid[x][y].type == 1)
            {
                grid[x][y].trender.setFillColor(foodColor);
                grid[x][y].trender.setSize(sf::Vector2f(tileSize,tileSize));
                grid[x][y].trender.setPosition(x * tileSize, y * tileSize);
                window.draw(grid[x][y].trender);
            }
            else if(grid[x][y].type == 4)
            {
                grid[x][y].trender.setFillColor(homeColor);
                grid[x][y].trender.setSize(sf::Vector2f(tileSize,tileSize));
                grid[x][y].trender.setPosition(x * tileSize, y * tileSize);
                window.draw(grid[x][y].trender);
            }
            else if(grid[x][y].type == 2)
            {
                
                grid[x][y].trender.setFillColor(sf::Color(255 * grid[x][y].homeIntensity,0,255 * grid[x][y].foodIntensity));
                //grid[x][y].trender.setOutlineThickness(-1.f);
                //grid[x][y].trender.setOutlineColor(sf::Color(0,0,0));
                grid[x][y].trender.setSize(sf::Vector2f(tileSize,tileSize));
                grid[x][y].trender.setPosition(x * tileSize, y * tileSize);
                //window.draw(grid[x][y].trender);
            
                //std::cout << grid[x][y].foodIntensity << std::endl;

                if((grid[x][y].homeIntensity - trailSize) >= 0.0)
                    grid[x][y].homeIntensity = grid[x][y].homeIntensity - trailSize;
                else
                    grid[x][y].homeIntensity = 0.0;

                if((grid[x][y].foodIntensity - foodTrail) >= 0.0)
                    grid[x][y].foodIntensity = grid[x][y].foodIntensity - foodTrail;
                else
                    grid[x][y].foodIntensity = 0.0;

                if((grid[x][y].homeIntensity <= 0.0) && (grid[x][y].foodIntensity <= 0.0))
                {
                        grid[x][y].homeIntensity = 0.0;
                        grid[x][y].foodIntensity = 0.0;
                        grid[x][y].setType(0);
                        //std::cout << grid[x][y].foodIntensity << std::endl;
                        //grid[x][y].homeIntensity = 0;
                        //grid[x][y].foodIntensity = 0;
                }
                window.draw(grid[x][y].trender);
                    
            }
        }
    }
}


#endif