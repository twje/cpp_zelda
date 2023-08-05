#pragma once

#include "Core/ResourceManager.h"

namespace TextureIDGeneratorPresets
{
    std::string ExtractLastDirectoryWithFilename(const fs::path &filePath);
}
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
