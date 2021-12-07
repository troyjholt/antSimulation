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
                //std::cout << grid[x + WIDTH * y].type << " ";
                if(grid[x + WIDTH * y].type == 3)
                {
                    colPos.x = x * TILE_SIZE;
                    colPos.y = y * TILE_SIZE;
                }
                else
                {
                    grid[x + WIDTH * y].shape.setPosition(x*TILE_SIZE, y*TILE_SIZE);
                    grid[x + WIDTH * y].shape.setSize(sf::Vector2f(TILE_SIZE,TILE_SIZE));
                    if(grid[x + WIDTH * y].type == 2)
                        grid[x + WIDTH * y].type = 0;
                }
            }
            //std::cout << std::endl;
        }
        //std::cout << colPos.x << " " << colPos.y << std::endl;
    }

    readFile.close();

    nest.setTexture(this->_data->assets.GetTexture("NEST"));
    nest.setOrigin(32.f, 32.f);
    nest.setScale(0.5,0.5);
    nest.setPosition(colPos.x, colPos.y);

    for(int i = 0; i < COLONY_START_SIZE; i++)
    {
        ant = new Ant(this->_data);
        ant->setPos(this->colPos);
        ant->colonyID = ID;
        ant->antSprite.setTexture(this->_data->assets.GetTexture("ANT"));
        //ant->antSprite.setColor(sf::Color::Red);
        _ants.push_back(ant);
    }
}

void Colony::drawColony()
{
    // draws pheromone tiles
    for(int i = 0; i < WIDTH * HEIGHT; i++)
    {
        if(this->grid[i].vision || (this->grid[i].pherFoodAmount > 0) || (this->grid[i].pherHomeAmount > 0))
        {
            if(this->grid[i].vision)
                this->grid[i].shape.setFillColor(sf::Color::Yellow);
            this->grid[i].vision = false;
            
            //std::cout << i << " turned to false" << std::endl;
            this->_data->window.draw(this->grid[i].shape);
        }
        
    }

    // draws the nest
    this->_data->window.draw(nest);

    // draws ants
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
        int X = (pos.x + x);
        int Y = (pos.y + y);
        int spot = (((X/TILE_SIZE) + WIDTH * (Y/TILE_SIZE)));
        
        bool foodDataCheck = false;
        int foodDataIndex = 0;

        //std::cout << spot << std::endl;
        
        //std::cout << "spot: " << X/TILE_SIZE << " " << Y/TILE_SIZE << " " << spot << std::endl;
        if(!hasFood)
        {
            for(int j = 0; j < this->_data->food.size(); j++)
            {
                //std::cout << "checking food " << std::endl;

                if(this->_data->food.at(j).CheckSpot((X/TILE_SIZE), (Y/TILE_SIZE)) == true)
                {
                    //std::cout << "found it " << std::endl;
                    foodDataCheck = true;
                    foodDataIndex = j;
                    //std::cout << foodDataCheck << std::endl;
                }
                    
            }
        }
        //std::cout << foodDataCheck << std::endl;
        
        if((this->grid[spot].type == 3) && (hasFood))
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
        else if((foodDataCheck) && (!hasFood))
        {
            //std::cout << foodDataCheck << std::endl;
            _ants.at(i)->hasFood = true;
            _ants.at(i)->antSprite.setTexture(this->_data->assets.GetTexture("ANT FOOD"));
            _ants.at(i)->pheromoneAmount = 500;
            
            if(this->_data->food.at(foodDataIndex).RemoveFood(carryCapacity) <= 0)
            {
                this->_data->food.erase(this->_data->food.begin() + foodDataIndex);
                foodDataCheck = false;
                foodDataIndex = 0;
            }
            //std::cout << "angle should reverse" << std::endl;
            angle = antReverse(angle);
            _ants.at(i)->setAngle(angle);
            _ants.at(i)->antSprite.setPosition(_ants.at(i)->pos);
            _ants.at(i)->antSprite.setRotation(_ants.at(i)->angle);
        }
        else if((this->grid[spot].type == 0) && (hasFood) && (this->grid[spot].pherHomeAmount > 0))
        {
            //temp = averageHomeAngle(ant[i]);
            pos.x = pos.x + x;
            pos.y = pos.y + y;
            _ants.at(i)->setPos(pos);
            _ants.at(i)->setAngle(angle);
            _ants.at(i)->antSprite.setPosition(_ants.at(i)->pos);
            _ants.at(i)->antSprite.setRotation(angle);
        }
        else if((this->grid[spot].type == 0) && (!hasFood) && (this->grid[spot].pherFoodAmount > 0))
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
        else if((this->grid[spot].type == 0) || ((this->grid[spot].type == 3) && (!hasFood)))
        {
            pos.x = (pos.x + x);
            pos.y = (pos.y + y);
            _ants.at(i)->setPos(pos);
            _ants.at(i)->setAngle(angle);
            _ants.at(i)->antSprite.setPosition(_ants.at(i)->pos);
            _ants.at(i)->antSprite.setRotation(_ants.at(i)->angle);
        }
        else
        {
            angle = antBounce(*_ants.at(i), (X/TILE_SIZE), (Y/TILE_SIZE));
            _ants.at(i)->setAngle(angle);
            _ants.at(i)->antSprite.setPosition(_ants.at(i)->pos);
            _ants.at(i)->antSprite.setRotation(_ants.at(i)->angle);
        }

        if((!hasFood) && (_ants.at(i)->pheromoneAmount > 0) && (this->grid[spot].pherHomeAmount < _ants.at(i)->pheromoneAmount))
        {
            _ants.at(i)->pheromoneAmount--;
            this->grid[spot].pherHome = true;
            //this->grid[X + WIDTH * Y].time = dt;//elapsed;
            this->grid[spot].toHomeAngle = antReverse(angle);
            this->grid[spot].pherHomeAmount = _ants.at(i)->pheromoneAmount;
        }
        else if((hasFood) && (_ants.at(i)->pheromoneAmount > 0) && (this->grid[spot].pherFoodAmount < _ants.at(i)->pheromoneAmount))
        {
            _ants.at(i)->pheromoneAmount--;
            this->grid[spot].pherFood = true;
            //this->grid[X + WIDTH * Y].time = dt;//elapsed;
            this->grid[spot].toFoodAngle = antReverse(angle);
            this->grid[spot].pherFoodAmount = _ants.at(i)->pheromoneAmount;
        }

        //std::cout << X << " " << Y << " " << std::endl;
    }

    //pheromoneSimulate(dt); // last thing we do is change pheromones
}

void Colony::pheromoneSimulate(float dt)
{
    //std::cout << (this->pherDisolveSpeed * dt) << std::endl;

    for(int x = 0; x < WIDTH; x++)
    {
        for(int y = 0; y < HEIGHT; y++)
        {
            int spot = (x + WIDTH * y);

            //std::cout << this->grid[spot].pherFoodAmount << " " << this->grid[spot].pherHomeAmount << std::endl;
            if((this->grid[spot].pherHome == true) && (this->grid[spot].pherFood == true))
            {
                int red = 250;
                int blue = 250;

                if(this->grid[spot].pherHomeAmount < 250)
                {
                    red = this->grid[spot].pherHomeAmount;
                    this->grid[spot].pherHomeAmount--;
                    if(this->grid[spot].pherHomeAmount <= 0)
                    {
                        this->grid[spot].pherHome = false;
                        this->grid[spot].pherHomeAmount = 0;
                    }
                }
                if(this->grid[spot].pherFoodAmount < 250)
                {
                    blue = this->grid[spot].pherFoodAmount;
                    this->grid[spot].pherFoodAmount--;
                    if(this->grid[spot].pherFoodAmount <= 0)
                    {
                        this->grid[spot].pherFood = false;
                        this->grid[spot].pherFoodAmount = 0;
                    }
                }
                if(red > blue)
                    this->grid[spot].shape.setFillColor(sf::Color(red, 0, blue,red));
                else
                    this->grid[spot].shape.setFillColor(sf::Color(red, 0, blue,blue));
            }
            else if(this->grid[spot].pherHome == true)
            {
                //std::cout << this->grid[spot].pherFoodAmount << " " << this->grid[spot].pherHomeAmount << std::endl;

                if(this->grid[spot].pherHomeAmount > 250)
                    this->grid[spot].shape.setFillColor(sf::Color(250, 0, 0, 250));
                else
                    this->grid[spot].shape.setFillColor(sf::Color(250, 0, 0,this->grid[spot].pherHomeAmount));
                
                this->grid[spot].shape.setSize(sf::Vector2f(TILE_SIZE,TILE_SIZE));
                this->grid[spot].shape.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                this->grid[spot].pherHomeAmount--;
                if(this->grid[spot].pherHomeAmount <= 0)
                {
                    this->grid[spot].pherHome = false;
                    this->grid[spot].pherHomeAmount = 0;
                }
            }
            else if(this->grid[spot].pherFood == true)
            {
                if(this->grid[spot].pherFoodAmount > 250)
                    this->grid[spot].shape.setFillColor(sf::Color(0, 0, 250, 250));
                else
                    this->grid[spot].shape.setFillColor(sf::Color(0, 0, 250,this->grid[spot].pherFoodAmount));

                //this->grid[spot].shape.setFillColor(sf::Color(0, 0, 250,this->grid[spot].pherFoodAmount));
                this->grid[spot].shape.setSize(sf::Vector2f(TILE_SIZE,TILE_SIZE));
                this->grid[spot].shape.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                this->grid[spot].pherFoodAmount--;
                
                if(this->grid[spot].pherFoodAmount <= 0)
                {
                    this->grid[spot].pherFood = false;
                    this->grid[spot].pherFoodAmount = 0;
                }
            }
        }
    }
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

    if(A.hasFood)
    {
        for(int x = start_X - r; x < start_X + r; x++)
        {
            for(int y = start_Y - r; y < start_Y + r; y++)
            {
                int spot = ((x/TILE_SIZE) + WIDTH * (y/TILE_SIZE));

                float deltaX = x - start_X;
                float deltaY = y - start_Y;
                float num = atan2(deltaY,deltaX) * 180 / 3.14;
                if((num < 0) || ((num < sAngle) && (num < eAngle)))
                    num +=360;

                if(((x-start_X)*(x-start_X) + (y-start_Y)*(y-start_Y) <= r*r) && 
                (num > sAngle) && (num < eAngle) && 
                (x > 0) && ((x/TILE_SIZE) < WIDTH) && (y > 0) && ((y/TILE_SIZE) < HEIGHT))
                {
                    //if(this->grid[spot].type == 0)
                    //{
                        this->grid[spot].vision = true;
                    //}

                    if(this->grid[spot].type == 3)
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
                    if((this->grid[spot].pherHome == true) && (this->grid[spot].pherHomeAmount > highAmount))
                    {
                        highX = x;
                        highY = y;
                        highAmount = this->grid[spot].pherHomeAmount;
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
                int spot = ((x/TILE_SIZE) + WIDTH * (y/TILE_SIZE));
                bool foodDataCheck = false;
                //std::cout << x << " " << y << std::endl;

                for(int j = 0; j < this->_data->food.size(); j++)
                {
                    if(this->_data->food.at(j).CheckSpot(x/TILE_SIZE,y/TILE_SIZE))
                    {
                        foodDataCheck = true;
                        //std::cout << foodDataCheck << std::endl;
                    }
                        
                }

                float deltaX = x - start_X;
                float deltaY = y - start_Y;
                float num = atan2(deltaY,deltaX) * 180 / 3.14;
                if((num < 0) || ((num < sAngle) && (num < eAngle)))
                    num +=360;

                if(((x-start_X)*(x-start_X) + (y-start_Y)*(y-start_Y) <= r*r) && 
                (num > sAngle) && (num < eAngle) && 
                (x > 0) && ((x/TILE_SIZE) < WIDTH) && (y > 0) && ((y/TILE_SIZE) < HEIGHT))
                {
                    //if(this->grid[spot].type == 0)
                    //{
                        this->grid[spot].vision = true;
                    //}


                    if(foodDataCheck)
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
                    else if((this->grid[spot].hasFood == false) && (this->grid[spot].pherFoodAmount > highAmount))
                    {
                        highX = x;
                        highY = y;
                        highAmount = this->grid[spot].pherFoodAmount;
                        check = true;
                        //calculate angle
                    } 
                }

                foodDataCheck = false;  
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
    int startX = A.pos.x/TILE_SIZE;
    int startY = A.pos.y/TILE_SIZE;

    //std::cout << startX << " " << startY  << " " << X << " " <<  Y << std::endl;

    if((angle >= 0) && (angle < 90))
    {
        if((this->grid[(startX + WIDTH * Y)].type != 1) && (this->grid[(X + WIDTH * startY)].type == 1))
            angle = rand() % 90 + 90;
        else if((this->grid[(startX + WIDTH * Y)].type == 1) && (this->grid[(X + WIDTH * startY)].type != 1))
            angle = rand() % 90 + 270;
        else
            angle = antReverse(angle);
    }
    else if((angle >= 90) && (angle < 180))
    {
        if((this->grid[(startX + WIDTH * Y)].type != 1) && (this->grid[(X + WIDTH * startY)].type == 1))
            angle = rand() % 90 + 1;
        else if((this->grid[(startX + WIDTH * Y)].type == 1) && (this->grid[(X + WIDTH * startY)].type != 1))
            angle = rand() % 90 + 180;
        else
            angle = antReverse(angle);
    }
    else if((angle >= 180) && (angle < 270))
    {
        if((this->grid[(startX + WIDTH * Y)].type != 1) && (this->grid[(X + WIDTH * startY)].type == 1))
            angle = rand() % 90 + 270;
        else if((this->grid[(startX + WIDTH * Y)].type == 1) && (this->grid[(X + WIDTH * startY)].type != 1))
            angle = rand() % 90 + 90;
        else
            angle = antReverse(angle);
    }
    else if((angle >= 270) && (angle <= 360))
    {
        if((this->grid[(startX + WIDTH * Y)].type != 1) && (this->grid[(X + WIDTH * startY)].type == 1))
            angle = rand() % 90 + 180;
        else if((this->grid[(startX + WIDTH * Y)].type == 1) && (this->grid[(X + WIDTH * startY)].type != 1))
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