#include "ant.hpp"

Ant::Ant()
{
    antTexture.loadFromFile("Assets/Graphics/ant.png");
    antTexture.setSmooth(true);
    antSprite.setTexture(antTexture); 
    antSprite.setScale(0.2,0.2);
    //antSprite.setRotation(angle);
    antSprite.rotate(angle);
}

sf::Vector2f Ant::getPos()
{
    return pos;
}

float Ant::getAngle()
{
    return angle;
}

void Ant::setAngle(float mAngle)
{
    angle = mAngle;
    //antSprite.setRotation(mAngle);
    antSprite.rotate(mAngle);
    //std::cout << angle << ' ' << mAngle << std::endl;
}

void Ant::setPos(sf::Vector2f mPos)
{
    pos.x = mPos.x;
    pos.y = mPos.y;
}

/* void Ant::setPos(sf::Vector2f position)
{
    pos.x = position.x;
    pos.y = position.y;
}

void Ant::setColony(int mCol)
{
    colony = mCol;
}

void Ant::simulate(World &world)
{
    nextSpot(world);
}

float Ant::reverse()
{
    angle -= 180;
    if(angle < 0)
        angle +=360;
    return angle;
}

void Ant::nextSpot(World &world)
{
    float temp = rand() % 11 - 5;
    angle = angle + temp; 
    
    if(angle > 360)
        angle -= 360;
    
    if(angle < 0)
        angle += 360;

    float rad = angle / 57.2958;
    float y = speed * cos(rad);
    float x = speed * sin(rad);
    int X = pos.x + x;
    int Y = pos.y + y;

    if(world.grid[X][Y].type == 0)
    {
        move(X,Y);
    }
    else
    {
        angle = reverse();
        nextSpot(world);
    }
}

void Ant::move(int X, int Y)
{
    pos.x = X;
    pos.y = Y;
} */