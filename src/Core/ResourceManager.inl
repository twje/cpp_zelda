template <typename Derived, typename T>
ResourceManager<Derived, T> &ResourceManager<Derived, T>::GetInstance()
{
    static ResourceManager<typename Derived, typename T> instance;
    return instance;
}

// Loaders
template <typename Derived, typename T>
ResourcePtr<T> ResourceManager<typename Derived, typename T>::Load(const std::string &path)
{
    return static_cast<Derived *>(this)->Load(path);
}

template <typename Derived, typename T>
void ResourceManager<typename Derived, typename T>::LoadResource(const std::string resourceID, const std::string &filePath)
{
    assert(fs::is_regular_file(filePath));
    mResources[resourceID] = Load(filePath);
}

template <typename Derived, typename T>
void ResourceManager<typename Derived, typename T>::LoadResources(TextureIDGenerator generator, const std::string &directoryPath)
{
    assert(fs::is_directory(directoryPath));

    for (const auto &entry : fs::directory_iterator(directoryPath))
    {
        const fs::path &entryPath = entry.path();
        if (fs::is_regular_file(entryPath))
        {
            mResources[generator(entryPath.string())] = Load(entryPath.string());
        }
    }
}

// Getters
template <typename Derived, typename T>
const ResourcePtr<T> &ResourceManager<typename Derived, typename T>::GetResource(const std::string &resourceID) const
{
    auto iter = mResources.find(resourceID);
    assert(iter != mResources.end());
    return iter->second;
}

template <typename Derived, typename T>
std::vector<std::string> ResourceManager<typename Derived, typename T>::GetResourceIDs() const
{
    std::vector<std::string> resourceIDs;
    for (const auto &pair : mResources)
    {
        resourceIDs.emplace_back(pair.first);
    }
    return resourceIDs;
}