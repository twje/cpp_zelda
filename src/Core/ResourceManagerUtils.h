#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>

#include <SFML/Graphics.hpp>

#include "Core/ResourceManager.h"

// Thinl about const

template <typename Derived, typename T>
class IndexResourcesViaPrefix
{
public:
    IndexResourcesViaPrefix(const ResourceManager<Derived, T> &manager)
        : mManager(manager)
    {
    }

    void AddResource(const std::string &resourceID)
    {
        std::string prefix = NormalzeResourceID(resourceID);
        mResourceMap[prefix].emplace_back(mManager.GetResource(resourceID));
    }

    ResourceMap<T> GetResources() { return mResourceMap; }

private:
    std::string NormalzeResourceID(const std::string &resourceID)
    {
        size_t underscorePos = resourceID.find_last_of('_');
        if (underscorePos != std::string::npos)
        {
            bool isAllDigits = true;
            for (size_t i = underscorePos + 1; i < resourceID.size(); ++i)
            {
                if (!std::isdigit(resourceID[i]))
                {
                    isAllDigits = false;
                    break;
                }
            }

            if (isAllDigits)
            {
                return resourceID.substr(0, underscorePos);
            }
        }
        return resourceID;
    }

private:
    const ResourceManager<Derived, T> &mManager;
    ResourceMap<T> mResourceMap;
};
