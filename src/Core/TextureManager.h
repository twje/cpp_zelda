#pragma once

#include <Core/Base.h>
#include <filesystem>
#include <functional>

namespace fs = std::filesystem;

namespace TextureIDGeneratorPresets
{
    std::string ExtractLastDirectoryWithFilename(const fs::path &filePath);
}

template <typename Derived, typename T>
class ResourceManager
{
    using TextureIDGenerator = std::function<std::string(std::string)>;

private:
    ResourceManager() = default;
    ResourceManager(const ResourceManager &) = delete;
    ResourceManager &operator=(const ResourceManager &) = delete;

public:
    static ResourceManager &ResourceManager::GetInstance()
    {
        static ResourceManager instance;
        return instance;
    }

    // Loaders
    TexturePtr Load(const std::string &path)
    {
        return static_cast<Derived *>(this)->Load(path);
    }

    void LoadResource(const std::string resourceID, const std::string &filePath)
    {
        assert(fs::is_regular_file(filePath));
        TexturePtr resourcePtr = Load(filePath);
        mResources[resourceID].emplace_back(resourcePtr);
    }

    void LoadResources(const std::string resourceID, const std::string &directoryPath)
    {
        assert(fs::is_directory(directoryPath));

        TextureVector resourceVector;
        for (const auto &entry : fs::directory_iterator(directoryPath))
        {
            const fs::path &entryPath = entry.path();
            if (fs::is_regular_file(entryPath))
            {
                TexturePtr resourcePtr = Load(entryPath.string());
                resourceVector.emplace_back(resourcePtr);
            }
        }
        mResources.emplace(resourceID, std::move(resourceVector));
    }

    void LoadResources(TextureIDGenerator generator, const std::string &directoryPath)
    {
        assert(fs::is_directory(directoryPath));

        for (const auto &entry : fs::directory_iterator(directoryPath))
        {
            const fs::path &entryPath = entry.path();
            if (fs::is_regular_file(entryPath))
            {
                TexturePtr resourcePtr = Load(entryPath.string());
                TextureVector resourceVector{resourcePtr};
                mResources.emplace(generator(entryPath.string()), std::move(resourceVector));
            }
        }
    }

    // Getters
    const TexturePtr &GetResource(const std::string &resourceID) const
    {
        return GetResourceAtIndex(resourceID, 0);
    }

    const TexturePtr &GetResourceAtIndex(const std::string &resourceID, size_t index) const
    {
        auto iter = mResources.find(resourceID);
        assert(iter != mResources.end() && iter->second.size() > 0);
        return iter->second.at(index);
    }

    const TextureVector &GetResources(const std::string &resourceID) const
    {
        return mResources.at(resourceID);
    }

private:
    TextureMap mResources;
};

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
