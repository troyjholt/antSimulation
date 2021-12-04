#include "Colony.hpp"

Colony::Colony( GameDataRef data , int ID) : _data( data )
{
    id = ID;
    std::ifstream readFile;
    readFile.open(this->_data->level);
    if(readFile.is_open())
    {
        for(int x = 0; x < WIDTH; x++)
        {
            for(int y = 0; y < HEIGHT; y++)
            {
                grid[x + WIDTH * y].type = readFile.get() - '0';
                if(grid[x + WIDTH * y].type == 4)
                {
                    colPos.x = x * TILE_SIZE;
                    colPos.y = y * TILE_SIZE;
                }
            }
        }
        //std::cout << colPos.x << " " << colPos.y << std::endl;
    }

    readFile.close();

    for(int i = 0; i < COLONY_START_SIZE; i++)
    {
        ant = new Ant(this->_data);
        ant->setPos(this->colPos);
        ant->colonyID = ID;
        ant->antSprite.setTexture(this->_data->assets.GetTexture("ANT"));
        _ants.push_back(ant);
    }
}

void Colony::drawColony()
{
    for(int i = 0; i < _ants.size(); i++)
    {
        this->_data->window.draw(_ants.at(i)->antSprite);
    }
}

void Colony::colonySimulate(float dt)
{
    for(int i = 0; i < _ants.size(); i++)
    {
        //Ant *A = _ants.at(i);
        float movement = this->speed * dt;

        sf::Vector2f pos = _ants.at(i)->getPos();
        float angle = findAngle(*_ants.at(i));
        //std::cout << "Angle = " << angle << std::endl;

        bool hasFood = _ants.at(i)->hasFood;
        float temp = rand() % 11 - 5;

        float rad = angle / 57.2958;
        //float x = 1.0f * cos(rad);
        //float y = 1.0f * sin(rad);
        float x = movement * cos(rad);
        float y = movement * sin(rad);
        int X = pos.x + x;
        int Y = pos.y + y;

        //std::cout << X << " " << Y << " " << (X + WIDTH * Y)/TILE_SIZE << std::endl;

        if((this->grid[(X + WIDTH * Y)/TILE_SIZE].type == 4) && (hasFood))
        {
            //std::cout << "we made it" << std::endl;
            pos.x = pos.x + x;
            pos.y = pos.y + y;
            _ants.at(i)->setPos(pos);
            _ants.at(i)->hasFood = false;
            _ants.at(i)->pheromoneAmount = 500;
            angle = antReverse(angle);
            _ants.at(i)->antSprite.setTexture(this->_data->assets.GetTexture("ANT"));
            _ants.at(i)->setAngle(angle);
            _ants.at(i)->antSprite.setPosition(_ants.at(i)->pos);
            _ants.at(i)->antSprite.setRotation(_ants.at(i)->angle);

            foodReturned = foodReturned + this->carryCapacity;
            //std::cout << "pheromoneAmount of food in storage: " << foodReturned << std::endl;
            if(foodReturned >= 5)
            {
                foodReturned = 0;
                colSize+=1;
                //std::cout << "New ant created. # of ants is now: " << antSize << std::endl;
            }
        }
        else if((this->grid[(X + WIDTH * Y)/TILE_SIZE].type == 0) && (hasFood) && (this->grid[(X + WIDTH * Y)/TILE_SIZE].pherHomeAmount > 0))
        {
            //temp = averageHomeAngle(ant[i]);
            pos.x = pos.x + x;
            pos.y = pos.y + y;
            _ants.at(i)->setPos(pos);
            _ants.at(i)->setAngle(angle);
            _ants.at(i)->antSprite.setPosition(_ants.at(i)->pos);
            _ants.at(i)->antSprite.setRotation(angle);
        }
        else if((this->grid[(X + WIDTH * Y)/TILE_SIZE].type == 0) && (!hasFood) && (this->grid[(X + WIDTH * Y)/TILE_SIZE].pherFoodAmount > 0))
        {
            //temp = averageFoodAngle(ant[i]);
            //std::cout << temp << ' ' <<  this->grid[X][Y].toFoodAngle << std::endl; 
            pos.x = pos.x + x;
            pos.y = pos.y + y;
            _ants.at(i)->setPos(pos);
            _ants.at(i)->setAngle(angle);
            _ants.at(i)->antSprite.setPosition(_ants.at(i)->pos);
            _ants.at(i)->antSprite.setRotation(angle);
        }
        else if((this->grid[(X + WIDTH * Y)/TILE_SIZE].type == 0) || ((this->grid[(X + WIDTH * Y)/TILE_SIZE].type == 4) && (!hasFood)))
        {
            pos.x = (pos.x + x);
            pos.y = (pos.y + y);
            _ants.at(i)->setPos(pos);
            _ants.at(i)->setAngle(angle);
            _ants.at(i)->antSprite.setPosition(_ants.at(i)->pos);
            _ants.at(i)->antSprite.setRotation(_ants.at(i)->angle);
        }
        else if((this->grid[(X + WIDTH * Y)/TILE_SIZE].type == 2) && (!hasFood))
        {
            _ants.at(i)->hasFood = true;
            _ants.at(i)->antSprite.setTexture(this->_data->assets.GetTexture("ANT FOOD"));
            _ants.at(i)->pheromoneAmount = 500;
            this->grid[(X + WIDTH * Y)/TILE_SIZE].foodAmount = this->grid[(X + WIDTH * Y)/TILE_SIZE].foodAmount - this->carryCapacity;

            if(this->grid[(X + WIDTH * Y)/TILE_SIZE].foodAmount <= 0)
            {
                this->grid[(X + WIDTH * Y)/TILE_SIZE].foodAmount = 0;
                this->grid[(X + WIDTH * Y)/TILE_SIZE].type = 0;
                //map.load("Assets/Graphics/tileMap.png", sf::Vector2u(tileSize, tileSize), level, WIDTH, HEIGHT);
                //rebuild
            }
            angle = antReverse(angle);
            _ants.at(i)->setAngle(angle);
            _ants.at(i)->antSprite.setPosition(_ants.at(i)->pos);
            _ants.at(i)->antSprite.setRotation(_ants.at(i)->angle);
        }
        else
        {
            angle = antBounce(*_ants.at(i), X, Y);
            _ants.at(i)->setAngle(angle);
            _ants.at(i)->antSprite.setPosition(_ants.at(i)->pos);
            _ants.at(i)->antSprite.setRotation(_ants.at(i)->angle);
        }

        if((!hasFood) && (_ants.at(i)->pheromoneAmount > 0) && (this->grid[(X + WIDTH * Y)/TILE_SIZE].pherHomeAmount < _ants.at(i)->pheromoneAmount))
        {
            _ants.at(i)->pheromoneAmount--;
            this->grid[(X + WIDTH * Y)/TILE_SIZE].pherHome = true;
            //this->grid[X + WIDTH * Y].time = dt;//elapsed;
            this->grid[(X + WIDTH * Y)/TILE_SIZE].toHomeAngle = antReverse(angle);
            this->grid[(X + WIDTH * Y)/TILE_SIZE].pherHomeAmount = _ants.at(i)->pheromoneAmount;
        }
        else if((hasFood) && (_ants.at(i)->pheromoneAmount > 0) && (this->grid[(X + WIDTH * Y)/TILE_SIZE].pherFoodAmount < _ants.at(i)->pheromoneAmount))
        {
            _ants.at(i)->pheromoneAmount--;
            this->grid[(X + WIDTH * Y)/TILE_SIZE].pherFood = true;
            //this->grid[X + WIDTH * Y].time = dt;//elapsed;
            this->grid[(X + WIDTH * Y)/TILE_SIZE].toFoodAngle = antReverse(angle);
            this->grid[(X + WIDTH * Y)/TILE_SIZE].pherFoodAmount = _ants.at(i)->pheromoneAmount;
        }

        //std::cout << X << " " << Y << " " << std::endl;
    }
}

float Colony::findAngle(Ant &A)
{
    int start_X = A.pos.x;//colPos.x; // center point
    int start_Y = A.pos.y;//colPos.y;

    int r = range;

    float angle = A.angle;
    float sAngle = A.angle - rangeWidth;
    float eAngle = A.angle + rangeWidth;
    bool check = false;
    
    if(sAngle < 0)
        sAngle+=360;
    if(eAngle < sAngle)
        eAngle+=360;
    
    double curCos = std::cos(sAngle);
    double curSin = std::sin(sAngle);
    double curTan = curSin/curCos;
    double newCos = std::cos(eAngle);
    double newSin = std::sin(eAngle);
    double newTan = newSin/newCos;
    double xMax = curCos*range;
    double r2 = range*range;

    int highX;
    int highY;
    int highAmount = 0;
    float distance = 30.0;
    int newAngle;

    if(A.hasFood)
    {
        for(int x = start_X - r; x < start_X + r; x++)
        {
            for(int y = start_Y - r; y < start_Y + r; y++)
            {
                float deltaX = x - start_X;
                float deltaY = y - start_Y;
                float num = atan2(deltaY,deltaX) * 180 / 3.14;
                if((num < 0) || ((num < sAngle) && (num < eAngle)))
                    num +=360;

                if(((x-start_X)*(x-start_X) + (y-start_Y)*(y-start_Y) <= r*r) && 
                (num > sAngle) && (num < eAngle) && 
                (x > 0) && (x < WIDTH) && (y > 0) && (y < HEIGHT))
                {
                    if(this->grid[(x + WIDTH * y)/TILE_SIZE].type == 4)
                    {
                        highX = x;
                        highY = y;
                        int newY = highY - start_Y;
                        int newX = highX - start_X;
                        int newAngle = atan2(newY, newX) * 180 / 3.14;
                        if(newAngle < 0)
                            newAngle += 360;
                        return newAngle;
                    }
                    if((this->grid[(x + WIDTH * y)/TILE_SIZE].pherHome == true) && (this->grid[(x + WIDTH * y)/TILE_SIZE].pherHomeAmount > highAmount))
                    {
                        highX = x;
                        highY = y;
                        highAmount = this->grid[(x + WIDTH * y)/TILE_SIZE].pherHomeAmount;
                    }
                }
            }
        }
    }
    else
    {
        for(int x = start_X - r; x < start_X + r; x++)
        {
            for(int y = start_Y - r; y < start_Y + r; y++)
            {
                float deltaX = x - start_X;
                float deltaY = y - start_Y;
                float num = atan2(deltaY,deltaX) * 180 / 3.14;
                if((num < 0) || ((num < sAngle) && (num < eAngle)))
                    num +=360;

                if(((x-start_X)*(x-start_X) + (y-start_Y)*(y-start_Y) <= r*r) && 
                (num > sAngle) && (num < eAngle) && 
                (x > 0) && (x < WIDTH) && (y > 0) && (y < HEIGHT))
                {
                    if(this->grid[(x + WIDTH * y)/TILE_SIZE].type == 2)
                    {
                        check = true;
                        int newY = highY - start_Y;
                        int newX = highX - start_X;
                        int tempX = pow(deltaX,2);
                        int tempY = pow(deltaY,2);
                        //std::cout << deltaX << " " << tempX << " " << deltaY << " " << tempY << std::endl;
                        float temp = sqrt(tempX + tempY);
                        //std::cout << temp << std::endl;
                        if(temp < distance)
                        {
                            distance = temp;
                            newAngle = atan2(deltaY, deltaX) * 180 / 3.14;
                            //newAngle = atan2(newY, newX) * 180 / 3.14;
                            
                            if(newAngle < 0)
                                newAngle += 360;
                            //std::cout << newAngle << std::endl;
                        }
                    }
                    else if((this->grid[(x + WIDTH * y)/TILE_SIZE].hasFood == false) && (this->grid[(x + WIDTH * y)/TILE_SIZE].pherFoodAmount > highAmount))
                    {
                        highX = x;
                        highY = y;
                        highAmount = this->grid[(x + WIDTH * y)/TILE_SIZE].pherFoodAmount;
                        check = true;
                        //calculate angle
                    }     
                }
            }
        }
    }

    
    if(distance < 30.0)
        return newAngle;

    if(highAmount > 0)
    {
        int newY = highY - start_Y;
        int newX = highX - start_X;
        int newAngle = atan2(newY, newX) * 180 / 3.14;
        if(newAngle < 0)
            newAngle += 360;
        return newAngle;
    }

    if(check == false)
    {
        float temp = rand() % 11 - 5;
        newAngle = angle + temp;
    }
        if(newAngle > 360)
            newAngle -= 360;
        
        if(newAngle < 0)
            newAngle += 360;

    return newAngle;
}

/* void Colony::pherSimulate(sf::Time elapsed)
{

} */

float Colony::antBounce(Ant &A, int X, int Y)
{

    float angle = A.getAngle();
    int startX = A.pos.x;
    int startY = A.pos.y;

    std::cout << startX << " " << startY  << " " << X << " " <<  Y << std::endl;
    if((angle >= 0) && (angle < 90) && (this->grid[(startX + WIDTH * Y)].type != 1))
    {
        angle = angle + 110;
    }
    else if((angle >= 0) && (angle < 90) && (this->grid[(X + WIDTH * startY)].type != 1))
    {
        angle = angle - 110;
    }
    else if((angle >= 90) && (angle < 180) && (this->grid[(startX + WIDTH * Y)].type != 1))
    {
        angle = angle - 110;
    }
    else if((angle >= 90) && (angle < 180) && (this->grid[(X + WIDTH * startY)].type != 1))
    {
        angle = angle + 110;
    }
    else if((angle >= 180) && (angle < 270) && (this->grid[(startX + WIDTH * Y)].type != 1))
    {
        angle = angle + 110;
    }
    else if((angle >= 180) && (angle < 270) && (this->grid[(X + WIDTH * startY)].type != 1))
    {
        angle = angle - 110;
    }
    else if((angle >= 270) && (angle <= 360) && (this->grid[(startX + WIDTH * Y)].type != 1))
    {
        angle = angle - 110;
    }
    else if((angle >= 270) && (angle <= 360) && (this->grid[(X + WIDTH * startY)].type != 1))
    {
        angle = angle + 110;
    }

    if(angle < 0)
        angle+= 360;
    if(angle > 360)
        angle-=360;
    return angle;
}

float Colony::antReverse(float angle)
{
    angle -= 180;
    if(angle < 0)
        angle +=360;

    return angle;
}