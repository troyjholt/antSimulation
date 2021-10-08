#include "world.hpp"

World::World()
{
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            if((x == 0) || (x == width - 1) || (y == 0) || (y == height - 1))
                this->grid[x][y].type = 1; // wall
        }
    }
    colPos.x = 2;
    colPos.y = 2;

    for(int i = 0; i < antSize; i++)
    {
        ant[i].pos.x = colPos.x;
        ant[i].pos.y = colPos.y;
    }
};

void World::draw(sf::RenderWindow &window)
{
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            if(this->grid[x][y].type == 1)
            {
                this->grid[x][y].shape.setFillColor(sf::Color(80, 65, 50));
                this->grid[x][y].shape.setSize(sf::Vector2f(tileSize,tileSize));
                this->grid[x][y].shape.setPosition(x * tileSize, y * tileSize);
                window.draw(this->grid[x][y].shape);
                //std::cout << x << ' ' << y << std::endl;
            }
        }
    }

    for(int i = 0; i < antSize; i++)
    {

        window.draw(this->ant[i].antSprite);
    }
};

void World::simulate()
{
    antSimulate();
    //future objects simulate()
}

void World::antSimulate()
{
    for(int i = 0; i < antSize; i++)
    {
        sf::Vector2f pos = ant[i].getPos();
        float angle = ant[i].getAngle();

        //antNextSpot(pos);

        float temp = rand() % 11 - 5;
        angle = angle + temp; 
        
        if(angle > 360)
            angle -= 360;
        
        if(angle < 0)
            angle += 360;

        float rad = angle / 57.2958;
        float y = 1.0f * cos(rad);
        float x = 1.0f * sin(rad);
        int X = pos.x + x;
        int Y = pos.y + y;
        

        if(this->grid[X][Y].type == 0)
        {
            pos.x = pos.x + x;
            pos.y = pos.y + y;
            this->ant[i].setPos(pos);
            this->ant[i].setAngle(angle);
            //antMove(X,Y);
        }
        else
        {
            angle = antReverse(angle);
            this->ant[i].setAngle(angle);
        }
    }
}


float World::antReverse(float angle)
{
    angle -= 180;
    if(angle < 0)
        angle +=360;

    return angle;
}

/* void World::antNextSpot(sf::Vector2f pos)
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

void World::antMove(int X, int Y)
{
    pos.x = X;
    pos.y = Y;
} */