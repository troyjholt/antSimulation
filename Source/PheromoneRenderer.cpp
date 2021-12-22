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


void PheromoneRenderer::update(std::vector<int> c, int id, GameDataRef data)
{
    int size = c.size();
    for(int i = 0; i < size; i++)
    {
        sf::Vertex* quad = &p_r_vertices[c[i] * 4];
        int red, green = 0, blue, alpha;

        //std::cout << data->grid[c[i]]->pherFoodAmount[id][0] << " " << data->grid[c[i]]->pherHomeAmount[id][0] << std::endl;
        if(data->grid[c[i]]->pherFoodAmount[id][0] > data->grid[c[i]]->pherHomeAmount[id][0])
            alpha = data->grid[c[i]]->pherFoodAmount[id][0];
        else if(data->grid[c[i]]->pherFoodAmount[id][0] < data->grid[c[i]]->pherHomeAmount[id][0])
            alpha = data->grid[c[i]]->pherHomeAmount[id][0];
        else
            alpha = 0;
        
        if(alpha > 255)
            alpha = 255;



        if(data->grid[c[i]]->pherFoodAmount[id][0] > 255)
            blue = 255;
        else if(data->grid[c[i]]->pherFoodAmount[id][0] < 0)
            blue = 0;
        else
            blue = data->grid[c[i]]->pherFoodAmount[id][0];

        if(data->grid[c[i]]->pherHomeAmount[id][0] > 255)
            red = 255;
        else if(data->grid[c[i]]->pherHomeAmount[id][0] < 0)
            red = 0;
        else
            red = data->grid[c[i]]->pherHomeAmount[id][0];


/*         if(data->grid[c[i]]->vision == true)
        {
            red = 255;
            green = 255;
            blue = 0;
            alpha = 255;
            data->grid[c[i]]->vision = false;
        } */

        sf::Color color(red,green,blue,alpha);
        
        // defining its 4 texture coordinates
        quad[0].color = color;
        quad[1].color = color;
        quad[2].color = color;
        quad[3].color = color;
    }
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

void PheromoneRenderer::vision(std::vector<int> c)
{
    //std::cout << c << std::endl;
    int red = 255, green = 255, blue = 0, alpha = 255;
    
    sf::Color color(red,green,blue,alpha);
    int size = c.size();

    for(int i = 0; i < size; i++)
    {
        //std::cout << c[i] << std::endl;
        sf::Vertex* quad = &p_r_vertices[c[i] * 4];

        quad[0].color = color;
        quad[1].color = color;
        quad[2].color = color;
        quad[3].color = color;
    }
}

void PheromoneRenderer::removeVision(int pos)
{
    int red = 0, green = 0, blue = 0, alpha = 0;
    
    sf::Color color(red,green,blue,alpha);
    sf::Vertex* quad = &p_r_vertices[pos * 4];

    quad[0].color = color;
    quad[1].color = color;
    quad[2].color = color;
    quad[3].color = color;
}