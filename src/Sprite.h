#pragma once

#include <SFML/Graphics.hpp>

class Sprite
{
public:
    virtual ~Sprite() = default;

    virtual const sf::Texture &GetTexture() const = 0;
    virtual sf::FloatRect GetRect() const = 0;
};