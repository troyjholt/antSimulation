#include "Game.hpp"
#include "SplashState.hpp"
//#include "GameState.hpp"

Game::Game(int width, int height, std::string title)//: mWindow(sf::VideoMode(1024, 768), "Ant Simulation")
{
    _data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
    _data->machine.AddState(StateRef(new SplashState(this->_data)));
    
    this->run( );
}

void Game::run()
{
    float newTime, frameTime, interpolation;

    float currentTime = this->_clock.getElapsedTime().asSeconds();
    float accumulator = 0.0f;

    while (this->_data->window.isOpen())
    {
        this->_data->machine.ProcessStateChanges();

        newTime = this->_clock.getElapsedTime().asSeconds();
        frameTime = newTime - currentTime;

        if (frameTime > 0.25f)
        {
            frameTime = 0.25f;
        }

        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= dt)
        {
            this->_data->machine.GetActiveState()->HandleInput();
            this->_data->machine.GetActiveState()->Update(dt);

            accumulator -= dt;
        }

        interpolation = accumulator / dt;
        this->_data->machine.GetActiveState()->Draw(interpolation);
    }
}

/* void Game::processEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::MouseButtonPressed:
                handleMouseInput(event.mouseButton, true);
                break;
            case sf::Event::KeyPressed:
                handleKeyboardInput(event.key.code, true);
                break;
            case sf::Event::Closed:
                mWindow.close();
                break;
        }
    }
} */

/* void Game::handleMouseInput(sf::Event::MouseButtonEvent b, bool isPressed)
{
     if(b.button == 0)
    {
        sf::Vector2i pos;// = sf::Mouse::getPosition(mWindow);
        pos.x = b.x;
        pos.y = b.y;

        if((pos.x >= 0) && ((pos.x/tileSize) <= (width * tileSize)) && (pos.y >= 0) && ((pos.y/tileSize) <= (height * tileSize)))
        {
            int x = brushSize * -1;
            for(x; x < brushSize; x++)
            {
                int y = brushSize * -1;
                for(y; y < brushSize; y++)
                {
                    if((((pos.x + x) >= 0) && ((pos.y + y) >= 0)) && ((pos.x + x)/tileSize < width) && ((pos.y + y)/tileSize < height))
                    {
                        if(bWall)
                        {
                            //level[((pos.x + x)/tileSize) + width * ((pos.y + y)/tileSize)] = 1;
                            //world->buildWalls(pos, brushSize);
                        }
                        else if(bFood)
                        {
                            // level[((pos.x + x)/tileSize) + width * ((pos.y + y)/tileSize)] = 2;
                            //world->buildFood(pos, brushSize);
                        }
                        else if(bErase)
                        {
                            // level[((pos.x + x)/tileSize) + width * ((pos.y + y)/tileSize)] = 0;
                            //world->buildErase(pos, brushSize);
                        }
                    }
                }
            }

            //map.load("Assets/Graphics/tileMap.png", sf::Vector2u(tileSize, tileSize), level, width, height);
            //world->updateLevel(level);
        }
    }
} */

/* void Game::handleKeyboardInput(sf::Keyboard::Key key, bool isPressed)
{
    if(key == sf::Keyboard::Num1)
        start = !start;
    else if(key == sf::Keyboard::Num2)
    {
        bWall = !bWall;
        bFood = false;
        bErase = false;
    }
    else if(key == sf::Keyboard::Num3)
    {
        bFood = !bFood;
        bWall = false;
        bErase = false;
    }
    else if(key == sf::Keyboard::Num4)
    {
        bErase = !bErase;
        bWall = false;
        bFood = false;
    }
    else if(key == sf::Keyboard::Num5)
    {
        // ant sight
    }
    else if(key == sf::Keyboard::Num6)
    {
        // pheromone draw
    }
    else if(key == sf::Keyboard::P)
    {
        // print map
    }
    else if(key == sf::Keyboard::LBracket)
    {
        if(brushSize == smallSize)
            brushSize = smallSize;
        else
            brushSize--;
    }
    else if(key == sf::Keyboard::RBracket)
    {
        if(brushSize == maxSize)
            brushSize = maxSize;
        else
            brushSize++;
    }
} */

/* void Game::update(sf::Time deltaTime)
{

} */

/* void Game::render()
{
    //mWindow.clear(sf::Color(225, 190, 160));
    //mWindow.draw();
    //mWindow.display();

} */