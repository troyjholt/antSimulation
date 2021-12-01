#include "Colony.hpp"

void Colony::antSimulate(sf::Time elapsed)
{
    for(int i = 0; i < colSize; i++)
    {
        sf::Vector2f pos = this->ant[i].getPos();
        float angle = findAngle(this->ant[i]);
        //std::cout << "Angle = " << angle << std::endl;

        bool hasFood = this->ant[i].hasFood;
        float temp = rand() % 11 - 5;

        float rad = angle / 57.2958;
        float x = 1.0f * cos(rad);
        float y = 1.0f * sin(rad);
        int X = pos.x + x;
        int Y = pos.y + y;

        if((this->grid[X + width * Y].type == 4) && (this->ant[i].hasFood == true))
        {
            //std::cout << "we made it" << std::endl;
            pos.x = pos.x + x;
            pos.y = pos.y + y;
            this->ant[i].setPos(pos);
            this->ant[i].hasFood = false;
            this->ant[i].amount = 500;
            angle = antReverse(angle);
            this->ant[i].antSprite.setTexture(antTexture);
            this->ant[i].setAngle(angle);
            this->ant[i].antSprite.setPosition(this->ant[i].pos);
            this->ant[i].antSprite.setRotation(this->ant[i].angle);

            foodReturned = foodReturned + this->ant[i].carryCapacity;
            //std::cout << "Amount of food in storage: " << foodReturned << std::endl;
            if(foodReturned >= 5)
            {
                foodReturned = 0;
                colSize+=1;
                //std::cout << "New ant created. # of ants is now: " << antSize << std::endl;
            }
        }
        else if((this->grid[X + width * Y].type == 0) && (this->ant[i].hasFood == true) && (this->grid[X + width * Y].pherHomeAmount > 0))
        {
            //temp = averageHomeAngle(ant[i]);
            pos.x = pos.x + x;
            pos.y = pos.y + y;
            this->ant[i].setPos(pos);
            this->ant[i].setAngle(angle);
            this->ant[i].antSprite.setPosition(this->ant[i].pos);
            this->ant[i].antSprite.setRotation(angle);
        }
        else if((this->grid[X + width * Y].type == 0) && (this->ant[i].hasFood == false) && (this->grid[X + width * Y].pherFoodAmount > 0))
        {
            //temp = averageFoodAngle(ant[i]);
            //std::cout << temp << ' ' <<  this->grid[X][Y].toFoodAngle << std::endl; 
            pos.x = pos.x + x;
            pos.y = pos.y + y;
            this->ant[i].setPos(pos);
            this->ant[i].setAngle(angle);
            this->ant[i].antSprite.setPosition(this->ant[i].pos);
            this->ant[i].antSprite.setRotation(angle);
        }
        else if((this->grid[X + width * Y].type == 0) || ((this->grid[X + width * Y].type == 4) && (this->ant[i].hasFood == false)))
        {
            pos.x = pos.x + x;
            pos.y = pos.y + y;
            this->ant[i].setPos(pos);
            this->ant[i].setAngle(angle);
            this->ant[i].antSprite.setPosition(this->ant[i].pos);
            this->ant[i].antSprite.setRotation(this->ant[i].angle);
        }
        else if((this->grid[X + width * Y].type == 2) && (this->ant[i].hasFood == false))
        {
            this->ant[i].hasFood = true;
            this->ant[i].antSprite.setTexture(antFoodTexture);
            this->ant[i].amount = 500;
            this->grid[X + width * Y].foodAmount = this->grid[X + width * Y].foodAmount - this->ant[i].carryCapacity;

            if(this->grid[X + width * Y].foodAmount <= 0)
            {
                this->grid[X + width * Y].foodAmount = 0;
                this->grid[X + width * Y].type = 0;
                //map.load("Assets/Graphics/tileMap.png", sf::Vector2u(tileSize, tileSize), level, width, height);
                //rebuild
            }
            angle = antReverse(angle);
            this->ant[i].setAngle(angle);
            this->ant[i].antSprite.setPosition(this->ant[i].pos);
            this->ant[i].antSprite.setRotation(this->ant[i].angle);
        }
        else
        {
            angle = antBounce(ant[i], X, Y);
            this->ant[i].setAngle(angle);
            this->ant[i].antSprite.setPosition(this->ant[i].pos);
            this->ant[i].antSprite.setRotation(this->ant[i].angle);
        }

        if((this->ant[i].hasFood == false) && (this->ant[i].amount > 0) && (this->grid[X + width * Y].pherHomeAmount < this->ant[i].amount))
        {
            this->ant[i].amount--;
            this->grid[X + width * Y].pherHome = true;
            this->grid[X + width * Y].time = elapsed;
            this->grid[X + width * Y].toHomeAngle = antReverse(angle);
            this->grid[X + width * Y].pherHomeAmount = this->ant[i].amount;
        }
        else if((this->ant[i].hasFood == true) && (this->ant[i].amount > 0) && (this->grid[X + width * Y].pherFoodAmount < this->ant[i].amount))
        {
            this->ant[i].amount--;
            this->grid[X + width * Y].pherFood = true;
            this->grid[X + width * Y].time = elapsed;
            this->grid[X + width * Y].toFoodAngle = antReverse(angle);
            this->grid[X + width * Y].pherFoodAmount = this->ant[i].amount;
        }
    }
}

float Colony::findAngle(Ant A)
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
                (x > 0) && (x < width) && (y > 0) && (y < height))
                {
                    if(this->grid[x + width * y].type == 4)
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
                    if((this->grid[x + width * y].pherHome == true) && (this->grid[x + width * y].pherHomeAmount > highAmount))
                    {
                        highX = x;
                        highY = y;
                        highAmount = this->grid[x + width * y].pherHomeAmount;
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
                (x > 0) && (x < width) && (y > 0) && (y < height))
                {
                    if(this->grid[x + width * y].type == 2)
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
                    else if((this->grid[x + width * y].hasFood == false) && (this->grid[x + width * y].pherFoodAmount > highAmount))
                    {
                        highX = x;
                        highY = y;
                        highAmount = this->grid[x + width * y].pherFoodAmount;
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

void Colony::pherSimulate(sf::Time elapsed)
{

}

float Colony::antBounce(Ant A, int X, int Y)
{

    float angle = A.getAngle();
    int startX = A.pos.x;
    int startY = A.pos.y;

    //std::cout << "flip" << std::endl;
    if((angle >= 0) && (angle < 90) && (this->grid[startX + width * Y].type != 1))
    {
        angle = angle + 110;
    }
    else if((angle >= 0) && (angle < 90) && (this->grid[X + width * startY].type != 1))
    {
        angle = angle - 110;
    }
    else if((angle >= 90) && (angle < 180) && (this->grid[startX + width * Y].type != 1))
    {
        angle = angle - 110;
    }
    else if((angle >= 90) && (angle < 180) && (this->grid[X + width * startY].type != 1))
    {
        angle = angle + 110;
    }
    else if((angle >= 180) && (angle < 270) && (this->grid[startX + width * Y].type != 1))
    {
        angle = angle + 110;
    }
    else if((angle >= 180) && (angle < 270) && (this->grid[X + width * startY].type != 1))
    {
        angle = angle - 110;
    }
    else if((angle >= 270) && (angle <= 360) && (this->grid[startX + width * Y].type != 1))
    {
        angle = angle - 110;
    }
    else if((angle >= 270) && (angle <= 360) && (this->grid[X + width * startY].type != 1))
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