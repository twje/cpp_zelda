#pragma once

#include "Core/SpriteData.h"

class Sprite
{
public:
    virtual ~Sprite() = default;

    virtual const SpriteDataView &GetSpriteData() const = 0;
    virtual void Update(const sf::Time &timestamp){};

protected:
    SpriteData mData;
};