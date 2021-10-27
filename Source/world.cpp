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
    colPos.x = 50;
    colPos.y = 50;
    grid[50][50].type = 4;

    nest.setRadius(10.f);
    nest.setPosition((colPos.x - 2) * tileSize, (colPos.y - 2) * tileSize);
    nest.setFillColor(sf::Color::Black);


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
            else if(this->grid[x][y].type == 2)
            {
                this->grid[x][y].shape.setFillColor(sf::Color(0, 255, 0));
                this->grid[x][y].shape.setSize(sf::Vector2f(tileSize,tileSize));
                this->grid[x][y].shape.setPosition(x * tileSize, y * tileSize);
                this->grid[x][y].hasFood = true;
                this->grid[x][y].foodAmount = 50;
                window.draw(this->grid[x][y].shape);
            }
            else if((this->grid[x][y].pherHome == true) && (this->grid[x][y].pherFood == true))
            {
                int alpha;
                if(this->grid[x][y].pherFoodAmount > this->grid[x][y].pherHomeAmount)
                {
                    alpha = this->grid[x][y].pherFoodAmount;
                }
                else
                {
                    alpha = this->grid[x][y].pherHomeAmount;
                }
                this->grid[x][y].shape.setFillColor(sf::Color(this->grid[x][y].pherHomeAmount, 0, this->grid[x][y].pherFoodAmount,alpha));
                this->grid[x][y].shape.setSize(sf::Vector2f(tileSize,tileSize));
                this->grid[x][y].shape.setPosition(x * tileSize, y * tileSize);
                window.draw(this->grid[x][y].shape);
            }
            else if(this->grid[x][y].pherHome == true)
            {
                this->grid[x][y].shape.setFillColor(sf::Color(255, 0, 0,this->grid[x][y].pherHomeAmount));
                this->grid[x][y].shape.setSize(sf::Vector2f(tileSize,tileSize));
                this->grid[x][y].shape.setPosition(x * tileSize, y * tileSize);
                window.draw(this->grid[x][y].shape);
            }
            else if(this->grid[x][y].pherFood == true)
            {
                this->grid[x][y].shape.setFillColor(sf::Color(0, 0, 255,this->grid[x][y].pherFoodAmount));
                this->grid[x][y].shape.setSize(sf::Vector2f(tileSize,tileSize));
                this->grid[x][y].shape.setPosition(x * tileSize, y * tileSize);
                window.draw(this->grid[x][y].shape);
            }
        }
    }

    for(int i = 0; i < antSize; i++)
    {
        this->ant[i].antSprite.setPosition(this->ant[i].pos.x * tileSize, this->ant[i].pos.y * tileSize);
        this->ant[i].antSprite.setRotation(this->ant[i].angle);
        window.draw(this->ant[i].antSprite);
    }

    window.draw(this->nest);
};

void World::simulate(sf::Time elapsed)
{
    pherSimulate(elapsed);
    antSimulate(elapsed);
    //future objects simulate()
}

void World::pherSimulate(sf::Time elapsed)
{
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            if(this->grid[x][y].pherHome == true)
            {
                float dif = elapsed.asSeconds() - this->grid[x][y].time.asSeconds();
                //std::cout << elapsed.asSeconds() << ' ' << this->grid[x][y].time.asSeconds() << std::endl;
                
                if((dif < 15.0) && (this->grid[x][y].pherHomeAmount > 0))
                {
                    this->grid[x][y].shape.setFillColor(sf::Color(250, 0, 0,this->grid[x][y].pherHomeAmount));
                    this->grid[x][y].shape.setSize(sf::Vector2f(tileSize,tileSize));
                    this->grid[x][y].shape.setPosition(x * tileSize, y * tileSize);
                    //this->grid[x][y].pherHomeAmount--;
                }
                else if((dif > 15.0) && (this->grid[x][y].pherHomeAmount > 0))
                {
                    this->grid[x][y].pherHomeAmount--;
                    this->grid[x][y].shape.setFillColor(sf::Color(250, 0, 0,this->grid[x][y].pherHomeAmount));
                    this->grid[x][y].shape.setSize(sf::Vector2f(tileSize,tileSize));
                    this->grid[x][y].shape.setPosition(x * tileSize, y * tileSize);
                }
                else
                { 
                    this->grid[x][y].pherHome = false;
                }
            }
            if(this->grid[x][y].pherFood == true)
            {
                float dif = elapsed.asSeconds() - this->grid[x][y].time.asSeconds();
                //std::cout << elapsed.asSeconds() << ' ' << this->grid[x][y].time.asSeconds() << std::endl;
                
                if((dif < 15.0) && (this->grid[x][y].pherFoodAmount > 0))
                {
                    this->grid[x][y].shape.setFillColor(sf::Color(250, 0, 0,this->grid[x][y].pherFoodAmount));
                    this->grid[x][y].shape.setSize(sf::Vector2f(tileSize,tileSize));
                    this->grid[x][y].shape.setPosition(x * tileSize, y * tileSize);
                    //this->grid[x][y].pherHomeAmount--;
                }
                else if((dif > 15.0) && (this->grid[x][y].pherFoodAmount > 0))
                {
                    this->grid[x][y].pherFoodAmount--;
                    this->grid[x][y].shape.setFillColor(sf::Color(250, 0, 0,this->grid[x][y].pherFoodAmount));
                    this->grid[x][y].shape.setSize(sf::Vector2f(tileSize,tileSize));
                    this->grid[x][y].shape.setPosition(x * tileSize, y * tileSize);
                }
                else
                { 
                    this->grid[x][y].pherFood = false;
                }
            }
        }
    }
}

void World::antSimulate(sf::Time elapsed)
{
    for(int i = 0; i < antSize; i++)
    {
        sf::Vector2f pos = this->ant[i].getPos();
        float angle = this->ant[i].getAngle();

        //antNextSpot(pos);

        float temp = rand() % 11 - 5;
        angle = angle + temp; 
        
        if(angle > 360)
            angle -= 360;
        
        if(angle < 0)
            angle += 360;

        float rad = angle / 57.2958;
        float x = 1.0f * cos(rad);
        float y = 1.0f * sin(rad);
        int X = pos.x + x;
        int Y = pos.y + y;
        
        //std::cout << X << ' ' << Y << std::endl;
        if((this->grid[X][Y].type == 4) && (this->ant[i].hasFood == true))
        {
            //std::cout << "we made it" << std::endl;
            pos.x = pos.x + x;
            pos.y = pos.y + y;
            this->ant[i].setPos(pos);
            this->ant[i].hasFood = false;
            this->ant[i].amount = 500;
            angle = antReverse(angle);
            this->ant[i].setAngle(angle);
            this->ant[i].antSprite.setPosition(this->ant[i].pos);
            this->ant[i].antSprite.setRotation(this->ant[i].angle);
        }
        else if((this->grid[X][Y].type == 0) && (this->ant[i].hasFood == true) && (this->grid[X][Y].pherHomeAmount > 0))
        {
            temp = averageHomeAngle(X,Y);
            pos.x = pos.x + x;
            pos.y = pos.y + y;
            this->ant[i].setPos(pos);
            this->ant[i].setAngle(temp);
            this->ant[i].antSprite.setPosition(this->ant[i].pos);
            this->ant[i].antSprite.setRotation(temp);
        }
        else if((this->grid[X][Y].type == 0) && (this->ant[i].hasFood == false) && (this->grid[X][Y].pherFoodAmount > 0))
        {
            temp = averageFoodAngle(X,Y);
            //std::cout << temp << ' ' <<  this->grid[X][Y].toFoodAngle << std::endl; 
            pos.x = pos.x + x;
            pos.y = pos.y + y;
            this->ant[i].setPos(pos);
            this->ant[i].setAngle(temp);
            this->ant[i].antSprite.setPosition(this->ant[i].pos);
            this->ant[i].antSprite.setRotation(temp);
        }
        else if((this->grid[X][Y].type == 0) || ((this->grid[X][Y].type == 4) && (this->ant[i].hasFood == false)))
        {
            pos.x = pos.x + x;
            pos.y = pos.y + y;
            this->ant[i].setPos(pos);
            this->ant[i].setAngle(angle);
            this->ant[i].antSprite.setPosition(this->ant[i].pos);
            this->ant[i].antSprite.setRotation(this->ant[i].angle);
            //antMove(X,Y);
        }
        else if((this->grid[X][Y].type == 2) && (this->ant[i].hasFood == false))
        {
            this->ant[i].hasFood = true;
            this->ant[i].amount = 500;
            angle = antReverse(angle);
            this->ant[i].setAngle(angle);
            this->ant[i].antSprite.setPosition(this->ant[i].pos);
            this->ant[i].antSprite.setRotation(this->ant[i].angle);
        }
        else
        {
            angle = antReverse(angle);
            this->ant[i].setAngle(angle);
            this->ant[i].antSprite.setPosition(this->ant[i].pos);
            this->ant[i].antSprite.setRotation(this->ant[i].angle);
        }

        if((this->ant[i].hasFood == false) && (this->ant[i].amount > 0) && (this->grid[X][Y].pherHomeAmount < this->ant[i].amount))
        {
            this->ant[i].amount--;
            this->grid[X][Y].pherHome = true;
            this->grid[X][Y].time = elapsed;
            this->grid[X][Y].toHomeAngle = antReverse(angle);
            if(this->ant[i].amount > 250)
                this->grid[X][Y].pherHomeAmount = 250;
            else
                this->grid[X][Y].pherHomeAmount = this->ant[i].amount;
        }
        else if((this->ant[i].hasFood == true) && (this->ant[i].amount > 0) && (this->grid[X][Y].pherFoodAmount < this->ant[i].amount))
        {
            this->ant[i].amount--;
            this->grid[X][Y].pherFood = true;
            this->grid[X][Y].time = elapsed;
            this->grid[X][Y].toFoodAngle = antReverse(angle);
            if(this->ant[i].amount > 250)
                this->grid[X][Y].pherFoodAmount = 250;
            else
                this->grid[X][Y].pherFoodAmount = this->ant[i].amount;
        }
    }
}

float World::averageFoodAngle(int x, int y)
{
    int sumOfWeight = 1;
    int weightAngle = 1;
    float ret = 0.0;

    for(int row = -1; row <= 1; row++)
        for(int col = -1; col <=1; col++)
        {
            if(this->grid[x + row][y + col].pherFood == true)
            {
                sumOfWeight = sumOfWeight + this->grid[x + row][y + col].pherFoodAmount;
                weightAngle = weightAngle + this->grid[x + row][y + col].pherFoodAmount * this->grid[x + row][y + col].toFoodAngle;
            }
        }

    //std::cout << "food pheromone " << weightAngle << " " << sumOfWeight << std::endl;
    if((sumOfWeight > 0) && (weightAngle > 0))
    {
        ret = weightAngle / sumOfWeight;
    }

    return ret;
}

float World::averageHomeAngle(int x, int y)
{
    int sumOfWeight = 0;
    int weightAngle = 0;
    float ret = 0.0;

    for(int row = -1; row <= 1; row++)
        for(int col = -1; col <=1; col++)
        {
            if((this->grid[x + row][y + col].type == 0) && (this->grid[x + row][y + col].pherHome == true))
            {
                sumOfWeight = sumOfWeight + this->grid[x + row][y + col].pherHomeAmount;
                weightAngle = weightAngle + this->grid[x + row][y + col].pherHomeAmount * this->grid[x + row][y + col].toHomeAngle;
            }
        }

    //std::cout << "Home pheromone " << weightAngle << " " << sumOfWeight << std::endl;
    if((sumOfWeight > 0) && (weightAngle > 0))
    {
        ret = weightAngle / sumOfWeight;
    }

    return ret;
}

float World::antReverse(float angle)
{
    angle -= 180;
    if(angle < 0)
        angle +=360;

    return angle;
}

void World::buildWalls(sf::Vector2i pos, int brushSize)
{
    int x;
    int y;
    if(brushSize > 1)
    {
        x = brushSize * -1;
        y = brushSize * -1;

        //std::cout << x << ' ' << y << std::endl;
        for(x; x < brushSize; x++)
        {
            for(y; y < brushSize; y++)
            {
                this->grid[(pos.x + x) / tileSize][(pos.y + y)/ tileSize].type = 1;
            }
        }
    }
    else
    {
        if(this->grid[pos.x / tileSize][pos.y / tileSize].type == 0)
        {
            this->grid[pos.x / tileSize][pos.y / tileSize].type = 1;
        }
        
    }
    
}

void World::buildFood(sf::Vector2i pos, int brushSize)
{
    int x;
    int y;
    if(brushSize > 1)
    {
        x = brushSize * -1;
        y = brushSize * -1;

        //std::cout << x << ' ' << y << std::endl;
        for(x; x < brushSize; x++)
        {
            for(y; y < brushSize; y++)
            {
                if(this->grid[(pos.x + x) / tileSize][(pos.y + y)/ tileSize].type == 0)
                {
                    this->grid[(pos.x + x) / tileSize][(pos.y + y)/ tileSize].type = 2;
                }

            }
        }
    }
    else
    {
        this->grid[pos.x / tileSize][pos.y / tileSize].type = 2;
    }
    //this->grid[pos.x / tileSize][pos.y / tileSize].type = 2;
}