#pragma once

// Core
#include "Core/Component.h"

// Game
#include "Settings.h"

// Forward declaration
class Player;

class AttackableComponent : public Component
{
public:
    virtual void InflictDemage(const Player &player, GameObject &attacker){};
    virtual bool IsDead() = 0;
};

class TypeComponent : public Component
{
public:
    TypeComponent(SpriteType spriteType)
        : mSpriteType(spriteType)
    {
    }

    SpriteType GetSpriteType() { return mSpriteType; }

private:
    SpriteType mSpriteType;
};