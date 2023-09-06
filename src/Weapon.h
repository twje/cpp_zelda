#pragma once

// Core
#include "Core/Sprite.h"

// Game
#include "Player.h"

class Weapon : public Sprite
{
public:
    Weapon(GroupManager& groupManager, const Player &player);
};