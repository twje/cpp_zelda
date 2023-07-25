// Core
#include "Core/Sprite.h"
#include "Core/Rect.h"

// Game
#include "Tile.h"
#include "Settings.h"

Tile::Tile(sf::Vector2f position, SpriteType spriteType, sf::Texture &texture)
    : Sprite()
{
    mData.mTexture = &texture;
    mData.mTextureRegion = sf::IntRect(sf::Vector2i(), sf::Vector2i(mData.mTexture->getSize()));
    mData.mBoundingBox = FloatRect(position, sf::Vector2f(mData.mTexture->getSize()));

    if (spriteType == SpriteType::OBJECT)
    {
        mData.mBoundingBox.AnchorPosition(Anchor::TOP_LEFT, sf::Vector2f(position.x, position.y - TILESIZE));
    }
    mData.mHitBox = mData.mBoundingBox.Inflate(0, -10);
}

void Tile::Draw(sf::RenderWindow &window)
{
    const SpriteDataView &data = GetSpriteData();
    sf::Sprite sprite(data.GetTexture());
    sprite.setTextureRect(data.GetTextureRegion());
    sprite.setPosition(data.GetBoundingBox().GetPosition());
    window.draw(sprite);
}