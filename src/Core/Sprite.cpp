#include "Core/Sprite.h"
#include "Core/SpriteGroup.h"

void Sprite::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
{
    sf::RenderStates statesCopy(states);
    statesCopy.transform *= getTransform();
    target.draw(mSprite, statesCopy);
}

void Sprite::setTexture(const sf::Texture &texture, bool setDefaultTextureRect)
{
    mSprite.setTexture(texture);
    if (setDefaultTextureRect)
    {
        sf::IntRect textureRect(sf::Vector2i(), sf::Vector2i(texture.getSize()));
        mSprite.setTextureRect(textureRect);
    }
}

void Sprite::Kill()
{
    for (auto spriteGroup : mSpriteGroups)
    {
        spriteGroup->RemoveSprite(*this);
    }
}