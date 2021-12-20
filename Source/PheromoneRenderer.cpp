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


void PheromoneRenderer::update(std::vector<Tile *> c, int id)
{
    for(int i = 0; i < c.size(); i++)
    {
        sf::Vertex* quad = &p_r_vertices[c[i]->arrayPos * 4];
        int red, green = 0, blue, alpha;

        if(c[i]->pherFoodAmount[id][0] > c[i]->pherHomeAmount[id][0])
            alpha = c[i]->pherFoodAmount[id][0];
        else if(c[i]->pherFoodAmount[id][0] < c[i]->pherHomeAmount[id][0])
            alpha = c[i]->pherHomeAmount[id][0];
        else
            alpha = 0;
        
        if(alpha > 255)
            alpha = 255;



        if(c[i]->pherFoodAmount[id][0] > 255)
            blue = 255;
        else
            blue = c[i]->pherFoodAmount[id][0];

        if(c[i]->pherHomeAmount[id][0] > 255)
            red = 255;
        else
            red = c[i]->pherHomeAmount[id][0];

/*         if(c[i]->vision == true)
        {
            red = 255;
            green = 255;
            blue = 0;
            alpha = 255;
            //c[i]->vision = false;
        } */
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