#include "Colony.hpp"

Colony::Colony( GameDataRef data , int ID) : _data( data )
{


    id = ID;

    for(int x = 0; x < WIDTH; x++)
    {
        for(int y = 0; y < HEIGHT; y++)
        {
            int spot = x + WIDTH * y;

            if(this->_data->grid[spot]->type == 3)
            {
                colPos.x = x * TILE_SIZE;
                colPos.y = y * TILE_SIZE;
            }
        }
    }

    nest.setTexture(this->_data->assets.GetTexture("NEST"));
    nest.setOrigin(32.f, 32.f);
    nest.setScale(0.5,0.5);
    nest.setPosition(colPos.x, colPos.y);

    for(int i = 0; i < COLONY_START_SIZE; i++)
    {
        ant = new Ant(this->_data);
        ant->setPos(this->colPos);
        ant->colonyID = ID;
        //ant->antSprite.setTexture(this->_data->assets.GetTexture("ANT"));
        //ant->antSprite.setColor(sf::Color::Red);
        _ants.push_back(ant);
    }
}

void Colony::drawColony()
{
    // draws pheromone tiles
/*     for(int i = 0; i < WIDTH * HEIGHT; i++)
    {
        if(this->grid[i]->vision || (this->grid[i]->pherFoodAmount > 0) || (this->grid[i]->pherHomeAmount > 0))
        {
            this->grid[i]->vision = false;
        }

    } */

    // draws the nest
    this->_data->window.draw(nest);

    // draws ants
    for(int i = 0; i < _ants.size(); i++)
    {
        this->_data->window.draw(_ants[i]->antSprite);
    }
}

void Colony::colonySimulate(float dt)
{
    for(int i = 0; i < _ants.size(); i++)
    {
        //Ant *A = _ants[i];
        float movement = this->speed * dt;

        sf::Vector2f pos = _ants[i]->getPos();
        float angle = findAngle(*_ants[i]);
        //std::cout << "Angle = " << angle << std::endl;

        bool hasFood = _ants[i]->hasFood;
        float temp = rand() % 11 - 5;

        float rad = angle / 57.2958;
        //float x = 1.0f * cos(rad);
        //float y = 1.0f * sin(rad);
        float x = movement * cos(rad);
        float y = movement * sin(rad);
        int X = (pos.x + x);
        int Y = (pos.y + y);
        int spot = (((X/TILE_SIZE) + WIDTH * (Y/TILE_SIZE)));

        bool foodDataCheck = false;
        int foodDataIndex = 0;

        //int foodSize = this->_data->food.size();

/*         if(!hasFood)
        {
            for(int j = 0; j < foodSize; j++)
            {
                if(this->_data->food[j].CheckSpot((X/TILE_SIZE), (Y/TILE_SIZE)) == true)
                {
                    foodDataCheck = true;
                    foodDataIndex = j;
                }

            }
        } */

        if((this->_data->grid[spot]->type == 3) && (hasFood))
        {
            pos.x = pos.x + x;
            pos.y = pos.y + y;
            _ants[i]->setPos(pos);
            _ants[i]->hasFood = false;
            _ants[i]->pheromoneAmount = 500;
            angle = antReverse(angle);
            _ants[i]->setAngle(angle);

            foodReturned = foodReturned + this->carryCapacity;
            if(foodReturned >= 5)
            {
                foodReturned = 0;
                colSize+=1;
            }
        }
        else if((this->_data->grid[spot]->hasFood) && (!hasFood)) // ANT FOUND FOOD
        {
            _ants[i]->hasFood = true;
            _ants[i]->pheromoneAmount = 500;

            if(this->_data->grid[spot]->foodAmount-=carryCapacity <= 0)
            {
                this->_data->grid[spot]->foodAmount = 0;
                this->_data->grid[spot]->type = 0;
                //foodDataCheck = false;
                //foodDataIndex = 0;
            }

            angle = antReverse(angle);
            _ants[i]->setAngle(angle);
        }
        else if((this->_data->grid[spot]->type == 0) && (hasFood) && (this->_data->grid[spot]->pherHomeAmount > 0))
        {
            pos.x = pos.x + x;
            pos.y = pos.y + y;
            _ants[i]->setPos(pos);
            _ants[i]->setAngle(angle);
        }
        else if((this->_data->grid[spot]->type == 0) && (!hasFood) && (this->_data->grid[spot]->pherFoodAmount > 0))
        {
            pos.x = pos.x + x;
            pos.y = pos.y + y;
            _ants[i]->setPos(pos);
            _ants[i]->setAngle(angle);
        }
        else if((this->_data->grid[spot]->type == 0) || ((this->_data->grid[spot]->type == 3) && (!hasFood)))
        {
            pos.x = (pos.x + x);
            pos.y = (pos.y + y);
            _ants[i]->setPos(pos);
            _ants[i]->setAngle(angle);
        }
        else
        {
            angle = antBounce(*_ants[i], (X/TILE_SIZE), (Y/TILE_SIZE));
            _ants[i]->setAngle(angle);
        }

        if((!hasFood) && (_ants[i]->pheromoneAmount > 0) && (this->_data->grid[spot]->pherHomeAmount[id][0] < _ants[i]->pheromoneAmount))
        {
            _ants[i]->pheromoneAmount--;
            this->_data->grid[spot]->pherHome[id][0] = true;
            //this->_data->grid[spot]->toHomeAngle = antReverse(angle);
            this->_data->grid[spot]->pherHomeAmount[id][0] = _ants[i]->pheromoneAmount;

            bool update = false;
            int index = -1;

            for(int k = 0; k < this->_pheromoneList.size(); k++)
            {
                if(this->_pheromoneList.at(k)->arrayPos == spot)
                {
                    update = true;
                    index = k;
                    break;
                }
            }

            if(update)
            {
                this->_pheromoneList.at(index) = this->_data->grid[spot];
                index = -1;
                update = false;
            }
            else
            {
                this->_pheromoneList.push_back(this->_data->grid[spot]);
            }
        }
        else if((hasFood) && (_ants[i]->pheromoneAmount > 0) && (this->_data->grid[spot]->pherFoodAmount[id][0] < _ants[i]->pheromoneAmount))
        {
            _ants[i]->pheromoneAmount--;
            this->_data->grid[spot]->pherFood[id][0] = true;
            //this->_data->grid[spot]->toFoodAngle = antReverse(angle);
            this->_data->grid[spot]->pherFoodAmount[id][0] = _ants[i]->pheromoneAmount;

            bool update = false;
            int index = -1;

            for(int k = 0; k < this->_pheromoneList.size(); k++)
            {
                if(this->_pheromoneList.at(k)->arrayPos == spot)
                {
                    update = true;
                    index = k;
                    break;
                }
            }

            if(update)
            {
                this->_pheromoneList.at(index) = this->_data->grid[spot];
                index = -1;
                update = false;
            }
            else
            {
                this->_pheromoneList.push_back(this->_data->grid[spot]);
            }
        }
    }
}

void Colony::pheromoneSimulate(float dt)
{
    for(int i = 0; i < this->_pheromoneList.size(); i++)
    {
        if(this->_pheromoneList[i]->pherFoodAmount > 0)
            this->_pheromoneList[i]->pherFoodAmount[id][0]--;

        if(this->_pheromoneList[i]->pherHomeAmount > 0)
            this->_pheromoneList[i]->pherHomeAmount[id][0]--;

        if(this->_pheromoneList[i]->pherHomeAmount == 0)
            this->_pheromoneList[i]->pherHome[id][0] = false;

        if(this->_pheromoneList[i]->pherFoodAmount == 0)
            this->_pheromoneList[i]->pherFood[id][0] = false;

        if(this->_pheromoneList[i]->pherHome[id][0] == false && this->_pheromoneList[i]->pherFood[id][0] == false)// && this->_pheromoneList[i]->vision == false)
            _pr.removePheromone(this->_pheromoneList[i]->arrayPos);
    }

    _pr.update(this->_pheromoneList, id);
}

float Colony::findAngle(Ant &A)
{

    int start_X = A.pos.x;//colPos.x; // center point
    int start_Y = A.pos.y;//colPos.y;
    // std::cout << A.pos.x << " " << A.pos.y << std::endl;
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
    float distance = 30;
    int newAngle;

    float _mult = (180.0 / 3.14);

    if(A.hasFood)
    {
        int _xStart = (cos(sAngle) > 0) ? start_X : start_X - r;
        int _yStart = (sin(sAngle) > 0) ? start_Y : start_Y - r;
        int _xEnd = (cos(eAngle) > 0) ? start_X + r : start_X;
        int _yEnd = (sin(eAngle) > 0) ? start_Y + r : start_Y;

        for (int x = _xStart; x < _xEnd; x++)
        {
            int _xCheck = x - start_X;
            int _rCheck = r*r;
            int _xDivCheck = x/TILE_SIZE;

            for (int y = _yStart; y < _yEnd; y++)
            {
                int spot = ((_xDivCheck) + WIDTH * (y/TILE_SIZE));
                
                float deltaX = _xCheck;
                float deltaY = y - start_Y;
                float num = atan2(deltaY,deltaX) * _mult; //180 / 3.14;
                if ((num < 0) || ((num < sAngle) && (num < eAngle)))
                {
                    num +=360;
                }


          

                if (((_xCheck)*(_xCheck) + (y-start_Y)*(y-start_Y) <= _rCheck) &&
                    (num > sAngle) &&
                    (num < eAngle) &&
                    (x > 0) &&
                    ((_xDivCheck) < WIDTH) &&
                    (y > 0) &&
                    ((y/TILE_SIZE) < HEIGHT))
                {
                    //if (this->_data->grid[spot]->type == 0)
                    //{
                    //this->_data->grid[spot]->vision = true;
                    //}

                        //this->_data->grid[spot]->vision = true;
                        //this->_pheromoneList.push_back(this->_data->grid[spot]);
                    if (this->_data->grid[spot]->type == 3)
                    {
                        highX = x;
                        highY = y;
                        int newY = highY - start_Y;
                        int newX = highX - start_X;
                        int newAngle = atan2(newY, newX) * _mult; //180 / 3.14;

                        if(newAngle < 0)
                        {
                            newAngle += 360;
                        }

                        return newAngle;
                    }

                    if ((this->_data->grid[spot]->pherHome[id][0] == true) && (this->_data->grid[spot]->pherHomeAmount[id][0] > highAmount))
                    {
                        highX = x;
                        highY = y;
                        highAmount = this->_data->grid[spot]->pherHomeAmount[id][0];
                    }
                }
            }
        }
    }
    else
    {

        int _xStart = (cos(sAngle) > 0) ? start_X : start_X - r;
        int _yStart = (sin(sAngle) > 0) ? start_Y : start_Y - r;
        int _xEnd = (cos(eAngle) > 0) ? start_X + r : start_X;
        int _yEnd = (sin(eAngle) > 0) ? start_Y + r : start_Y;

        //int foodSize = this->_data->food.size();
        for (int x = _xStart; x < _xEnd; x++)
        {
            int _xCheck = x - start_X;
            int _xCheckSquared = _xCheck*_xCheck;
            int _rCheck = r*r;
            int _xDivCheck = x/TILE_SIZE;
            int _tempX = pow(_xCheck, 2);

            for (int y = _yStart; y < _yEnd; y++)
            {
                int _yDivCheck = y/TILE_SIZE;

                int spot = ((_xDivCheck) + WIDTH * (_yDivCheck));
/*                 bool foodDataCheck = false;
                //std::cout << x << " " << y << std::endl;

                for (int j = 0; j < foodSize; j++)
                {
                    if (this->_data->food[j].CheckSpot(_xDivCheck,_yDivCheck))
                    {
                        foodDataCheck = true;
                        //std::cout << foodDataCheck << std::endl;
                    }

                } */

                float deltaX = _xCheck;
                float deltaY = y - start_Y;
                float angleCalc = atan2(deltaY,deltaX) * _mult; //180 / 3.14;
                float num = angleCalc; //atan2(deltaY,deltaX) * _mult; //180 / 3.14;
                if ((num < 0) || ((num < sAngle) && (num < eAngle)))
                {
                    num += 360;
                }

                if ((_xCheckSquared + (deltaY)*(deltaY) <= _rCheck) &&
                    (num > sAngle) &&
                    (num < eAngle) &&
                    (x > 0) &&
                    ((_xDivCheck) < WIDTH) &&
                    (y > 0) &&
                    ((_yDivCheck) < HEIGHT))
                {
                    //if(this->_data->grid[spot]->type == 0)
                    //{
                    //this->_data->grid[spot]->vision = true;
                    //}


                    if (this->_data->grid[spot]->hasFood)
                    {
                        check = true;
                        int newY = highY - start_Y;
                        int newX = highX - start_X;
                        int tempX = _tempX; //pow(deltaX,2);
                        int tempY = pow(deltaY,2);
                        //std::cout << deltaX << " " << tempX << " " << deltaY << " " << tempY << std::endl;
                        float temp = sqrt(tempX + tempY);
                        //std::cout << temp << std::endl;
                        if(temp < distance)
                        {
                            distance = temp;
                            newAngle = angleCalc; //atan2(deltaY, deltaX) * _mult; //180 / 3.14;
                            //newAngle = atan2(newY, newX) * 180 / 3.14;

                            if(newAngle < 0)
                                newAngle += 360;
                            //std::cout << newAngle << std::endl;
                        }
                    }
                    else if ((this->_data->grid[spot]->hasFood == false) && (this->_data->grid[spot]->pherFoodAmount[id][0] > highAmount))
                    {
                        highX = x;
                        highY = y;
                        highAmount = this->_data->grid[spot]->pherFoodAmount[id][0];
                        check = true;
                        //calculate angle
                    }
                }

                //foodDataCheck = false;
            }
        }
    }


    if (distance < 30.0)
    {
        return newAngle;
    }

    if (highAmount > 0)
    {
        int newY = highY - start_Y;
        int newX = highX - start_X;
        int newAngle = atan2(newY, newX) * _mult; //180 / 3.14;

        if (newAngle < 0)
        {
            newAngle += 360;
        }

        return newAngle;
    }

    if (check == false)
    {
        float temp = rand() % 11 - 5;
        newAngle = angle + temp;
    }

    if(newAngle > 360)
    {
        newAngle -= 360;
    }

    if(newAngle < 0)
    {
        newAngle += 360;
    }

    return newAngle;
}

/* void Colony::pherSimulate(sf::Time elapsed)
{

} */

float Colony::antBounce(Ant &A, int X, int Y)
{

    float angle = A.getAngle();
    int startX = A.pos.x/TILE_SIZE;
    int startY = A.pos.y/TILE_SIZE;

    //std::cout << startX << " " << startY  << " " << X << " " <<  Y << std::endl;

    if((angle >= 0) && (angle < 90))
    {
        if((this->_data->grid[(startX + WIDTH * Y)]->type != 1) && (this->_data->grid[(X + WIDTH * startY)]->type == 1))
            angle = rand() % 90 + 90;
        else if((this->_data->grid[(startX + WIDTH * Y)]->type == 1) && (this->_data->grid[(X + WIDTH * startY)]->type != 1))
            angle = rand() % 90 + 270;
        else
            angle = antReverse(angle);
    }
    else if((angle >= 90) && (angle < 180))
    {
        if((this->_data->grid[(startX + WIDTH * Y)]->type != 1) && (this->_data->grid[(X + WIDTH * startY)]->type == 1))
            angle = rand() % 90 + 1;
        else if((this->_data->grid[(startX + WIDTH * Y)]->type == 1) && (this->_data->grid[(X + WIDTH * startY)]->type != 1))
            angle = rand() % 90 + 180;
        else
            angle = antReverse(angle);
    }
    else if((angle >= 180) && (angle < 270))
    {
        if((this->_data->grid[(startX + WIDTH * Y)]->type != 1) && (this->_data->grid[(X + WIDTH * startY)]->type == 1))
            angle = rand() % 90 + 270;
        else if((this->_data->grid[(startX + WIDTH * Y)]->type == 1) && (this->_data->grid[(X + WIDTH * startY)]->type != 1))
            angle = rand() % 90 + 90;
        else
            angle = antReverse(angle);
    }
    else if((angle >= 270) && (angle <= 360))
    {
        if((this->_data->grid[(startX + WIDTH * Y)]->type != 1) && (this->_data->grid[(X + WIDTH * startY)]->type == 1))
            angle = rand() % 90 + 180;
        else if((this->_data->grid[(startX + WIDTH * Y)]->type == 1) && (this->_data->grid[(X + WIDTH * startY)]->type != 1))
            angle = rand() % 90 + 1;
        else
            angle = antReverse(angle);

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