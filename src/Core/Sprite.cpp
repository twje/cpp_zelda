#include "Core/Sprite.h"
#include "Core/Group.h"

Sprite::Sprite(const std::shared_ptr<sf::Texture> &texture)
    : mTexture(texture),
      mSprite(*texture)
{
}

Sprite::Sprite()
    : mSprite(GetPlaceholderTexture())
{
}

void Sprite::SetTexture(const std::shared_ptr<sf::Texture> &texture, bool resetRect)
{
    mTexture = texture;
    mSprite.setTexture(*mTexture, resetRect);
}

void Sprite::SetAlpha(uint8_t value)
{
    sf::Color color = mSprite.getColor();
    color.a = value;
    mSprite.setColor(color);
}

const sf::Texture &Sprite::GetPlaceholderTexture()
{
    static sf::Texture placeholder;
    return placeholder;
}
