#pragma once

#include <iostream>

// Game
#include "EntityBase.h"

// Forward declaration
class Player;
class Tile;

class Tile : public EntityBase
{
public:
    Tile(GroupManager& groupManager, sf::Vector2f position, SpriteType spriteType, const std::shared_ptr<sf::Texture> &texture);
    sf::FloatRect GetHitbox() const override { return mHitBox; }
    virtual void Accept(EntityVisitor& visitor) { visitor.Visit(*this); }

private:
    SpriteType mSpriteType;
    sf::FloatRect mHitBox;
};