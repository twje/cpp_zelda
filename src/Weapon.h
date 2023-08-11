#pragma once

// Core
#include "Core/Sprite.h"

// Game
#include "Player.h"

class Weapon : public Sprite
{
public:
    Weapon(const Player &player);

    // Getters
    static std::shared_ptr<sf::Texture> GetDirectionTexture(const Player &player);
    static std::shared_ptr<sf::Texture> GetIconTexture(const Player &player);
};