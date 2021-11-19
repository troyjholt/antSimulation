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
    int x = 50;
    int y = 50;
    range = 10;
    rangeWidth = 60;
    colPos.x = x;
    colPos.y = y;
    grid[x][y].type = 4;

    nest.setRadius(7.f);
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
                this->grid[x][y].shape.setOutlineColor(sf::Color(0, 0, 0));
                this->grid[x][y].shape.setOutlineThickness(0);
                this->grid[x][y].shape.setSize(sf::Vector2f(tileSize,tileSize));
                this->grid[x][y].shape.setPosition(x * tileSize, y * tileSize);
                window.draw(this->grid[x][y].shape);
            }
            else if(this->grid[x][y].type == 2)
            {
                this->grid[x][y].shape.setFillColor(sf::Color(0, 255, 0));
                this->grid[x][y].shape.setOutlineColor(sf::Color(0, 0, 0, 50));
                this->grid[x][y].shape.setOutlineThickness(-1);
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
                this->grid[x][y].shape.setOutlineColor(sf::Color(0, 0, 0, 50));
                this->grid[x][y].shape.setOutlineThickness(-1);
                this->grid[x][y].shape.setSize(sf::Vector2f(tileSize,tileSize));
                this->grid[x][y].shape.setPosition(x * tileSize, y * tileSize);
                window.draw(this->grid[x][y].shape);
            }
            else if(this->grid[x][y].pherHome == true)
            {
                this->grid[x][y].shape.setFillColor(sf::Color(255, 0, 0,this->grid[x][y].pherHomeAmount));
                this->grid[x][y].shape.setOutlineColor(sf::Color(0, 0, 0, 50));
                this->grid[x][y].shape.setOutlineThickness(-1);
                this->grid[x][y].shape.setSize(sf::Vector2f(tileSize,tileSize));
                this->grid[x][y].shape.setPosition(x * tileSize, y * tileSize);
                window.draw(this->grid[x][y].shape);
            }
            else if(this->grid[x][y].pherFood == true)
            {
                this->grid[x][y].shape.setFillColor(sf::Color(0, 0, 255,this->grid[x][y].pherFoodAmount));
                this->grid[x][y].shape.setOutlineColor(sf::Color(0, 0, 0, 50));
                this->grid[x][y].shape.setOutlineThickness(-1);
                this->grid[x][y].shape.setSize(sf::Vector2f(tileSize,tileSize));
                this->grid[x][y].shape.setPosition(x * tileSize, y * tileSize);
                window.draw(this->grid[x][y].shape);
            }
            else if(this->grid[x][y].vision == true)
            {
                this->grid[x][y].shape.setFillColor(sf::Color::Yellow);
                this->grid[x][y].shape.setSize(sf::Vector2f(tileSize,tileSize));
                this->grid[x][y].shape.setPosition(x * tileSize, y * tileSize);
                window.draw(this->grid[x][y].shape);
                this->grid[x][y].vision = false;
            }
        }
    }

    for(int i = 0; i < antSize; i++)
    {
        this->ant[i].antSprite.setPosition(this->ant[i].pos.x * tileSize, this->ant[i].pos.y * tileSize);
        this->ant[i].antSprite.setRotation(this->ant[i].angle);
        if(sightD)
        {
            //std::cout << sightD << std::endl;
            showVision(this->ant[i]);
        }
            
        window.draw(this->ant[i].antSprite);
    }

    window.draw(this->nest);
};

void World::showVision(Ant A)
{

    int start_X = A.pos.x;//colPos.x; // center point
    int start_Y = A.pos.y;//colPos.y;

    int r = range;

    float angle = A.angle;
    float sAngle = A.angle - rangeWidth;
    float eAngle = A.angle + rangeWidth;
    
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
                    this->grid[x][y].vision = true;
            }
        }
    }
}

void World::simulate(sf::Time elapsed)
{
    antSimulate(elapsed);
    pherSimulate(elapsed);
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

/*     int start_X = colPos.x; // center point
    int start_Y = colPos.y;

    int r = range;

    // current point
    int x; 
    int y;

    for(int i = start_X - r; i < start_X + r; i++)
    {
        for(int j = start_Y - r; j < start_Y + r; j++)
        {
            if((i-start_X)*(i-start_X) + (j-start_Y)*(j-start_Y) <= r*r)
            {
                this->grid[i][j].pherHomeAmount = 500;
                this->grid[i][j].pherHome = true;
            }
        }
    } */


/*     for(int x = range * -1; x < range; x++)
        for(int y = range * -1; y < range; y++)
        {
            if(((colPos.x + x) < (width * tileSize)) && 
              ((colPos.y + y) < (height * tileSize)) &&
              ((colPos.x + x) > 0) && ((colPos.y + y) > 0))
            {
                int row = colPos.x + x;
                int col = colPos.y + y;
                this->grid[row][col].pherHomeAmount = 500;
                this->grid[row][col].pherHome = true;
                int y2 = colPos.y + y;
                int y1 = colPos.y;
                int x2 = colPos.x + x;
                int x1 = colPos.x;
                float newAngle = atan2((y2 - y1), (x2 - x1)) * (180/3.14);
                newAngle -= 180;
                if(newAngle < 0)
                    newAngle += 360;
                else if(newAngle > 360)
                    newAngle -= 360;
                //std::cout << "here is atan2 " <<  newAngle << std::endl;
                //if(((y2 - y1) != 0) && ((x2 - x1) != 0))
                //{
                    //float angle = (((y2 - y1)/(x2-x1)) * 180 / 3.14);
                    this->grid[row][col].toHomeAngle = newAngle;//(((y2 - y1)/(x2-x1)) * 180 / 3.14);
                    //std::cout << angle << std::endl;
                //}
            }
        } */
}

void World::antSimulate(sf::Time elapsed)
{
    for(int i = 0; i < antSize; i++)
    {
        // decide where to move
        // does ant have food
            // is there home pheromones in area
            // calculate for pheromones.
        // is there food pheromones in area
        // use angle determine next spot.
            // is spot open
                // go there
            // is spot a wall
                // reverse
            // is spot food.
                // grab food.
                // reverse.
        // move.


        sf::Vector2f pos = this->ant[i].getPos();
        float angle = this->ant[i].getAngle();
        bool hasFood = this->ant[i].hasFood;
        float temp = rand() % 11 - 5;
        //float tempAngle;
        if(pherCheck(ant[i]) == true)
        {
            if(hasFood)
            {
                angle = averageHomeAngle(ant[i]);
            }
            else
            {
                angle = averageFoodAngle(ant[i]);
            }
        }
        
        angle = angle + temp;


        //angle = ((angle + tempAngle)/2) + temp;

        
        //angle = angle + temp; 
        
        if(angle > 360)
            angle -= 360;
        
        if(angle < 0)
            angle += 360;

        //angle = 360;

        float rad = angle / 57.2958;
        float x = 1.0f * cos(rad);
        float y = 1.0f * sin(rad);
        int X = pos.x + x;
        int Y = pos.y + y;
        
        
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
            temp = averageHomeAngle(ant[i]);
            pos.x = pos.x + x;
            pos.y = pos.y + y;
            this->ant[i].setPos(pos);
            this->ant[i].setAngle(temp);
            this->ant[i].antSprite.setPosition(this->ant[i].pos);
            this->ant[i].antSprite.setRotation(temp);
        }
        else if((this->grid[X][Y].type == 0) && (this->ant[i].hasFood == false) && (this->grid[X][Y].pherFoodAmount > 0))
        {
            temp = averageFoodAngle(ant[i]);
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
            //angle = antBounce(angle);
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

        //std::cout << X << ' ' << Y << ' ' << ant[i].angle << std::endl;
    }
}

bool World::pherCheck(Ant A)
{

    int start_X = A.pos.x;//colPos.x; // center point
    int start_Y = A.pos.y;//colPos.y;

    int r = range;

    float angle = A.angle;
    float sAngle = A.angle - rangeWidth;
    float eAngle = A.angle + rangeWidth;
    
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
                        if((this->grid[x][y].pherHome == true) || (this->grid[x][y].type == 4))
                            return true;
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
                        if(this->grid[x][y].pherFood == true)
                            return true;
                }
            }
        }
    }

    return false;

/*     int x = A.pos.x;
    int y = A.pos.y;

    if(A.hasFood)
    {
        for(int row = -1; row <= 1; row++)
            for(int col = -1; col <=1; col++)
            {
                if(this->grid[x + row][y + col].pherHome == true)
                {
                    return true;
                }
            }
    }
    else
    {
        for(int row = -1; row <= 1; row++)
            for(int col = -1; col <=1; col++)
            {
                if(this->grid[x + row][y + col].pherFood == true)
                {
                    return true;
                }
            }
    }

    return false; */
}

float World::averageFoodAngle(Ant A)
{
    int start_X = A.pos.x;//colPos.x; // center point
    int start_Y = A.pos.y;//colPos.y;

    int r = range;

    float angle = A.angle;
    float sAngle = A.angle - rangeWidth;
    float eAngle = A.angle + rangeWidth;
    
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
                if((this->grid[x][y].hasFood == false) && (this->grid[x][y].pherFoodAmount > highAmount))
                {
                    highX = x;
                    highY = y;
                    highAmount = this->grid[x][y].pherFoodAmount;
                }
            }
        }
    }

    if(highAmount > 0)
    {
        int newY = highY - start_Y;
        int newX = highX - start_X;
        int newAngle = atan2(newY, newX) * 180 / 3.14;
        if(newAngle < 0)
            newAngle += 360;
        return newAngle;
    }

    return angle;


    //----------------------------------------------------------------//
    /*     int sumOfWeight = 1;
        int weightAngle = 1;
        float ret = 0.0;

        for(int row = -2; row <= 2; row++)
            for(int col = -2; col <=2; col++)
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

        return ret; */
}

float World::averageHomeAngle(Ant A)
{
    int start_X = A.pos.x;//colPos.x; // center point
    int start_Y = A.pos.y;//colPos.y;

    int r = range;

    float angle = A.angle;
    float sAngle = A.angle - rangeWidth;
    float eAngle = A.angle + rangeWidth;
    
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
                if(this->grid[x][y].type == 4)
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
                if((this->grid[x][y].pherHome == true) && (this->grid[x][y].pherHomeAmount > highAmount))
                {
                    highX = x;
                    highY = y;
                    highAmount = this->grid[x][y].pherHomeAmount;
                }
            }
        }
    }

    if(highAmount > 0)
    {
        int newY = highY - start_Y;
        int newX = highX - start_X;
        int newAngle = atan2(newY, newX) * 180 / 3.14;
        if(newAngle < 0)
            newAngle += 360;
        return newAngle;
    }

    return angle;









    /*     int sumOfWeight = 0;
        int weightAngle = 0;
        float ret = 0.0;

        for(int row = -2; row <= 2; row++)
            for(int col = -2; col <=2; col++)
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

        return ret; */
}

// does not work yet.
float World::antBounce(float angle)
{
    //float angle = A.getAngle();

    if((angle < 361) && (angle > 270))
    {
        angle = angle - 90;
        if(angle < 0)
            angle +=360;
    }
    else if((angle < 271) && (angle > 180))
    {
        angle = angle + 90;
        if(angle > 360)
            angle -= 360;
    }
    else if((angle < 181) && (angle > 90))
    {
        angle = angle - 90;
        if(angle < 0)
            angle +=360;
    }
    else if((angle < 91) && (angle > 0))
    {
        angle = angle + 90;
        if(angle > 360)
            angle -= 360;
    }
    return angle;
/*     angle = angle + 90;
    if(angle > 360)
        angle -= 360;
    return angle; */
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

        for(x; x < brushSize; x++)
        {
            y = brushSize * -1;
            //std::cout << pos.x << ' ' << pos.y << std::endl;
            for(y; y < brushSize; y++)
            {
                if(((pos.x + x) < (width * tileSize)) && 
                  ((pos.y + y) < (height * tileSize)) &&
                  ((pos.x + x) > 0) && ((pos.y + y) > 0))
                {
                    this->grid[(pos.x + x) / tileSize][(pos.y + y)/ tileSize].type = 1; 
                }
                          
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
        

        //std::cout << x << ' ' << y << std::endl;
        for(x; x < brushSize; x++)
        {
            y = brushSize * -1;
            for(y; y < brushSize; y++)
            {
                if(((pos.x + x) < (width * tileSize)) && 
                  ((pos.y + y) < (height * tileSize)) &&
                  ((pos.x + x) > 0) && ((pos.y + y) > 0))
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

void World::buildErase(sf::Vector2i pos, int brushSize)
{
    int x;
    int y;
    if(brushSize > 1)
    {
        x = brushSize * -1;

        //std::cout << x << ' ' << y << std::endl;
        for(x; x < brushSize; x++)
        {
            y = brushSize * -1;
            for(y; y < brushSize; y++)
            {
                if(((pos.x + x) < (width * tileSize)) && 
                  ((pos.y + y) < (height * tileSize)) &&
                  ((pos.x + x) > 0) && ((pos.y + y) > 0))
                {
                    this->grid[(pos.x + x) / tileSize][(pos.y + y)/ tileSize].type = 0; 
                }
            }
        }
    }
    else
    {
        this->grid[pos.x / tileSize][pos.y / tileSize].type = 0;
    }
    //this->grid[pos.x / tileSize][pos.y / tileSize].type = 2;
}

void World::sightDraw()
{
    if(sightD == false)
        sightD = true;
    else
        sightD = false;
}