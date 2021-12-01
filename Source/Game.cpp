#include "Game.hpp"

Game::Game()
: mWindow(sf::VideoMode(1024, 768), "Ant Simulation")
{

}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    TextureHolder textures;
    textures.load(Textures::Ant, "Assets/Graphics/ant.png");

    sf::Sprite ant;
    ant.setTexture(textures.get(Textures::Ant));


    sf::Text landing_text;
    sf::Font font;
    if(!font.loadFromFile("Assets/Fonts/Yagora.ttf"));

    landing_text.setFont(font);
    landing_text.setCharacterSize(30);

    landing_text.setFillColor(sf::Color::Black);
    landing_text.setFillColor(sf::Color::Black);
    landing_text.setPosition(mWindow.getView().getSize().x / 2, 40.f);//mWindow.getSize().x/2.f, 20.0f);
    landing_text.setString("Ant Simulation");
    sf::FloatRect textRect = landing_text.getLocalBounds();
    landing_text.setOrigin((textRect.left + textRect.width/2.0f), (textRect.top + textRect.height/2.0f));

    while(mWindow.isOpen())
    {
        //sf::Time deltaTime = clock.restart();
        
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        
        render();
        mWindow.draw(landing_text);
        mWindow.display();
    }
}

void Game::processEvents()
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
}

void Game::handleMouseInput(sf::Event::MouseButtonEvent b, bool isPressed)
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
}

void Game::handleKeyboardInput(sf::Keyboard::Key key, bool isPressed)
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
}

void Game::update(sf::Time deltaTime)
{

}

void Game::render()
{
    mWindow.clear(sf::Color(225, 190, 160));
    //mWindow.draw();
    //mWindow.display();

}