#include "Core/Sprite.h"
#include "Core/Group.h"

Sprite::Sprite(GroupManager& groupManager, const std::shared_ptr<sf::Texture> &texture)
    : GameObject(groupManager),    
      mTexture(texture),
      mSprite(*texture)
{
}

Sprite::Sprite(GroupManager& groupManager)
    : GameObject(groupManager),
      mSprite(GetPlaceholderTexture())
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
