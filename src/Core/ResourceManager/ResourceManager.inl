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
            mInstance->LoadResource(resourceID, resourcePath);
        }
    }
}

template <typename Derived, typename T>
ResourceManager<Derived, T> &ResourceManager<Derived, T>::GetInstance()
{
    assert(mInstance != nullptr);
    return *mInstance;
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
const ResourcePtr<T> &ResourceManager<typename Derived, typename T>::GetResource(const std::string &resourceID)
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