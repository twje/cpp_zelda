#pragma once

// Core
#include "Core/Sprite.h"

// Game
#include "Player.h"

class Weapon : public Sprite
{
public:
    Weapon(const Player &player);
};