#pragma once

#include <Core/Base.h>
#include <filesystem>

namespace fs = std::filesystem;

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