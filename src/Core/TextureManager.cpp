#include "Core/TextureManager.h"

#include <cassert>

namespace TextureIDGeneratorPresets
{
    std::string ExtractLastDirectoryWithFilename(const fs::path &filePath)
    {
        assert(fs::is_regular_file(filePath));

        std::string filenameWithoutExtension = filePath.stem().string();
        fs::path parentDir = filePath.parent_path();

        fs::path lastDir;
        auto it = parentDir.begin();
        std::advance(it, std::distance(parentDir.begin(), parentDir.end()) - 1);
        lastDir = *it;

        return lastDir.string() + "_" + filenameWithoutExtension;
    }
}

TextureManager &TextureManager::GetInstance()
{
    static TextureManager instance;
    return instance;
}

void TextureManager::LoadTexture(const std::string textureID, const std::string &filePath)
{
    assert(fs::is_regular_file(filePath));

    TexturePtr texturePtr = std::make_shared<sf::Texture>();
    if (!texturePtr->loadFromFile(filePath))
    {
        throw std::runtime_error("Failed to load texture: " + filePath);
    }
    mTextures[textureID].emplace_back(texturePtr);
}

void TextureManager::LoadTextures(const std::string textureID, const std::string &directoryPath)
{
    assert(fs::is_directory(directoryPath));

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
    assert(fs::is_directory(directoryPath));

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
    return GetTextureAtIndex(textureID, 0);
}

const TexturePtr &TextureManager::GetTextureAtIndex(const std::string &textureID, size_t index) const
{
    auto iter = mTextures.find(textureID);
    assert(iter != mTextures.end() && iter->second.size() > 0);
    return iter->second.at(index);
}

const TextureVector &TextureManager::GetTextures(const std::string &textureID) const
{
    return mTextures.at(textureID);
}

Scope<sf::Texture> TextureManager::LoadTexture(const std::string &filePath)
{
    assert(fs::is_regular_file(filePath));

    sf::Texture texture;
    if (!texture.loadFromFile(filePath))
    {
        throw std::runtime_error("Failed to load texture: " + filePath);
    }
    return std::make_unique<sf::Texture>(std::move(texture));
}