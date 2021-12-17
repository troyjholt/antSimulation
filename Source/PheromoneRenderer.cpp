#include "PheromoneRenderer.hpp"

bool PheromoneRenderer::load()
{
    p_r_vertices.setPrimitiveType(sf::Quads);
    p_r_vertices.resize(HEIGHT * WIDTH * 4);

    for(int x = 0; x < WIDTH; x++)
    {
        for(int y = 0; y < HEIGHT; y++)
        {
            // pointer to current ants vertices in vertex array.
            sf::Vertex* quad = &p_r_vertices[(x + y * WIDTH) * 4];

            int spot = (x + y * WIDTH);
/* 
            int alpha;
            int red, green, blue;

            if(c.grid[spot]->pherFoodAmount > c.grid[spot]->pherHomeAmount)
                alpha = c.grid[spot]->pherFoodAmount;
            else if(c.grid[spot]->pherFoodAmount < c.grid[spot]->pherHomeAmount)
                alpha = c.grid[spot]->pherHomeAmount;
            else
                alpha = 0;
            
            if(alpha > 255)
                alpha = 255;

            if(c.grid[spot]->pherFoodAmount > 255)
                blue = 255;
            else
                blue = c.grid[spot]->pherFoodAmount;

            if(c.grid[spot]->pherHomeAmount > 255)
                red = 255;
            else
                red = c.grid[spot]->pherHomeAmount;

            green = 0;
 */
            int red = 0, green = 0, blue = 0, alpha = 0;
            
            sf::Color color(red,green,blue,alpha);

            // defining the 4 corners of the "Sprite"
            quad[0].position = sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE);
            quad[1].position = sf::Vector2f((x + 1) * TILE_SIZE, y * TILE_SIZE);
            quad[2].position = sf::Vector2f((x + 1) * TILE_SIZE, (y + 1) * TILE_SIZE);
            quad[3].position = sf::Vector2f(x * TILE_SIZE, (y + 1) * TILE_SIZE);

            // defining its 4 texture coordinates
            quad[0].color = color;
            quad[1].color = color;
            quad[2].color = color;
            quad[3].color = color;
            
        }
    }

    return true;
}

void PheromoneRenderer::update(std::vector<Tile *> c)
{
    for(int i = 0; i < c.size(); i++)
    {
        sf::Vertex* quad = &p_r_vertices[c.at(i)->arrayPos * 4];
        int red, green = 0, blue, alpha;

        if(c.at(i)->pherFoodAmount > c.at(i)->pherHomeAmount)
            alpha = c.at(i)->pherFoodAmount;
        else if(c.at(i)->pherFoodAmount < c.at(i)->pherHomeAmount)
            alpha = c.at(i)->pherHomeAmount;
        else
            alpha = 0;
        
        if(alpha > 255)
            alpha = 255;

        if(c.at(i)->pherFoodAmount > 255)
            blue = 255;
        else
            blue = c.at(i)->pherFoodAmount;

        if(c.at(i)->pherHomeAmount > 255)
            red = 255;
        else
            red = c.at(i)->pherHomeAmount;

        sf::Color color(red,green,blue,alpha);
        
        // defining its 4 texture coordinates
        quad[0].color = color;
        quad[1].color = color;
        quad[2].color = color;
        quad[3].color = color;
    }
/*     for(int x = 0; x < WIDTH; x++)
    {
        for(int y = 0; y < HEIGHT; y++)
        {
            // pointer to current ants vertices in vertex array.
            sf::Vertex* quad = &p_r_vertices[(x + y * WIDTH) * 4];

            int spot = (x + y * WIDTH);

            int alpha;
            int red, green, blue;

            if(c.grid[spot]->pherFoodAmount > c.grid[spot]->pherHomeAmount)
                alpha = c.grid[spot]->pherFoodAmount;
            else if(c.grid[spot]->pherFoodAmount < c.grid[spot]->pherHomeAmount)
                alpha = c.grid[spot]->pherHomeAmount;
            else
                alpha = 0;
            
            if(alpha > 255)
                alpha = 255;

            if(c.grid[spot]->pherFoodAmount > 255)
                blue = 255;
            else
                blue = c.grid[spot]->pherFoodAmount;

            if(c.grid[spot]->pherHomeAmount > 255)
                red = 255;
            else
                red = c.grid[spot]->pherHomeAmount;

            green = 0;

            sf::Color color(red,green,blue,alpha);

            // defining the 4 corners of the "Sprite"
            quad[0].position = sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE);
            quad[1].position = sf::Vector2f((x + 1) * TILE_SIZE, y * TILE_SIZE);
            quad[2].position = sf::Vector2f((x + 1) * TILE_SIZE, (y + 1) * TILE_SIZE);
            quad[3].position = sf::Vector2f(x * TILE_SIZE, (y + 1) * TILE_SIZE);

            // defining its 4 texture coordinates
            quad[0].color = color;
            quad[1].color = color;
            quad[2].color = color;
            quad[3].color = color;
            
        }
    } */
}

void PheromoneRenderer::removePheromone(int pos)
{
    int red = 0, green = 0, blue = 0, alpha = 0;
    
    sf::Color color(red,green,blue,alpha);
    sf::Vertex* quad = &p_r_vertices[pos * 4];

    quad[0].color = color;
    quad[1].color = color;
    quad[2].color = color;
    quad[3].color = color;
}