#pragma once

#include <filesystem>
#include <functional>
#include <map>
#include <set>
#include <cassert>
#include <fstream>
#include <filesystem>

#include <Core/Base.h>

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

    ResourcePtr<T> Load(const std::string &path);

public:
    static void Create(const std::string configFilePath);
    static ResourceManager &GetInstance();

    // Getters
    std::unique_ptr<T> LoadUnique(const std::string &resourceID);
    std::shared_ptr<T> GetResource(const std::string &resourceID);
    std::vector<std::string> GetResourceIDs() const;

protected:
    std::map<std::string, std::string> mManifest;

private:
    std::map<std::string, std::weak_ptr<T>> mResources;
    std::set<std::shared_ptr<T>> mCachedResources;
};

#include "Core/ResourceManager/ResourceManager.inl"
