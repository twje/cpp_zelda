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
    ResourcePtr<T> resourcePtr = Load(filePath);
    mResources[resourceID].emplace_back(resourcePtr);
}

template <typename Derived, typename T>
void ResourceManager<typename Derived, typename T>::LoadResources(const std::string resourceID, const std::string &directoryPath)
{
    assert(fs::is_directory(directoryPath));

    ResourceVector<T> resourceVector;
    for (const auto &entry : fs::directory_iterator(directoryPath))
    {
        const fs::path &entryPath = entry.path();
        if (fs::is_regular_file(entryPath))
        {
            ResourcePtr<T> resourcePtr = Load(entryPath.string());
            resourceVector.emplace_back(resourcePtr);
        }
    }
    mResources.emplace(resourceID, std::move(resourceVector));
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
            ResourcePtr<T> resourcePtr = Load(entryPath.string());
            ResourceVector<T> resourceVector{resourcePtr};
            mResources.emplace(generator(entryPath.string()), std::move(resourceVector));
        }
    }
}

// Getters
template <typename Derived, typename T>
const ResourcePtr<T> &ResourceManager<typename Derived, typename T>::GetResource(const std::string &resourceID) const
{
    return GetResourceAtIndex(resourceID, 0);
}

template <typename Derived, typename T>
const ResourcePtr<T> &ResourceManager<typename Derived, typename T>::GetResourceAtIndex(const std::string &resourceID, size_t index) const
{
    auto iter = mResources.find(resourceID);
    assert(iter != mResources.end() && iter->second.size() > 0);
    return iter->second.at(index);
}

template <typename Derived, typename T>
const ResourceVector<T> &ResourceManager<typename Derived, typename T>::GetResources(const std::string &resourceID) const
{
    return mResources.at(resourceID);
}
