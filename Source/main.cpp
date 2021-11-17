#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "world.hpp"
//#include "ant.hpp"

//#include "tile.hpp"

sf::Vector2f viewSize(1024, 768);
sf::VideoMode vm(viewSize.x, viewSize.y);  

const int TILE_NUMBER_X = 540;
const int TILE_NUMBER_Y = 960;
const int SIZE = 2;
int spot = 1;
int maxSize = 20;
int smallSize = 1;
int brushSize = 10;
bool start = false;
bool bWall = false;
bool bFood = false;
bool bErase = false;

int main(int argc, char *argv[])
{
    srand (time(NULL));
    sf::RenderWindow window(vm, "Ant Simulation", sf::Style::Default);

    World* world = new World();//colony);

    sf::RectangleShape background;
    background.setFillColor(sf::Color(225, 190, 160));
    background.setPosition(0,0);
    background.setSize(viewSize);
    
    sf::Texture antTexture; 
    sf::Sprite antSprite;
    // Load sky Texture 
    antTexture.loadFromFile("Assets/Graphics/ant.png"); 
        
    // Set and  Attacha Texture to Sprite 
    antSprite.setTexture(antTexture); 
    antSprite.setScale(0.05,0.05);

    sf::Clock clock;
    sf::Clock clockHolder;
    while (window.isOpen())
    {
        sf::Time elapsed = clock.getElapsedTime();
        
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                //std::cout << pos.x << " " << pos.y << std::endl;
/*                 if((pos.x /tileSize) > width)
                    pos.x = width * tileSize;
                if((pos.y/tileSize) > height)
                    pos.y = height * tileSize; */
                if((pos.x >= 0) && ((pos.x/tileSize) <= (width * tileSize)) && (pos.y >= 0) && ((pos.y/tileSize) <= (height * tileSize)))
                {
                    if(bWall)
                        world->buildWalls(pos, brushSize);
                    else if(bFood)
                        world->buildFood(pos, brushSize);
                    else if(bErase)
                        world->buildErase(pos, brushSize);
                }
            }

            if(event.type == sf::Event::KeyPressed)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
                {
                    if(start == false)
                    {
                        start = true;
                        std::cout << "Simulation started" << std::endl;
                    }
                    else
                    {
                        start = false;
                        std::cout << "Simulation stopped" << std::endl;
                    }
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
                {
                    if(bWall == false)
                    {
                        bWall = true;
                        bFood = false;
                        bErase = false;
                        std::cout << "Wall building Activated" << std::endl;
                    }
                    else
                    {
                        bWall = false;
                        std::cout << "Wall building Deactivated" << std::endl;
                    }
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
                {
                    if(bFood == false)
                    {
                        bFood = true;
                        bWall = false;
                        bErase = false;
                        std::cout << "Food building Activated" << std::endl;
                    }
                    else
                    {
                        bFood = false;
                        std::cout << "Food building Deactivated" << std::endl;
                    }
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
                {
                    if(bErase == false)
                    {
                        bErase = true;
                        bFood = false;
                        bWall = false;
                        std::cout << "Erase Tool Activated" << std::endl;
                    }
                    else
                    {
                        bErase = false;
                        std::cout << "Erase Tool Deactivated" << std::endl;
                    }
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::LBracket) || sf::Keyboard::isKeyPressed(sf::Keyboard::RBracket))
                {
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LBracket))
                    {
                        if(brushSize == smallSize)
                            brushSize = smallSize;
                        else
                            brushSize--;
                    }
                        
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::RBracket))
                    {
                        if(brushSize == maxSize)
                            brushSize = maxSize;
                        else
                            brushSize++;
                    }

                    std::cout << "brushSize: " << brushSize << std::endl;
                }
            }
        }

        window.clear(sf::Color(225, 190, 160));
        if((elapsed.asSeconds() > 0.05) && (start))
        {
            sf::Time timeHolder = clockHolder.getElapsedTime();
            //world->draw(window);
            world->simulate(timeHolder);

            elapsed = clock.restart();
        }
        world->draw(window);
        window.display();
    }

    return 0;
}