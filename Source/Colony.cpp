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
        sf::Vector2f pos = colPos; // delete later
        pos.x+=4; // delete later
        pos.y+= 4; // delete later
        ant->setPos(pos); // send colpos later
        ant->colonyID = ID;
        _ants.push_back(ant);
    }
}


void Colony::colonySimulate(float dt)
{
/*     int size = _visionList.size();
    for(int i = 0; i < _visionList.size(); i++)
    {
            //std::cout << this->_data->grid[_visionList[i]]->timeCheck << std::endl;
            this->_data->grid[_visionList[i]]->vision = false;
            _pr.removeVision(_visionList[i]);  
    }
    _visionList.clear(); */

    for(int i = 0; i < _ants.size(); i++)
    {
        float movement = this->speed * dt;
        sf::Vector2f pos = _ants[i]->getPos();
        bool hasFood = _ants[i]->hasFood;
        float angle;
        hasFood ? (angle = findHome(*_ants[i], dt)) : (angle = findFood(*_ants[i], dt));
        
        float rad = angle / 57.2958;

        float x = movement * cos(rad);
        float y = movement * sin(rad);
        int X = (pos.x + x);
        int Y = (pos.y + y);
        int spot = (((X/TILE_SIZE) + WIDTH * (Y/TILE_SIZE)));

        bool foodDataCheck = false;
        int foodDataIndex = 0;
        
        //std::cout << this->_data->grid[spot]->type << std::endl;

        if((this->_data->grid[spot]->type == 3) && (hasFood))
        {
            pos.x = pos.x + x;
            pos.y = pos.y + y;
            _ants[i]->setPos(pos);
            _ants[i]->hasFood = false;
            _ants[i]->pheromoneAmount = 1000;
            angle = antReverse(angle);
            _ants[i]->setAngle(angle);

            foodReturned = foodReturned + this->carryCapacity;
            if(foodReturned >= 5)
            {
                foodReturned-=5;
                colSize+=1;
                ant = new Ant(this->_data);
                ant->setPos(this->colPos);
                ant->colonyID = id;
                _ants.push_back(ant);
            }
        }
        else if((this->_data->grid[spot]->type == 3) && (!hasFood))
        {
            pos.x = pos.x + x;
            pos.y = pos.y + y;
            _ants[i]->setPos(pos);
            _ants[i]->pheromoneAmount = 1000;
            _ants[i]->setAngle(angle);
        }
        else if((this->_data->grid[spot]->hasFood) && (!hasFood)) // ANT FOUND FOOD
        {
            //std::cout << "ant got food" << std::endl;
            _ants[i]->hasFood = true;
            _ants[i]->pheromoneAmount = 1000;

            if(this->_data->grid[spot]->foodAmount-=carryCapacity <= 0)
            {
                this->_data->grid[spot]->foodAmount = 0;
                this->_data->grid[spot]->type = 0;
                this->_data->grid[spot]->hasFood = false;
                this->_data->map.removeFood(spot);
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
            //std::cout << "no food" << std::endl;
            this->_data->grid[spot]->pherHome[id][0] = true;
            this->_data->grid[spot]->pherHomeAmount[id][0] = _ants[i]->pheromoneAmount;
            
            _ants[i]->pheromoneAmount-=2;
            if(_ants[i]->pheromoneAmount < 0)
                _ants[i]->pheromoneAmount = 0;

            //this->_data->grid[spot]->toHomeAngle = antReverse(angle);
            

            bool update = false;
            int index = -1;

            for(int k = 0; k < this->_pheromoneList.size(); k++)
            {
                if(this->_pheromoneList[k] == spot)
                {
                    update = true;
                    index = k;
                    break;
                }
            }

            if(update)
            {
                this->_pheromoneList[index] = this->_data->grid[spot]->arrayPos;
                index = -1;
                update = false;
            }
            else
            {
                this->_pheromoneList.push_back(this->_data->grid[spot]->arrayPos);
            }
        }
        else if((hasFood) && (_ants[i]->pheromoneAmount > 0) && (this->_data->grid[spot]->pherFoodAmount[id][0] < _ants[i]->pheromoneAmount))
        {
            //std::cout << "yes food" << std::endl;
            _ants[i]->pheromoneAmount-=2;
            if(_ants[i]->pheromoneAmount < 0)
                _ants[i]->pheromoneAmount = 0;
            this->_data->grid[spot]->pherFood[id][0] = true;
            //this->_data->grid[spot]->toFoodAngle = antReverse(angle);
            this->_data->grid[spot]->pherFoodAmount[id][0] = _ants[i]->pheromoneAmount;

            bool update = false;
            int index = -1;

            for(int k = 0; k < this->_pheromoneList.size(); k++)
            {
                if(this->_pheromoneList[k] == spot)
                {
                    update = true;
                    index = k;
                    break;
                }
            }

            if(update)
            {
                this->_pheromoneList[index] = this->_data->grid[spot]->arrayPos;
                index = -1;
                update = false;
            }
            else
            {
                this->_pheromoneList.push_back(this->_data->grid[spot]->arrayPos);
            }
        }
    }
}

void Colony::pheromoneSimulate(float dt)
{
    bool remove = false;
    int removeSpot = -1;
    float change = pherDisolveSpeed * dt;
    //std::cout << change << std::endl;

    
    for(int i = 0; i < this->_pheromoneList.size(); i++)
    {
        int spot = _pheromoneList[i];
        if(this->_data->grid[spot]->pherFoodAmount[id][0] > 0)
            this->_data->grid[spot]->pherFoodAmount[id][0]-=change;

        if(this->_data->grid[spot]->pherHomeAmount[id][0] > 0)
            this->_data->grid[spot]->pherHomeAmount[id][0]-=change;

        if(this->_data->grid[spot]->pherHomeAmount[id][0] <= 0)
            this->_data->grid[spot]->pherHome[id][0] = false;

        if(this->_data->grid[spot]->pherFoodAmount[id][0] <= 0)
            this->_data->grid[spot]->pherFood[id][0] = false;

        if(this->_data->grid[spot]->pherHome[id][0] == false && this->_data->grid[spot]->pherFood[id][0] == false)// && this->_pheromoneList[i]->vision == false)
        {
            _pr.removePheromone(spot);
            remove = true;
            removeSpot = i;
        }
            
    }

    if(remove)
    {
        _pheromoneList.erase(_pheromoneList.begin() + removeSpot);
        remove = false;
        removeSpot = -1;
    }

    _pr.vision(this->_visionList);
        

    _pr.update(this->_pheromoneList, id, this->_data);
}

float Colony::findHome(Ant &A, float dt)
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
    float distance = 30.0;
    int newAngle;

    float _mult = (180.0 / 3.14);

    int _xStart = start_X - r;//(cos(sAngle) > 0) ? start_X : start_X - r;
    int _yStart = start_Y - r;//(sin(sAngle) > 0) ? start_Y : start_Y - r;
    int _xEnd = start_X + r;//(cos(eAngle) > 0) ? start_X + r : start_X;
    int _yEnd = start_Y + r;//(sin(eAngle) > 0) ? start_Y + r : start_Y;

    for (int x = _xStart; x < _xEnd; x++)
    {
        int _xCheck = x - start_X;
        int _rCheck = r*r;
        int _xDivCheck = x/TILE_SIZE;

        for (int y = _yStart; y < _yEnd; y++)
        {
             int _yDivCheck = y/TILE_SIZE;
            int spot = ((_xDivCheck) + WIDTH * (y/TILE_SIZE));
            
            float deltaX = _xCheck;
            float deltaY = y - start_Y;
            float num = atan2(deltaY,deltaX) * _mult; //180 / 3.14;
            if ((num < 0) || ((num < sAngle) && (num < eAngle)))
            {
                num +=360;
            }


        
            //std::cout << "XcheckSquared |  DeltaY * deltaY | rCheck   |   num     |    sAngle    | eAgnle | xDivCheck | yDivCheck" << std::endl;
            //std::cout << (_xCheck)*(_xCheck) << "                      " << (deltaY)*(deltaY) << "        " << _rCheck << "       " << num << "         " << sAngle << "          " << eAngle << "      " << _xDivCheck << "          " << _yDivCheck << std::endl; 

            if (((_xCheck)*(_xCheck) + (y-start_Y)*(y-start_Y) <= _rCheck) &&
                (num > sAngle) &&
                (num < eAngle) &&
                (x > 0) &&
                ((_xDivCheck) < WIDTH) &&
                (y > 0) &&
                ((y/TILE_SIZE) < HEIGHT))
            {

/*                 if(this->_data->grid[spot]->vision == false)
                {
                    this->_data->grid[spot]->vision = true;
                    //this->_data->grid[spot]->timeCheck+=dt;
                    _visionList.push_back(spot);
                } */

                if (this->_data->grid[spot]->type == 3)
                {
                    //std::cout << "found HOME!!" << std::endl;
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
                    //std::cout << highAmount << std::endl;
                }
            }
        }
    }
    if (highAmount > 0)
    {
        //std::cout << highAmount << std::endl;
        int newY = highY - start_Y;
        int newX = highX - start_X;
        int newAngle = atan2(newY, newX) * _mult; //180 / 3.14;
        
        if (newAngle < 0)
        {
            newAngle += 360;
        }
        //std::cout << newAngle << std::endl;

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


float Colony::findFood(Ant &A, float dt)
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
    float distance = 30.0;
    int newAngle;

    float _mult = (180.0 / 3.14);

    int _xStart = start_X - r; //(cos(sAngle) > 0) ? start_X : start_X - r;
    int _yStart = start_Y - r;//(sin(sAngle) > 0) ? start_Y : start_Y - r;
    int _xEnd = start_X + r;//(cos(eAngle) > 0) ? start_X + r : start_X;
    int _yEnd = start_Y + r;//(sin(eAngle) > 0) ? start_Y + r : start_Y;

    //std::cout << _xStart << " " << _xEnd << " "<< _yStart << " " << _yEnd << std::endl;  

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

            float deltaX = _xCheck;
            float deltaY = y - start_Y;
            float angleCalc = atan2(deltaY,deltaX) * _mult; //180 / 3.14;
            float num = angleCalc; //atan2(deltaY,deltaX) * _mult; //180 / 3.14;
            if ((num < 0) || ((num < sAngle) && (num < eAngle)))
            {
                num += 360;
            }
            //if(num > 360)
             //   num-=360;
           
            //std::cout << "XcheckSquared |  DeltaY * deltaY | rCheck   |   num     |    sAngle    | eAgnle | xDivCheck | yDivCheck" << std::endl;
            //std::cout << _xCheckSquared << "                      " << (deltaY)*(deltaY) << "        " << _rCheck << "       " << num << "         " << sAngle << "          " << eAngle << "      " << _xDivCheck << "          " << _yDivCheck << std::endl; 
            
            if ((_xCheckSquared + (deltaY)*(deltaY) <= _rCheck) &&
                (num > sAngle) &&
                (num < eAngle) &&
                (x > 0) &&
                ((_xDivCheck) < WIDTH) &&
                (y > 0) &&
                ((_yDivCheck) < HEIGHT))
            {

                

/*                 if(this->_data->grid[spot]->vision == false)
                {
                    //std::cout << spot << std::endl;
                    
                    this->_data->grid[spot]->vision = true;
                    //std::cout << this->_data->grid[spot]->vision << std::endl;
                    //this->_data->grid[spot]->timeCheck+=dt;
                    _visionList.push_back(spot);
                } */


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
                }
            }
        }
    }

    if (distance < 30.0)
    {
        //std::cout << "distance less than 30" << std::endl;
        return newAngle;
    }

    //std::cout << "Distance greater than 30" << std::endl;

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