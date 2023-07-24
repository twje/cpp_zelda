#pragma once

#include <SFML/Graphics.hpp>

#include "Core/SpriteDataView.h"
#include "Rect.h"

class SpriteData
{
public:
    SpriteData() : mView(*this)
    {
    }

    sf::Texture *mTexture;
    sf::IntRect mTextureRegion;
    FloatRect mBoundingBox;
    FloatRect mHitBox;

    const SpriteDataView &GetDataView() const { return mView; }

private:
    SpriteDataView mView;
};