#pragma once

#include <SFML/Graphics.hpp>

#include "Rect.h"

// Forward declaration
class SpriteData;

class SpriteDataView
{
public:
    SpriteDataView(const SpriteData &data)
        : mData(data)
    {
    }

    const sf::Texture &GetTexture() const;
    const sf::IntRect &GetTextureRegion() const;
    const FloatRect &GetBoundingBox() const;
    const FloatRect &GetHitBox() const;

private:
    const SpriteData &mData;
};