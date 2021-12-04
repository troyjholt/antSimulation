#include <sstream>
#include "GameState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

GameState::GameState( GameDataRef data ) : _data( data )
{

}

void GameState::Init()
{
    this->_data->assets.LoadTexture("ANT", ANT_TEXTURE_FILEPATH);
    this->_data->assets.LoadTexture("ANT FOOD", ANT_FOOD_TEXTURE_FILEPATH);

    std::ifstream readFile;
    readFile.open(this->_data->level);
    if(readFile.is_open())
    {
        for(int x = 0; x < WIDTH; x++)
        {
            for(int y = 0; y < HEIGHT; y++)
            {
                _level[x + WIDTH * y] = readFile.get() - '0';
            }
        }
    }
    
    readFile.close();

    if (!_map.load("Assets/Graphics/tileMap.png", sf::Vector2u(TILE_SIZE, TILE_SIZE), _level, WIDTH, HEIGHT))
        return;
    
    for( unsigned short int i = 0; i < NUM_COLONIES; i++)
    {
        colony = new Colony(this->_data, i);//Colony colony(this->_data);
        
        _colony.push_back(colony);
    }
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
    for( unsigned short int i = 0; i < _colony.size(); i++)
    {   
        _colony.at(i)->colonySimulate(dt);
    }
}

void GameState::Draw(float dt)
{
    this->_data->window.clear();
    this->_data->window.draw(_map);
    for( unsigned short int i = 0; i < NUM_COLONIES; i++)
    {
        _colony.at(i)->drawColony();
    }
    this->_data->window.display();
}