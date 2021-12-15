#include <SFML/Graphics.hpp>
#include "Colony.hpp"
#include "Game.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

class PheromoneRenderer : public sf::Drawable, public sf::Transformable
{
    public:
        bool load(Colony &c);
        void update(Colony &c);
        sf::VertexArray p_r_vertices;
        sf::Texture p_r_texture;
    
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            // apply the transform
            states.transform *= getTransform();

            // apply the tileset texture
            states.texture = &p_r_texture;

            // draw the vertex array
            target.draw(p_r_vertices, states);
        }
};