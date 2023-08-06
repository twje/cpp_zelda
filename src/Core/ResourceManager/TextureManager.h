#pragma once

#include "Core/ResourceManager/ResourceManager.h"

using TexturePtr = ResourcePtr<sf::Texture>;
using TextureVector = ResourceVector<sf::Texture>;
using TextureMap = ResourceMap<sf::Texture>;

class TextureManager : public ResourceManager<TextureManager, sf::Texture>
{
public:
    TexturePtr Load(const std::string &filePath)
    {
        TexturePtr texturePtr = std::make_shared<sf::Texture>();
        if (!texturePtr->loadFromFile(filePath))
        {
            throw std::runtime_error("Failed to load texture: " + filePath);
        }
        return texturePtr;
    }
};
