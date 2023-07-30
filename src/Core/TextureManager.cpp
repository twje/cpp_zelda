#include "Core/TextureManager.h"

namespace TextureIDGeneratorPresets
{
    std::string ExtractSecondLastDirectoryWithFilename(const fs::path &filePath)
    {
        std::string filenameWithoutExtension = filePath.stem().string();
        fs::path parentDir = filePath.parent_path();

        // Get the second last directory name
        fs::path secondLastDir;
        auto it = parentDir.begin();
        std::advance(it, std::distance(parentDir.begin(), parentDir.end()) - 1);
        secondLastDir = *it;

        return secondLastDir.string() + "_" + filenameWithoutExtension;
    }
}

TextureManager &TextureManager::GetInstance()
{
    static TextureManager instance;
    return instance;
}

void TextureManager::LoadTexture(const std::string textureID, const std::string &filePath)
{
    TexturePtr texturePtr = std::make_shared<sf::Texture>();
    if (!texturePtr->loadFromFile(filePath))
    {
        throw std::runtime_error("Failed to load texture: " + filePath);
    }
    mTextures[textureID].emplace_back(texturePtr);
}

void TextureManager::LoadTextures(const std::string textureID, const std::string &directoryPath)
{
    TextureVector textureVector;
    for (const auto &entry : fs::directory_iterator(directoryPath))
    {
        const fs::path &entryPath = entry.path();
        if (fs::is_regular_file(entryPath))
        {
            TexturePtr texture = CreateScope<sf::Texture>();
            if (!texture->loadFromFile(entryPath.string()))
            {
                throw std::runtime_error("Failed to load texture: " + entryPath.string());
            }
            textureVector.emplace_back(texture);
        }
    }
    mTextures.emplace(textureID, std::move(textureVector));
}

void TextureManager::LoadTextures(TextureIDGenerator generator, const std::string &directoryPath)
{
    for (const auto &entry : fs::directory_iterator(directoryPath))
    {
        const fs::path &entryPath = entry.path();
        if (fs::is_regular_file(entryPath))
        {
            TexturePtr texture = CreateScope<sf::Texture>();
            if (!texture->loadFromFile(entryPath.string()))
            {
                throw std::runtime_error("Failed to load texture: " + entryPath.string());
            }
            TextureVector textureVector{texture};
            mTextures.emplace(generator(entryPath.string()), std::move(textureVector));
        }
    }
}

const TexturePtr &TextureManager::GetTexture(const std::string &textureID) const
{
    const auto &textures = mTextures.at(textureID);
    return textures.empty() ? defaultTexture : textures[0];
}

const TexturePtr &TextureManager::GetTextureAtIndex(const std::string &textureID, size_t index) const
{
    const auto &textures = mTextures.at(textureID);
    return index < textures.size() ? textures[index] : defaultTexture;
}

const TextureVector &TextureManager::GetTextures(const std::string &textureID) const
{
    return mTextures.at(textureID);
}

Scope<sf::Texture> TextureManager::LoadTexture(const std::string &filePath)
{
    sf::Texture texture;
    if (!texture.loadFromFile(filePath))
    {
        throw std::runtime_error("Failed to load texture: " + filePath);
    }
    return std::make_unique<sf::Texture>(std::move(texture));
}