#include "AntRenderer.hpp"

bool AntRenderer::load(Colony &c)
{
    
    //if(!a_r_texture.loadFromFile("Assets/Graphics/antTextures.png"))
      //  return false;


    a_r_vertices.setPrimitiveType(sf::Quads);
    a_r_vertices.resize(COLONY_MAX_SIZE * 4);

    for(int j = 0; j < c.colSize; j++)
    {

        int spriteNum = 0;
        if(!c._ants[j]->hasFood)
            spriteNum = 1;
        
        // pointer to current ants vertices in vertex array.
        sf::Vertex* quad = &a_r_vertices[j * 4];
        quad->color = sf::Color::Red;

        // defining the 4 corners of the "Sprite"
        float degree = c._ants[j]->angle;
        float radians = degree * (3.1415 / 180);
        const sf::Vector2f dir_vec(cos(radians) * 10.f, sin(radians) * 10.f) ; // the * 10 is the length?
        float size_ratio = 1.f;// / 5.0f;
		const sf::Vector2f nrm_vec(-dir_vec.y * size_ratio, dir_vec.x * size_ratio);
        
        // defining the 4 corners of the "Sprite"
        quad[0].position = c._ants[j]->pos - nrm_vec + dir_vec;//sf::Vector2f((c._ants[j]->pos - nrm_vec + dir_vec), ((c._ants[j]->pos.y - 10));
        quad[1].position = c._ants[j]->pos + nrm_vec + dir_vec;//sf::Vector2f((c._ants[j]->pos.x + 10), (c._ants[j]->pos.y - 10));
        quad[2].position = c._ants[j]->pos + nrm_vec - dir_vec;//sf::Vector2f((c._ants[j]->pos.x + 10), (c._ants[j]->pos.y + 10));
        quad[3].position = c._ants[j]->pos - nrm_vec - dir_vec;//sf::Vector2f((c._ants[j]->pos.x - 10), (c._ants[j]->pos.y + 10));

        // defining its 4 texture coordinates
        quad[0].texCoords = sf::Vector2f(0.f,0.f);
        quad[1].texCoords = sf::Vector2f(64.f,0.f);
        quad[2].texCoords = sf::Vector2f(64.f,64.f);
        quad[3].texCoords = sf::Vector2f(0.f,64.f);
    }
    return true;
}

void AntRenderer::update(Colony &c)
{
    for(int j = 0; j < c.colSize; j++)
    {
        // pointer to current ants vertices in vertex array.
        sf::Vertex* quad = &a_r_vertices[j * 4];
        quad->color = sf::Color::Red;

        // defining the 4 corners of the "Sprite"
        float degree = c._ants[j]->angle;
        float radians = degree * (3.1415 / 180);
        const sf::Vector2f dir_vec(cos(radians) * 10.f, sin(radians) * 10.f) ;
        float size_ratio = 1.f;// / 5.0f;
        const sf::Vector2f nrm_vec(-dir_vec.y * size_ratio, dir_vec.x * size_ratio);
        
        // defining the 4 corners of the "Sprite"
        quad[0].position = c._ants[j]->pos - nrm_vec + dir_vec;//sf::Vector2f((c._ants[j]->pos - nrm_vec + dir_vec), ((c._ants[j]->pos.y - 10));
        quad[1].position = c._ants[j]->pos + nrm_vec + dir_vec;//sf::Vector2f((c._ants[j]->pos.x + 10), (c._ants[j]->pos.y - 10));
        quad[2].position = c._ants[j]->pos + nrm_vec - dir_vec;//sf::Vector2f((c._ants[j]->pos.x + 10), (c._ants[j]->pos.y + 10));
        quad[3].position = c._ants[j]->pos - nrm_vec - dir_vec;//sf::Vector2f((c._ants[j]->pos.x - 10), (c._ants[j]->pos.y + 10));

        //quad[0].position = sf::Vector2f(500 * j,500 * j);
        //quad[1].position = sf::Vector2f(550 * j,500 * j);
        //quad[2].position = sf::Vector2f(550 * j,550 * j);
        //quad[3].position = sf::Vector2f(500 * j,550 * j);

        // defining its 4 texture coordinates
        if(!c._ants[j]->hasFood)
        {
            quad[0].texCoords = sf::Vector2f(0.f,0.f);
            quad[1].texCoords = sf::Vector2f(64.f,0.f);
            quad[2].texCoords = sf::Vector2f(64.f,64.f);
            quad[3].texCoords = sf::Vector2f(0.f,64.f);
        }
        else
        {
            quad[0].texCoords = sf::Vector2f(64.f,0.f);
            quad[1].texCoords = sf::Vector2f(128.f,0.f);
            quad[2].texCoords = sf::Vector2f(128.f,64.f);
            quad[3].texCoords = sf::Vector2f(64.f,64.f);
        }
    }
}