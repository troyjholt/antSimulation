#include "FoodRenderer.hpp"

bool FoodRenderer::load(GameDataRef data)
{
    f_r_vertices.setPrimitiveType(sf::Quads);
    f_r_vertices.resize(MAX_FOOD_SIZE * 4);

    for(int j = 0; j < data->food.size(); j++)
    {   
        // pointer to current ants vertices in vertex array.
        sf::Vertex* quad = &f_r_vertices[j * 4];
        //quad->color = sf::Color::Red;

        sf::Vector2f pos = data->food.at(j).pos;
        
        // defining the 4 corners of the "Sprite"
        quad[0].position = sf::Vector2f((pos.x * TILE_SIZE - 2) , (pos.y * TILE_SIZE - 2));
        quad[1].position = sf::Vector2f((pos.x * TILE_SIZE + 2) , (pos.y * TILE_SIZE - 2));
        quad[2].position = sf::Vector2f((pos.x * TILE_SIZE + 2) , (pos.y * TILE_SIZE + 2));
        quad[3].position = sf::Vector2f((pos.x * TILE_SIZE - 2) , (pos.y * TILE_SIZE + 2));

        // defining its 4 texture coordinates
        quad[0].texCoords = sf::Vector2f(0.f,0.f);
        quad[1].texCoords = sf::Vector2f(64.f,0.f);
        quad[2].texCoords = sf::Vector2f(64.f,64.f);
        quad[3].texCoords = sf::Vector2f(0.f,64.f);
    }
    return true;
}

void FoodRenderer::update(GameDataRef data)
{
    for(int j = 0; j < data->food.size(); j++)
    {
        // pointer to current ants vertices in vertex array.
        sf::Vertex* quad = &f_r_vertices[j * 4];
        //quad->color = sf::Color::Red;

        sf::Vector2f pos = data->food.at(j).pos;

        // defining the 4 corners of the "Sprite"
        quad[0].position = sf::Vector2f((pos.x * TILE_SIZE - 2) , (pos.y * TILE_SIZE - 2));
        quad[1].position = sf::Vector2f((pos.x * TILE_SIZE + 2) , (pos.y * TILE_SIZE - 2));
        quad[2].position = sf::Vector2f((pos.x * TILE_SIZE + 2) , (pos.y * TILE_SIZE + 2));
        quad[3].position = sf::Vector2f((pos.x * TILE_SIZE - 2) , (pos.y * TILE_SIZE + 2));

        // defining its 4 texture coordinates
        quad[0].texCoords = sf::Vector2f(0.f,0.f);
        quad[1].texCoords = sf::Vector2f(64.f,0.f);
        quad[2].texCoords = sf::Vector2f(64.f,64.f);
        quad[3].texCoords = sf::Vector2f(0.f,64.f);
    }
}