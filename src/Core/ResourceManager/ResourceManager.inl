template <typename Derived, typename T>
ResourceManager<Derived, T> *ResourceManager<Derived, T>::mInstance = nullptr;

template <typename Derived, typename T>
void ResourceManager<Derived, T>::Create(const std::string configFilePath)
{
    assert(mInstance == nullptr);
    mInstance = new ResourceManager();

    std::ifstream file(configFilePath);
    if (!file)
    {
        throw std::runtime_error("Failed to load configuration file " + configFilePath);
    }

    std::string line;
    while (std::getline(file, line))
    {
        auto isSpace = [](char c)
        {
            return std::isspace(c);
        };
        if (line.empty() || std::all_of(line.begin(), line.end(), isSpace) || line[0] == '#')
        {
            continue;
        }

        std::istringstream iss(line);
        std::string resourceID, resourcePath;
        if (std::getline(iss >> std::ws, resourceID, ',') && std::getline(iss >> std::ws, resourcePath, ','))
        {
            mInstance->mManifest.emplace(resourceID, resourcePath);
        }
    }
}

template <typename Derived, typename T>
ResourceManager<Derived, T> &ResourceManager<Derived, T>::GetInstance()
{
    assert(mInstance != nullptr);
    return *mInstance;
}

template <typename Derived, typename T>
ResourcePtr<T> ResourceManager<typename Derived, typename T>::Load(const std::string &path)
{
    return static_cast<Derived *>(this)->Load(path);
}

// Getters
template <typename Derived, typename T>
std::shared_ptr<T> ResourceManager<typename Derived, typename T>::GetResource(const std::string &resourceID)
{
    auto iter = mResources.find(resourceID);
    if (iter != mResources.end())
    {
        if (auto resource = iter->second.lock())
        {
            return resource;
        }
    }

    ResourcePtr<T> resource = Load(mManifest[resourceID]);
    mResources[resourceID] = resource;
    return resource;
}

template <typename Derived, typename T>
std::vector<std::string> ResourceManager<typename Derived, typename T>::GetResourceIDs() const
{
    std::vector<std::string> resourceIDs;
    for (const auto &pair : mManifest)
    {
        resourceIDs.emplace_back(pair.first);
    }
    return resourceIDs;
}