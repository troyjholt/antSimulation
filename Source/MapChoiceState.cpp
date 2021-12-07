#include <sstream>
#include "MapChoiceState.hpp"
#include "GameState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

MapChoiceState::MapChoiceState( GameDataRef data ) : _data( data )
{

}

void MapChoiceState::Init()
{
    this->_data->assets.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
    this->_data->assets.LoadTexture("Game Title", GAME_TITLE_FILEPATH);
    this->_data->assets.LoadTexture("Play Button", BUTTON_SMALL_FILEPATH);
    this->_data->assets.LoadTexture("Create Button", PLAY_BUTTON_FILEPATH);

    _background.setTexture(this->_data->assets.GetTexture("Main Menu Background"));
    _levelButton.setTexture(this->_data->assets.GetTexture("Play Button"));

    _levelButton.setPosition((SCREEN_WIDTH/2) - (_levelButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (_levelButton.getGlobalBounds().height / 2));
}

void MapChoiceState::HandleInput()
{
    sf::Event event;

    while(this->_data->window.pollEvent(event))
    {
        if(sf::Event::Closed == event.type)
        {
            this->_data->window.close();
        }

        if(_data->input.IsSpriteClicked(_levelButton, sf::Mouse::Left, this->_data->window))
        {
            //std::cout << "Go to game screen" << std::endl;
            _data->level = "Assets/Levels/test_level.txt";
            _data->machine.AddState(StateRef(new GameState(_data)), true);
        }
    }
}

void MapChoiceState::Update( float dt )
{

}

void MapChoiceState::Draw(float dt)
{
    this->_data->window.clear();
    this->_data->window.draw(this->_background);
    this->_data->window.draw(this->_levelButton);
    this->_data->window.display();
}