#include <sstream>
#include "CreateState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

CreateState::CreateState( GameDataRef data ) : _data( data )
{

}

void CreateState::Init()
{
    this->_data->assets.LoadTexture("Small Button", BUTTON_SMALL_FILEPATH);
    this->_data->assets.LoadTexture("Small Button Active", BUTTON_SMALL_ACTIVE_FILEPATH);
    this->_data->assets.LoadFont("Game Font", GAME_FONT_FILEPATH);

    _wallButton.setTexture(this->_data->assets.GetTexture("Small Button"));
    _nestButton.setTexture(this->_data->assets.GetTexture("Small Button"));
    _foodButton.setTexture(this->_data->assets.GetTexture("Small Button"));
    _saveButton.setTexture(this->_data->assets.GetTexture("Small Button"));
    
    //_createButton.setTexture(this->_data->assets.GetTexture("Play Button"));
    //_playText.setFont(this->_data->assets.GetFont("Game Font"));
    //_createText.setFont(this->_data->assets.GetFont("Game Font"));

    //_playText.setString("Play");
    //_playText.setFillColor(sf::Color::Black);
    //_playText.setCharacterSize(35);

    //_createText.setString("Create");
    //_createText.setFillColor(sf::Color::Black);
    //_createText.setCharacterSize(35);

    //_title.setPosition((SCREEN_WIDTH/2) - (_title.getGlobalBounds().width / 2), _title.getGlobalBounds().height / 2);

    _wallButton.setPosition(((SCREEN_WIDTH/4) * 0.5 ) - (_nestButton.getGlobalBounds().width / 2), ((SCREEN_HEIGHT / 2) - (_nestButton.getGlobalBounds().height / 2) + 250));
    _nestButton.setPosition(((SCREEN_WIDTH/4) * 1   ) - (_nestButton.getGlobalBounds().width / 2), ((SCREEN_HEIGHT / 2) - (_nestButton.getGlobalBounds().height / 2) + 250));
    _foodButton.setPosition(((SCREEN_WIDTH/4) * 1.5 ) - (_foodButton.getGlobalBounds().width / 2), ((SCREEN_HEIGHT / 2) - (_foodButton.getGlobalBounds().height / 2) + 250));
    _saveButton.setPosition(((SCREEN_WIDTH/4) * 2   ) - (_foodButton.getGlobalBounds().width / 2), ((SCREEN_HEIGHT / 2) - (_foodButton.getGlobalBounds().height / 2) + 250));

    //_playText.setPosition((SCREEN_WIDTH/2) - (_playText.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (_playText.getGlobalBounds().height / 2) - 5);
    //_createText.setPosition((SCREEN_WIDTH/2) - (_createText.getGlobalBounds().width / 2), ((SCREEN_HEIGHT / 2) - (_createText.getGlobalBounds().height / 2) + 140));
    
    std::ifstream readFile;
    readFile.open("Assets/Levels/creation_level.txt");
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
                //_level[x + WIDTH * y] = readFile.get() - '0';
            }
        }
    }
    
    readFile.close();

    if (!_map.load("Assets/Graphics/tileMap.png", sf::Vector2u(TILE_SIZE, TILE_SIZE),_data->grid, WIDTH, HEIGHT))
        return;
}


void CreateState::HandleInput()
{
    sf::Event event;

    while(this->_data->window.pollEvent(event))
    {
        if(sf::Event::Closed == event.type)
        {
            this->_data->window.close();
        }

        if(_data->input.IsSpriteClicked(_wallButton, sf::Mouse::Left, this->_data->window))
        {
            this->_bWall = !_bWall;
            this->_bFood = false;
            this->_bNest = false;
            
            if(!this->_bWall)
                _wallButton.setTexture(this->_data->assets.GetTexture("Small Button"));
            else
                _wallButton.setTexture(this->_data->assets.GetTexture("Small Button Active"));   

            _nestButton.setTexture(this->_data->assets.GetTexture("Small Button"));
            _foodButton.setTexture(this->_data->assets.GetTexture("Small Button"));
        }
        else if(_data->input.IsSpriteClicked(_nestButton, sf::Mouse::Left, this->_data->window))
        {
            this->_bWall = false;
            this->_bFood = false;
            this->_bNest = !_bNest;

            if(!this->_bNest)
                _nestButton.setTexture(this->_data->assets.GetTexture("Small Button"));
            else
                _nestButton.setTexture(this->_data->assets.GetTexture("Small Button Active"));   

            _wallButton.setTexture(this->_data->assets.GetTexture("Small Button"));
            _foodButton.setTexture(this->_data->assets.GetTexture("Small Button"));
        }
        else if(_data->input.IsSpriteClicked(_foodButton, sf::Mouse::Left, this->_data->window))
        {
            this->_bWall = false;
            this->_bFood = !_bFood;
            this->_bNest = false;

            if(!this->_bFood)
                _foodButton.setTexture(this->_data->assets.GetTexture("Small Button"));
            else
                _foodButton.setTexture(this->_data->assets.GetTexture("Small Button Active"));   
            
            _wallButton.setTexture(this->_data->assets.GetTexture("Small Button"));
            _nestButton.setTexture(this->_data->assets.GetTexture("Small Button"));
        }
        else if(_data->input.IsSpriteClicked(_saveButton, sf::Mouse::Left, this->_data->window))
        {
            int num = rand() % 100000;

            std::string str1 = "Assets/Levels/" +  std::to_string(num) + ".txt";// + num + ".txt";
            std::cout << str1 << std::endl;

            std::ofstream readFile(str1);
            
            for(int x = 0; x < WIDTH; x++)
            {
                for(int y = 0; y < HEIGHT; y++)
                {
                    readFile << this->_data->grid[x + WIDTH * y]->type;
                }
            }
            readFile.close();
            _data->machine.AddState(StateRef(new MainMenuState(_data)), true);
        }
        else if((sf::Mouse::isButtonPressed(sf::Mouse::Right) || 
               ((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && 
               (_bWall || _bFood || _bNest))))
        {
            int size = this->_brushSize;
            if(_bNest && !sf::Mouse::isButtonPressed(sf::Mouse::Right))
                size = 1;
            sf::Vector2i pos = sf::Mouse::getPosition(this->_data->window);
            int x = size * -1;
            for(x; x < size; x++)
            {
                int y = size * -1;
                for(y; y < size; y++)
                {
                    if((((pos.x + x) >= 4) && ((pos.y + y) >= 4)) && ((pos.x + x)/TILE_SIZE < WIDTH - 1) && ((pos.y + y)/TILE_SIZE < HEIGHT - 1))
                    {
                        if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
                        {
                            this->_data->grid[((pos.x + x)/TILE_SIZE) + WIDTH * ((pos.y + y)/TILE_SIZE)]->type = 0;
                        }
                        else if(_bWall)
                        {
                            this->_data->grid[((pos.x + x)/TILE_SIZE) + WIDTH * ((pos.y + y)/TILE_SIZE)]->type = 1;
                            //world->buildWalls(pos, brushSize);
                        }
                        else if(_bFood)
                        {
                             this->_data->grid[((pos.x + x)/TILE_SIZE) + WIDTH * ((pos.y + y)/TILE_SIZE)]->type = 2;
                            //world->buildFood(pos, brushSize);
                        }
                        else if(_bNest)
                        {
                             this->_data->grid[((pos.x + x)/TILE_SIZE) + WIDTH * ((pos.y + y)/TILE_SIZE)]->type = 3;
                        }

                    }
                }
            }

            if (!_map.load("Assets/Graphics/tileMap.png", sf::Vector2u(TILE_SIZE, TILE_SIZE), _data->grid, WIDTH, HEIGHT))
                return;
        }
    }
}

void CreateState::Update( float dt )
{

}

void CreateState::Draw(float dt)
{
    this->_data->window.clear();
    this->_data->window.draw(this->_map);
    this->_data->window.draw(this->_wallButton);
    this->_data->window.draw(this->_nestButton);
    this->_data->window.draw(this->_foodButton);
    this->_data->window.draw(this->_saveButton);
    this->_data->window.display();
}