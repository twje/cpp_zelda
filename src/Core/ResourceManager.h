#pragma once

#include <filesystem>
#include <functional>

#include <Core/Base.h>

namespace fs = std::filesystem;

template <typename Derived, typename T>
class ResourceManager
{
    using TextureIDGenerator = std::function<std::string(std::string)>;

private:
    ResourceManager() = default;
    ResourceManager(const ResourceManager &) = delete;
    ResourceManager &operator=(const ResourceManager &) = delete;

public:
    static ResourceManager &GetInstance();

    // Loaders
    ResourcePtr<T> Load(const std::string &path);
    void LoadResource(const std::string resourceID, const std::string &filePath);
    void LoadResources(const std::string resourceID, const std::string &directoryPath);
    void LoadResources(TextureIDGenerator generator, const std::string &directoryPath);

    // Getters
    const ResourcePtr<T> &GetResource(const std::string &resourceID) const;
    const ResourcePtr<T> &GetResourceAtIndex(const std::string &resourceID, size_t index) const;
    const ResourceVector<T> &GetResources(const std::string &resourceID) const;

private:
    ResourceMap<T> mResources;
};

#include "Core/ResourceManager.inl"
