/* #include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string> */
#include "Game.hpp"
#include "DEFINITIONS.hpp"

//#include "world.hpp"
//#include "TileMap.cpp"


//#include "ant.hpp"

//#include "tile.hpp"

/* sf::Vector2f viewSize(SCREEN_WIDTH, SCREEN_HEIGHT);
sf::VideoMode vm(viewSize.x, viewSize.y);  

const int TILE_NUMBER_X = 540;
const int TILE_NUMBER_Y = 960;
const int SIZE = 2;
int spot = 1; */

//int numColonies = 1;

int main(int argc, char *argv[])
{

    Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Ant Simulation");

    return 0;
}
    /* srand (time(NULL));
    sf::RenderWindow window(vm, "Ant Simulation", sf::Style::Default);

    

    sf::RectangleShape background;
    background.setFillColor(sf::Color(225, 190, 160));
    background.setPosition(0,0);
    background.setSize(viewSize);
    

    //sf::Sprite antSprite;
    // Load sky Texture 
    //const antTexture = antTexture.loadFromFile("Assets/Graphics/ant.png"); 
        
    // Set and  Attacha Texture to Sprite 
    //antSprite.setTexture(antTexture); 
    //antSprite.setScale(0.05,0.05);

    sf::Clock clock;
    sf::Clock clockHolder;

    int level[width * height];
    int x = 0;
    int y = 0;
    //std::cout << (width * height) << std::endl;
    for(x = 0; x < width; x++)
    {
        for(y = 0; y < height; y++)
        {
            if((x == 0) || (x == (width - 1)))
            {
                level[x + width * y] = 1;
            }
            else if((y == 0) || (y == (height - 1)))
            {
                level[x + width * y] = 1;
            }
            else
            {
                level[x + width * y] = 0;
            }
        }
    }

    World* world = new World(numColonies, level, true);//colony);

    TileMap map;
    if (!map.load("Assets/Graphics/tileMap.png", sf::Vector2u(tileSize, tileSize), level, width, height))
            return -1;


    sf::Clock C;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    
    int fps = 0;
    sf::Text fps_text;
    sf::Text ant_text;
    sf::Font fps_font;
    if(!fps_font.loadFromFile("Assets/Fonts/Yagora.ttf"));

    fps_text.setFont(fps_font);
    ant_text.setFont(fps_font);
    fps_text.setCharacterSize(20);
    ant_text.setCharacterSize(20);
    fps_text.setFillColor(sf::Color::Black);
    ant_text.setFillColor(sf::Color::Black);
    fps_text.setPosition(10.0f, 10.0f);
    ant_text.setPosition(10.0f, 40.0f);
    
    while (window.isOpen())
    {
        sf::Time deltaTime = C.restart();
        sf::Time elapsed = clock.getElapsedTime();
        
        
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i pos = sf::Mouse::getPosition(window);

                if((pos.x >= 0) && ((pos.x/tileSize) <= (width * tileSize)) && (pos.y >= 0) && ((pos.y/tileSize) <= (height * tileSize)))
                {
                    //std::cout << (pos.x / tileSize) << " " << (pos.y/tileSize) << " " << (pos.x + width * pos.y) << std::endl;
                    int x = brushSize * -1;
                    for(x; x < brushSize; x++)
                    {
                        y = brushSize * -1;
                        for(y; y < brushSize; y++)
                        {
                            if((((pos.x + x) >= 0) && ((pos.y + y) >= 0)) && ((pos.x + x)/tileSize < width) && ((pos.y + y)/tileSize < height))
                            {
                                if(bWall)
                                {
                                    level[((pos.x + x)/tileSize) + width * ((pos.y + y)/tileSize)] = 1;
                                    //world->buildWalls(pos, brushSize);
                                }
                                else if(bFood)
                                {
                                    level[((pos.x + x)/tileSize) + width * ((pos.y + y)/tileSize)] = 2;
                                    //world->buildFood(pos, brushSize);
                                }
                                else if(bErase)
                                {
                                    level[((pos.x + x)/tileSize) + width * ((pos.y + y)/tileSize)] = 0;
                                    //world->buildErase(pos, brushSize);
                                }
                            }
                        }
                    }

                    map.load("Assets/Graphics/tileMap.png", sf::Vector2u(tileSize, tileSize), level, width, height);
                    world->updateLevel(level);
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
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
                {
                    world->sightDraw();
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
                {
                    world->pherDraw();
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
                {
                    world->print();
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

        sf::Time efficiencyA = clock.getElapsedTime();
        window.clear(sf::Color(225, 190, 160));
        sf::Time efficiencyB = clock.getElapsedTime();
        //std::cout << "window.clear took " << (efficiencyB.asMicroseconds() - efficiencyA.asMicroseconds()) << std::endl;
        
        if(start)//((elapsed.asSeconds() > 0.05) && (start))
        {
            sf::Time timeHolder = clockHolder.getElapsedTime();
            //world->draw(window);
            efficiencyA = clock.getElapsedTime();
            world->simulate(timeHolder);
            sf::Time efficiencyB = clock.getElapsedTime();
            //std::cout << "world->simulate() took " << (efficiencyB.asMicroseconds() - efficiencyA.asMicroseconds()) << std::endl;
            fps = (1 / C.restart().asSeconds());
            elapsed = clock.restart();
        }
        
        efficiencyA = clock.getElapsedTime();
        
        window.draw(map);
        efficiencyB = clock.getElapsedTime();
        //std::cout << "window.draw(map) took " << (efficiencyB.asMicroseconds() - efficiencyA.asMicroseconds()) << std::endl;
        
        efficiencyA = clock.getElapsedTime();
        world->draw(window, clock);
        efficiencyB = clock.getElapsedTime();
        //std::cout << "Ant drawing took " << (efficiencyB.asMicroseconds() - efficiencyA.asMicroseconds()) << std::endl;
        
        fps_text.setString("FPS: " + std::to_string(fps));
        ant_text.setString("ANTS: " + std::to_string(world->colonies[0].colSize));
        window.draw(fps_text);
        window.draw(ant_text);
        window.display();
        
    } */

