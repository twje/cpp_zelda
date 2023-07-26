#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <filesystem>

#include <SFML/Graphics.hpp>

namespace fs = std::filesystem;

using TexturePtr = std::shared_ptr<const sf::Texture>;
using TextureVector = std::vector<TexturePtr>;
using TextureMap = std::unordered_map<std::string, TextureVector>;

class TextureManager
{
private:
    TextureManager() = default;
    TextureManager(const TextureManager &) = delete;
    TextureManager &operator=(const TextureManager &) = delete;

public:
    static TextureManager &GetInstance();
    void LoadTexture(const std::string textureID, const std::string &filePath);
    void LoadTextures(const std::string textureID, const std::string &directoryPath);
    const TexturePtr &GetTexture(const std::string &textureID) const;
    const TexturePtr &GetTextureAtIndex(const std::string &textureID, size_t index) const;
    const TextureVector &GetAllTextures(const std::string &textureID) const;
    void AddTexture(const std::string &textureID, const TexturePtr &texture);

private:
    void LoadTexturesFromDirectoryRecursive(TextureVector &textureVectorOut, const fs::path &directoryPath);

private:
    const TexturePtr defaultTexture = nullptr;
    TextureMap mTextures;
};