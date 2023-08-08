#pragma once

#include <filesystem>
#include <functional>
#include <map>
#include <cassert>
#include <fstream>

#include <Core/Base.h>

namespace fs = std::filesystem;

// Type aliases
template <typename T>
using ResourcePtr = std::shared_ptr<T>;
template <typename T>
using ResourceVector = std::vector<ResourcePtr<T>>;
template <typename T>
using ResourceMap = std::map<std::string, ResourceVector<T>>;

template <typename Derived, typename T>
class ResourceManager
{
    using TextureIDGenerator = std::function<std::string(std::string)>;

private:
    static ResourceManager *mInstance;

    ResourceManager() = default;
    ResourceManager(const ResourceManager &) = delete;
    ResourceManager &operator=(const ResourceManager &) = delete;

    // Loaders
    ResourcePtr<T> Load(const std::string &path);
    void LoadResource(const std::string resourceID, const std::string &filePath);

public:
    static void Create(const std::string configFilePath);
    static ResourceManager &GetInstance();

    // Getters
    const ResourcePtr<T> &GetResource(const std::string &resourceID);
    std::vector<std::string> GetResourceIDs() const;

private:
    std::map<std::string, ResourcePtr<T>> mResources;
};

#include "Core/ResourceManager/ResourceManager.inl"
