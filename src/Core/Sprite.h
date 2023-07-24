#pragma once

#include <SFML/Graphics.hpp>

#include "Rect.h"

class SpriteData
{
public:
    SpriteData() = default;

    // Setters
    void SetTexture(sf::Texture *texture) { mTexture = texture; }
    void SetTextureRegion(const sf::IntRect &textureRegion) { mTextureRegion = textureRegion; }
    void SetBoundingBox(const FloatRect &boundingBox) { mBoundingBox = boundingBox; }
    void SetHitBox(const FloatRect &hitBox) { mHitBox = hitBox; }

    // Getters
    const sf::Texture &GetTexture() const { return *mTexture; }
    const sf::IntRect &GetTextureRegion() const { return mTextureRegion; }
    const FloatRect &GetBoundingBox() const { return mBoundingBox; }
    const FloatRect &GetHitBox() const { return mHitBox; }

    // Mutable getters
    FloatRect &GetMutableBoundingBox() { return mBoundingBox; }
    FloatRect &GetMutableHitBox() { return mHitBox; }

private:
    sf::Texture *mTexture;
    sf::IntRect mTextureRegion;
    FloatRect mBoundingBox;
    FloatRect mHitBox;
};

class Sprite
{
public:
    virtual ~Sprite() = default;

    virtual const SpriteData &GetSpriteData() const = 0;
    virtual void Update(const sf::Time &timestamp){};
};