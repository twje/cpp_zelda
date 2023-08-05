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
    auto iter = mResources.find(resourceID);
    assert(iter != mResources.end() && iter->second.size() > 0);
    return iter->second.at(0);
}

template <typename Derived, typename T>
const ResourceVector<T> &ResourceManager<typename Derived, typename T>::GetResources() const
{
    ResourceVector<T> result;
    for (const auto &pair : mResources)
    {
        result.push_back(pair.second[0]);
    }
    return result;
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