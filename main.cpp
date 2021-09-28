#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "ant.hpp"
#include "colony.hpp"
#include "food.hpp"
#include "world.hpp"

//using namespace sf;

const int TILE_NUMBER_X = 540;
const int TILE_NUMBER_Y = 960;
const int SIZE = 2;
int spot = 1;
bool start = false;

int main(int argc, char *argv[])
{
    srand (time(NULL));
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    Colony* colony = new Colony();
    Food food;
    World* world = new World();

    sf::RectangleShape ants[colony->size];
    //sf::CircleShape antHill(10);
    sf::RectangleShape foodRender;
    //antHill.setFillColor(sf::Color(100,250,50));
    //antHill.setPosition(colony->antHill[0], colony->antHill[1]);

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time elapsed = clock.getElapsedTime();
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseButtonPressed)
            {    
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    //std::cout << "left button" << std::endl;
                    sf::Vector2i pos = sf::Mouse::getPosition(window);
                    world->getType(pos.x, pos.y);
                    std::cout << pos.x << ' ' << pos.y << std::endl;
                }
            }
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

        if((elapsed.asSeconds() > 0.01) && start)
        {
            window.clear();
            world->render(window);
            colony->simulate(*world);
            colony->render(window);
            
            for(int i = 0; i < colony->size;i++)
            {
                float * pos = colony->getPosition(i);
                //std::cout << i << " = " << pos[0] << " " << pos[1] << std::endl;
                ants[i].setSize(sf::Vector2f(colony->antSize(i), colony->antSize(i)));
                ants[i].setPosition(pos[0], pos[1]);
                ants[i].setFillColor(sf::Color(100,250,50));
                window.draw(ants[i]);
                //window.draw(antHill);
            }

            elapsed = clock.restart();
        }


        window.display();
    }

    return 0;
}