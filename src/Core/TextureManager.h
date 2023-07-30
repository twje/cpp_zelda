#pragma once

#include <Core/Base.h>
#include <filesystem>
#include <functional>

namespace fs = std::filesystem;

class TextureManager
{
    using TextureIDGenerator = std::function<std::string(std::string)>;

private:
    TextureManager() = default;
    TextureManager(const TextureManager &) = delete;
    TextureManager &operator=(const TextureManager &) = delete;

public:
    static TextureManager &GetInstance();
    void LoadTexture(const std::string textureID, const std::string &filePath);
    void LoadTextures(const std::string textureID, const std::string &directoryPath);
    void LoadTextures(TextureIDGenerator generator, const std::string &directoryPath);
    const TexturePtr &GetTexture(const std::string &textureID) const;
    const TexturePtr &GetTextureAtIndex(const std::string &textureID, size_t index) const;
    const TextureVector &GetTextures(const std::string &textureID) const;
    static Scope<sf::Texture> LoadTexture(const std::string &filePath);

private:
    const TexturePtr defaultTexture = nullptr;
    TextureMap mTextures;
};