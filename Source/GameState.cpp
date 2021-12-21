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
    //_fr.f_r_texture.loadFromFile("Assets/Graphics/food.png");

    std::ifstream readFile;
    readFile.open(this->_data->levelName);
    //std::cout << "1" << std::endl;

    if(readFile.is_open())
    {
        for(int x = 0; x < WIDTH; x++)
        {
            for(int y = 0; y < HEIGHT; y++)
            {
                int spot = x + y * WIDTH;

                this->_data->grid[spot] = new Tile();

                this->_data->grid[spot]->type = readFile.get() - '0';
                this->_data->grid[spot]->arrayPos = spot;

                if(this->_data->grid[spot]->type == 2)
                    this->_data->grid[spot]->foodAmount = FOOD_DEFAULT_AMOUNT;
                //std::cout << "2" << std::endl;
                for(int i = 0; i < NUM_COLONIES; i++)
                {
                    this->_data->grid[spot]->pherHome[i][0] = false;
                    this->_data->grid[spot]->pherFood[i][0] = false;
                    this->_data->grid[spot]->pherFoodAmount[i][0] = 0;
                    this->_data->grid[spot]->pherHomeAmount[i][0] = 0;
                }

                //std::cout << this->_data->grid[spot]->type << " ";
            }
            //std::cout << std::endl;
        }
    }
    //int size = sizeof(this->_data->grid) << std::endl;
    //std::cout << this->_data->grid->size() << std::endl;

    readFile.close();

    //std::cout << "3" << std::endl;
    if (!_map.load("Assets/Graphics/tileMap.png", sf::Vector2u(TILE_SIZE, TILE_SIZE), _data->grid, WIDTH, HEIGHT))
        return;

    //std::cout << "yup 2" << std::endl;

    //std::cout << "4" << std::endl;
/*     if (!_fr.load(this->_data))make
        return; */


    
    
    for( unsigned short int i = 0; i < NUM_COLONIES; i++)
    {
        colony = new Colony(this->_data, i);//Colony colony(this->_data);
        colony->_pr.load();
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
            //_fr.update(_data);
            _ar.update(*_colony.at(i));
            //_colony.at(i)->_pr.update(*_colony.at(i));
        }
}

void GameState::Draw(float dt)
{
    this->_data->window.clear();
    this->_data->window.draw(_map);
    
    for( unsigned short int i = 0; i < NUM_COLONIES; i++)
    {
        this->_data->window.draw(_colony.at(i)->_pr);
        this->_data->window.draw(_colony.at(i)->nest);
    }

    //this->_data->window.draw(_fr);
    this->_data->window.draw(_ar);


    this->_data->window.display();
}