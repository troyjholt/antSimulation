//#include "world.hpp"

World::World(int numColonies, int level[], bool randStart)
{
    colonies = new Colony [numColonies];
    numCol = numColonies;


    for(int i = 0; i < numColonies; i++)
    {
        colonies[i].antTexture.loadFromFile("Assets/Graphics/ant.png");
        colonies[i].antFoodTexture.loadFromFile("Assets/Graphics/antFood.png");
        colonies[i].id = i;
        for(int x = 0; x < (height * width); x++)
        {
            colonies[i].grid[x].type = level[x];
        }
        
        if(randStart)
        {
            colonies[i].colPos.x = (rand() % width);
            colonies[i].colPos.y = (rand() % height);
            int x = colonies[i].colPos.x;
            int y = colonies[i].colPos.y;
            colonies[i].grid[x + width * y].type = 4;
            level[x + width * y] = 4;
            std::cout <<  colonies[i].colPos.x << " " << colonies[i].colPos.y << " " << (x + width * y) << std::endl;
        }
        else
        {
            // Assign to a spot with type 4.
        }
        for(int x = 0; x < maxAntSize; x++)
        {
            colonies[i].ant[x].setPos(colonies[i].colPos);
            colonies[i].ant[x].antSprite.setTexture(colonies[i].antTexture);
        }
    }
};

void World::updateLevel(int level[height * width])
{
    for(int i = 0; i < numCol; i++)
    {
        for(int x = 0; x < (height * width); x++)
        {
            colonies[i].grid[x].type = level[x];
        }
    }
}

void World::print()
{
    for(int i = 0; i < numCol; i++)
    {
        for(int x = 0; x < (height * width); x++)
        {
            std::cout << colonies[i].grid[x].type << " ";
            if(x == width)
                std::cout << std::endl;
        }
    }
}

void World::draw(sf::RenderWindow &window, sf::Clock &clock)
{
    for(int i = 0; i < numCol; i++)
    {
        for(int k = 0; k < colonies[i].colSize; k++)
        {
            Ant A = colonies[i].ant[k];

            A.antSprite.setPosition(A.pos.x * tileSize, A.pos.y * tileSize);
            A.antSprite.setRotation(A.angle);
            if(sightD)
            {
                //std::cout << sightD << std::endl;
                showVision(A);
            }
            //if(A.hasFood == true)
            //{
                //A.antSprite.setTexture(A.antFoodTexture);
                //A.antSprite.setOrigin(50.f, 50.f);
                //A.antSprite.setScale(0.2,0.2);
                //A.antSprite.setRotation(A.angle);
            //}
            //else
           //{
                //A.antSprite.setTexture(A.antTexture);
                //A.antSprite.setOrigin(50.f, 50.f);
                //A.antSprite.setScale(0.2,0.2);
                //A.antSprite.setRotation(A.angle);
            //}
            window.draw(A.antSprite);
        }
    }
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
                    //this->grid[x][y].vision = true;
            }
        }
    }
}

void World::simulate(sf::Time elapsed)
{
    for(int i = 0; i < numCol; i++)
    {
        colonies[i].antSimulate(elapsed);
        colonies[i].pherSimulate(elapsed);
    }
    //future objects simulate()
}

void World::sightDraw()
{
    if(sightD == false)
        sightD = true;
    else
        sightD = false;
}

void World::pherDraw()
{
    if(showPher == false)
        showPher = true;
    else
        showPher = false;
}