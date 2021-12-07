#include <sstream>
#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "CreateState.hpp"
#include "DEFINITIONS.hpp"
#include "MapChoiceState.hpp"

#include <iostream>

MainMenuState::MainMenuState( GameDataRef data ) : _data( data )
{

}

void MainMenuState::Init()
{
    this->_data->assets.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
    this->_data->assets.LoadTexture("Game Title", GAME_TITLE_FILEPATH);
    this->_data->assets.LoadTexture("Play Button", PLAY_BUTTON_FILEPATH);
    this->_data->assets.LoadTexture("Create Button", PLAY_BUTTON_FILEPATH);
    this->_data->assets.LoadFont("Game Font", GAME_FONT_FILEPATH);

    _background.setTexture(this->_data->assets.GetTexture("Main Menu Background"));
    _title.setTexture(this->_data->assets.GetTexture("Game Title"));
    _playButton.setTexture(this->_data->assets.GetTexture("Play Button"));
    _createButton.setTexture(this->_data->assets.GetTexture("Play Button"));
    _playText.setFont(this->_data->assets.GetFont("Game Font"));
    _createText.setFont(this->_data->assets.GetFont("Game Font"));

    _playText.setString("Play");
    _playText.setFillColor(sf::Color::Black);
    _playText.setCharacterSize(35);

    _createText.setString("Create");
    _createText.setFillColor(sf::Color::Black);
    _createText.setCharacterSize(35);

    _title.setPosition((SCREEN_WIDTH/2) - (_title.getGlobalBounds().width / 2), _title.getGlobalBounds().height / 2);
    _playButton.setPosition((SCREEN_WIDTH/2) - (_playButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (_playButton.getGlobalBounds().height / 2));
    _createButton.setPosition((SCREEN_WIDTH/2) - (_playButton.getGlobalBounds().width / 2), ((SCREEN_HEIGHT / 2) - (_playButton.getGlobalBounds().height / 2) + 150));

    _playText.setPosition((SCREEN_WIDTH/2) - (_playText.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (_playText.getGlobalBounds().height / 2) - 5);
    _createText.setPosition((SCREEN_WIDTH/2) - (_createText.getGlobalBounds().width / 2), ((SCREEN_HEIGHT / 2) - (_createText.getGlobalBounds().height / 2) + 140));
}

void MainMenuState::HandleInput()
{
    sf::Event event;

    while(this->_data->window.pollEvent(event))
    {
        if(sf::Event::Closed == event.type)
        {
            this->_data->window.close();
        }

        if(_data->input.IsSpriteClicked(_playButton, sf::Mouse::Left, this->_data->window))
        {
            //std::cout << "Go to game screen" << std::endl;
            _data->machine.AddState(StateRef(new MapChoiceState(_data)), true);
        }

        if(_data->input.IsSpriteClicked(_createButton, sf::Mouse::Left, this->_data->window))
        {
            //std::cout << "Go to create screen" << std::endl;
            _data->machine.AddState(StateRef(new CreateState(_data)), true);
        }
    }
}

void MainMenuState::Update( float dt )
{

}

void MainMenuState::Draw(float dt)
{
    this->_data->window.clear();
    this->_data->window.draw(this->_background);
    this->_data->window.draw(this->_title);
    this->_data->window.draw(this->_playButton);
    this->_data->window.draw(this->_createButton);
    this->_data->window.draw(this->_playText);
    this->_data->window.draw(this->_createText);
    this->_data->window.display();
}