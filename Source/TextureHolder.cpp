#include "TextureHolder.hpp"

// Stores the texture in a unique pointer.
// access the texture with sf::Texture& get(Textures::ID id);
// chapter 2 SFML Game Developement Jan Haller, Henrik Vogelius Hansson, Artur Moreira
void TextureHolder::load(Textures::ID id, const std::string& filename)
{
    std::unique_ptr<sf::Texture> texture(new sf::Texture());
    if (!texture->loadFromFile(filename))
        throw std::runtime_error("TextureHolder::load - Failed to load "     + filename);

    auto inserted = mTextureMap.insert(std::make_pair(id,   std::move(texture)));
    assert(inserted.second);
}

sf::Texture& TextureHolder::get(Textures::ID id)
{
    auto found = mTextureMap.find(id);
    assert(found != mTextureMap.end());

    return *found->second;
}