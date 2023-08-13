#pragma once

#include "Core/ResourceManager/ResourceManager.h"

std::string NormalzeResourceID(const std::string &resourceID);

template <typename Derived, typename T>
ResourceMap<T> GroupResourcesByPrefix(ResourceManager<Derived, T> &manager)
{
    ResourceMap<T> result;
    for (const std::string &resourceID : manager.GetResourceIDs())
    {
        std::string prefix = NormalzeResourceID(resourceID);
        result[prefix].emplace_back(manager.GetResource(resourceID));
    }
    return result;
}

template <typename Derived, typename T>
std::map<std::string, std::vector<std::string>> GroupResources(ResourceManager<Derived, T> &manager)
{
    std::map<std::string, std::vector<std::string>> result;
    for (const std::string &resourceID : manager.GetResourceIDs())
    {
        std::string prefix = NormalzeResourceID(resourceID);
        result[prefix].emplace_back(resourceID);
    }
    return result;
}