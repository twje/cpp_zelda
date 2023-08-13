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
        return nullptr;
    }
};
