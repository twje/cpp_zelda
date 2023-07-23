#pragma once

#include <SFML/Graphics.hpp>

#include "Rect.h"

class Sprite
{
public:
    virtual ~Sprite() = default;

    virtual const sf::Texture &GetTexture() const = 0;
    virtual sf::IntRect GetTextureRegion() const = 0;
    virtual FloatRect GetRect() const = 0;
    virtual FloatRect GetHitbox() const = 0;
    virtual void Update(const sf::Time &timestamp){};
};