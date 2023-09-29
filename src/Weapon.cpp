#include "Weapon.h"

#include <sstream>

#include <SFML/Graphics.hpp>

// Core
#include "Core/RectUtils.h"
#include "Core/ResourceManager/TextureManager.h"

// Game
#include "Settings.h"

Weapon::Weapon(GroupManager& groupManager, const Player &player)
    : Sprite(groupManager)
{
    SetTexture(player.GetWeaponTexture(), true);

    PlayerDirection direction = player.GetDirection();
    if (direction == PlayerDirection::RIGHT)
    {
        SetPosition(GetRectMidRight(player.GetGlobalBounds()) - GetRectMidLeft(GetLocalBounds()) + sf::Vector2f(0, 16));
    }
    else if (direction == PlayerDirection::LEFT)
    {
        SetPosition(GetRectMidLeft(player.GetGlobalBounds()) - GetRectMidRight(GetLocalBounds()) + sf::Vector2f(0, 16));
    }
    else if (direction == PlayerDirection::DOWN)
    {
        SetPosition(GetRectMidBottom(player.GetGlobalBounds()) - GetRectMidTop(GetLocalBounds()) + sf::Vector2f(-10, 0));
    }
    else
    {
        SetPosition(GetRectMidTop(player.GetGlobalBounds()) - GetRectMidBottom(GetLocalBounds()) + sf::Vector2f(-10, 0));
    }    
}