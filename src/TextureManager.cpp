#include "TextureManager.h"

TextureManager &TextureManager::GetInstance()
{
    static TextureManager instance;
    return instance;
}

void TextureManager::LoadTexture(const std::string textureID, const std::string &filePath)
{
    sf::Texture texture;
    if (!texture.loadFromFile(filePath))
    {
        throw std::runtime_error("Failed to load texture: " + filePath);
    }
    mTextures[textureID].emplace_back(std::make_shared<sf::Texture>(std::move(texture)));
}

void TextureManager::LoadTextures(const std::string textureID, const std::string &directoryPath)
{
    TextureVector textures;
    LoadTexturesFromDirectoryRecursive(textures, directoryPath);
    mTextures[textureID] = std::move(textures);
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

const TextureVector &TextureManager::GetAllTextures(const std::string &textureID) const
{
    return mTextures.at(textureID);
}

void TextureManager::AddTexture(const std::string &textureID, const TexturePtr &texture)
{
    mTextures[textureID].push_back(texture);
}

void TextureManager::LoadTexturesFromDirectoryRecursive(TextureVector &textureVectorOut, const fs::path &directoryPath)
{
    for (const auto &entry : fs::directory_iterator(directoryPath))
    {
        const fs::path &entryPath = entry.path();

        if (fs::is_regular_file(entryPath))
        {
            sf::Texture texture;
            if (!texture.loadFromFile(entryPath.string()))
            {
                throw std::runtime_error("Failed to load texture: " + entryPath.string());
            }
            textureVectorOut.emplace_back(std::make_shared<sf::Texture>(std::move(texture)));
        }
        else if (fs::is_directory(entryPath))
        {
            LoadTexturesFromDirectoryRecursive(textureVectorOut, entryPath);
        }
    }
}
