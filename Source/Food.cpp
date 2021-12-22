#include "Food.hpp"

Food::Food( int X, int Y)
{
    posX = X;
    posY = Y;
    pos.x = X;
    pos.y = Y;

    //SpawnFood(X, Y);
}

void Food::SpawnFood(int X, int Y)
{
    //foodSprite.setPosition(X * TILE_SIZE, Y * TILE_SIZE);
    //foodSprite.setScale(0.15,0.15);
}

int Food::RemoveFood(int carryCapacity)
{
    foodAmount-=carryCapacity;
    return foodAmount;
}

bool Food::CheckSpot(int X, int Y)
{
    //std::cout << X << " " << Y << std::endl;
    if((X == posX) && (Y == posY))
        return true;

    return false;
}