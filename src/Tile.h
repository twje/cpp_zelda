#pragma once

#include <iostream>

// Core
#include "Core/Sprite.h"

// Game
#include "Components.h"

// Forward declaration
class Player;
class Tile;

class TileAttackableComponent : public AttackableComponent
{
public:
    bool IsDead() override { return true; };
};

class Tile : public Sprite
{
public:
    Tile(GroupManager& groupManager, sf::Vector2f position, SpriteType spriteType, const std::shared_ptr<sf::Texture> &texture);
    sf::FloatRect GetHitbox() const override { return mHitBox; }

private:
    SpriteType mSpriteType;
    sf::FloatRect mHitBox;
};