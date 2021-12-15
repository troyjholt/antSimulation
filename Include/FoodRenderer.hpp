#include <SFML/Graphics.hpp>
#include "Colony.hpp"
#include "Game.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

class FoodRenderer : public sf::Drawable, public sf::Transformable
{
    public:
        bool load(GameDataRef data);
        void update(GameDataRef data);
        sf::VertexArray f_r_vertices;
        sf::Texture f_r_texture;
    
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            // apply the transform
            states.transform *= getTransform();

            // apply the tileset texture
            states.texture = &f_r_texture;

            // draw the vertex array
            target.draw(f_r_vertices, states);
        }
};