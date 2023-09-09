#pragma once

#include <iostream>

// Core
#include "Core/Sprite.h"

// Forward declaration
class Player;
class Tile;

class Tile : public Sprite
{
public:
    Tile(GroupManager& groupManager, sf::Vector2f position, SpriteType spriteType, const std::shared_ptr<sf::Texture> &texture);
    sf::FloatRect GetHitbox() const override { return mHitBox; }    
    SpriteType GetSpriteType() { return mSpriteType; }

private:
    SpriteType mSpriteType;
    sf::FloatRect mHitBox;
};