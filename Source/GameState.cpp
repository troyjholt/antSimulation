#include <sstream>
#include "GameState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

GameState::GameState( GameDataRef data ) : _data( data )
{

}

void GameState::Init()
{
    std::ifstream readFile;
    readFile.open(this->_data->level);
    if(readFile.is_open())
    {
        for(int x = 0; x < width; x++)
        {
            for(int y = 0; y < height; y++)
            {
                _level[x + width * y] = readFile.get() - '0';
            }
        }
    }
    
    readFile.close();

    if (!_map.load("Assets/Graphics/tileMap.png", sf::Vector2u(tileSize, tileSize), _level, width, height))
        return;
}


void GameState::HandleInput()
{
    sf::Event event;

    while(this->_data->window.pollEvent(event))
    {
        if(sf::Event::Closed == event.type)
        {
            this->_data->window.close();
        }
    }
}

void GameState::Update( float dt )
{

}

void GameState::Draw(float dt)
{
    this->_data->window.clear();
    this->_data->window.draw(_map);
    this->_data->window.display();
}