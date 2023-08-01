#include "Weapon.h"

#include <sstream>

#include <SFML/Graphics.hpp>

// Core
#include "Core/RectUtils.h"
#include "Core/TextureManager.h"

Weapon::Weapon(const Player &player)
    : Sprite()
{
    std::string direction = player.GetDirection();

    // Init texture
    std::ostringstream oss;
    oss << player.GetWeapon() << "_" << direction;
    std::string textureID = oss.str();
    SetTexture(*TextureManager::GetInstance().GetTexture(textureID), true);

    // Set position
    if (direction == "right")
    {
        SetPosition(GetRectMidRight(player.GetGlobalBounds()) - GetRectMidLeft(GetLocalBounds()) + sf::Vector2f(0, 16));
    }
    else if (direction == "left")
    {
        SetPosition(GetRectMidLeft(player.GetGlobalBounds()) - GetRectMidRight(GetLocalBounds()) + sf::Vector2f(0, 16));
    }
    else if (direction == "down")
    {
        SetPosition(GetRectMidBottom(player.GetGlobalBounds()) - GetRectMidTop(GetLocalBounds()) + sf::Vector2f(-10, 0));
    }
    else
    {
        SetPosition(GetRectMidTop(player.GetGlobalBounds()) - GetRectMidBottom(GetLocalBounds()) + sf::Vector2f(-10, 0));
    }
}
