#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

class MapChoiceState : public State
{
    public:
        MapChoiceState(GameDataRef data);

        void Init();
        
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
    
    private:
        GameDataRef _data;

        sf::Sprite _background;
        sf::Sprite _levelButton;
};