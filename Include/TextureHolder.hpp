#ifndef TEXTUREHOLDER_HPP
#define TEXTUREHOLDER_HPP
#include <map>
#include <memory>
#include <assert.h>
#include <SFML/Graphics.hpp>

namespace Textures
{
    enum ID {Ant, AntFood};
}

class TextureHolder
{
    public:
        void                  load(Textures::ID id,const std::string& filename);
        sf::Texture&          get(Textures::ID id);
        const sf::Texture&    get(Textures::ID id) const;
    private:
        std::map<Textures::ID,std::unique_ptr<sf::Texture>> mTextureMap;
};

#endif