#pragma once

#include <memory>

#include <yaml-cpp/yaml.h>

// Core Game
#include "Core/ResourceManager/ResourceManager.h"
#include "Core/GuiStyle.h"

class GUIStyleManager : public ResourceManager<GUIStyleManager, GuiStyle>
{
public:
    std::shared_ptr<GuiStyle> Load(const std::string &filePath)
    {
        std::shared_ptr<GuiStyle> guiStyle = std::make_shared<GuiStyle>();
        GuiStyleSerializer::Deserialize(*guiStyle, filePath);
        return guiStyle;
    }
};
