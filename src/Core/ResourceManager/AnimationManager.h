#pragma once

#include <memory>

#include <yaml-cpp/yaml.h>

// Core Game
#include "Core/ResourceManager/ResourceManager.h"
#include "Core/Animation/Animation.h"

class AnimationManager : public ResourceManager<AnimationManager, Animation>
{
public:
    std::shared_ptr<Animation> Load(const std::string &filePath)
    {
        auto animation = std::make_shared<Animation>();
        animation->LoadFromFile(filePath);
        return animation;
    }

    std::unique_ptr<Animation> LoadUnique(const std::string resourceID)
    {
        auto animation = std::make_unique<Animation>();
        animation->LoadFromFile(mManifest[resourceID]);
        return animation;
    }
};
