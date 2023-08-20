#pragma once

#include <memory>

#include <yaml-cpp/yaml.h>

#include <SFML/Graphics.hpp>

// Core Game
#include "Core/ResourceManager/ResourceManager.h"

class FontManager : public ResourceManager<FontManager, sf::Font>
{
public:
    std::shared_ptr<sf::Font> Load(const std::string &filePath)
    {
        std::shared_ptr<sf::Font> font = std::make_shared<sf::Font>();
        if (!font->loadFromFile(filePath))
        {
            throw std::runtime_error("Failed to load font: " + filePath);
        }
        return font;
    }

    std::unique_ptr<sf::Font> LoadUnique(const std::string resourceID)
    {
        throw std::runtime_error("Not implemented");
    }
};
