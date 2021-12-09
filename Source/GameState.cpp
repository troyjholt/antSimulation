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
    this->_data->assets.LoadTexture("FOOD", FOOD_TEXTURE_FILEPATH);
    this->_data->assets.LoadTexture("NEST", NEST_TEXTURE_FILEPATH);

    _ar.a_r_texture.loadFromFile("Assets/Graphics/antTextures.png");

    std::ifstream readFile;
    readFile.open(this->_data->level);
    if(readFile.is_open())
    {
        for(int x = 0; x < WIDTH; x++)
        {
            for(int y = 0; y < HEIGHT; y++)
            {
                this->_level[x + WIDTH * y] = readFile.get() - '0';
                if(_level[x + WIDTH * y] == 2)
                {
                    //std::cout << "food: " << x << " " << y << std::endl; 
                    Food food(x, y);
                    food.foodSprite.setTexture(_data->assets.GetTexture("FOOD"));
                    this->_data->food.push_back(food); //_food->push_back(food);
                    this->_level[x + WIDTH * y] = 0;
                }
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
        if(!_ar.load(*_colony.at(i)))
            return;
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

        if(event.type == sf::Event::KeyPressed)
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            {
                _start = !_start;
                //std::cout << _start << std::endl;
                break;
            }

    }
}

void GameState::Update( float dt )
{
    if(_start)
        for( unsigned short int i = 0; i < _colony.size(); i++)
        {   
            _colony.at(i)->colonySimulate(dt);
            _colony.at(i)->pheromoneSimulate(dt);
            //std::cout << "yes" << std::endl;
            _ar.update(*_colony.at(i));
        }
}

void GameState::Draw(float dt)
{
    this->_data->window.clear();
    this->_data->window.draw(_map);
    this->_data->window.draw(_ar);

/*     for(int i = 0; i < this->_data->food.size(); i++)
    {
        this->_data->window.draw(this->_data->food.at(i).foodSprite);
    } */

    for( unsigned short int i = 0; i < NUM_COLONIES; i++)
    {
       // _colony.at(i)->drawColony();
    }
    this->_data->window.display();
}