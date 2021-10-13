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
bool start = false;

int main(int argc, char *argv[])
{
    srand (time(NULL));
    sf::RenderWindow window(vm, "Hello World", sf::Style::Default);

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
    while (window.isOpen())
    {
        sf::Time elapsed = clock.getElapsedTime();
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::KeyPressed)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
                {
                    start = true;
                    std::cout << "yup" << std::endl;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
                {
                    
                }
            }
        }

        if((elapsed.asSeconds() > 0.05) && (start))
        {
            window.clear(sf::Color(225, 190, 160));
            world->draw(window);
            world->simulate();

            elapsed = clock.restart();
        }

        window.display();
    }

    return 0;
}