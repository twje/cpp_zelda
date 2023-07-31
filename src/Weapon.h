#pragma once

#include <sstream>

#include <SFML/Graphics.hpp>

// Core
#include "Core/RectUtils.h"
#include "Core/TextureManager.h"

// Game
#include "Core/Sprite.h"
#include "Constants.h"
#include "Player.h"

class Weapon : public Sprite
{
public:
    Weapon(const Player &player)
        : Sprite()
    {
        std::string direction = player.GetDirection();

        // Init texture
        std::ostringstream oss;
        oss << player.GetWeapon() << "_" << direction;
        std::string textureID = oss.str();
        setTexture(*TextureManager::GetInstance().GetTexture(textureID), true);

        // Set position
        if (direction == "right")
        {
            setPosition(GetRectMidRight(player.GetGlobalBounds()) - GetRectMidLeft(GetLocalBounds()) + sf::Vector2f(0, 16));
        }
        else if (direction == "left")
        {
            setPosition(GetRectMidLeft(player.GetGlobalBounds()) - GetRectMidRight(GetLocalBounds()) + sf::Vector2f(0, 16));
        }
        else if (direction == "down")
        {
            setPosition(GetRectMidBottom(player.GetGlobalBounds()) - GetRectMidTop(GetLocalBounds()) + sf::Vector2f(-10, 0));
        }
        else
        {
            setPosition(GetRectMidTop(player.GetGlobalBounds()) - GetRectMidBottom(GetLocalBounds()) + sf::Vector2f(-10, 0));
        }
    }
};
