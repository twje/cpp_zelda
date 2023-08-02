#include "Core/Sprite.h"
#include "Core/SpriteGroup.h"

Sprite::Sprite(const sf::Texture &texture)
    : mSprite(texture)
{
}

Sprite::Sprite()
    : mSprite(GetPlaceholderTexture())
{
}

const sf::Texture &Sprite::GetPlaceholderTexture()
{
    static sf::Texture placeholder;
    return placeholder;
}
