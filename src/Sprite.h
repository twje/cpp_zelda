#pragma once

#include <SFML/Graphics.hpp>

#include "Rect.h"

class Sprite
{
public:
    virtual ~Sprite() = default;

    virtual const sf::Texture &GetTexture() const = 0;
    virtual Util::FloatRect GetRect() const = 0;
    virtual void Update(){};
    virtual void DrawHitbox(sf::RenderWindow &window){};
    virtual void DrawRect(sf::RenderWindow &window){};
};