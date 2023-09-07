#pragma once

// Core
#include "Core/Sprite.h"

// Forward declaration
class Tile;
class Enemy;

class EntityVisitor
{
public:
    virtual void Visit(Tile& tile) {}
    virtual void Visit(Enemy& enemy) {}
};

class EntityBase : public Sprite
{
public:
    EntityBase(GroupManager& groupManager);
    EntityBase(GroupManager& groupManager, const std::shared_ptr<sf::Texture>& texture);

    virtual void Accept(EntityVisitor& visitor) {}
};