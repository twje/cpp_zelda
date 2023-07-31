#include "Core/Sprite.h"
#include "Core/SpriteGroup.h"

Sprite::Sprite(const sf::Texture &texture)
    : sf::Sprite(texture)
{
}

Sprite::Sprite()
    : sf::Sprite(GetPlaceholderTexture())
{
}

const sf::Texture &Sprite::GetPlaceholderTexture()
{
    static sf::Texture placeholder;
    return placeholder;
}

void Sprite::Kill()
{
    for (auto spriteGroup : mSpriteGroups)
    {
        spriteGroup->RemoveSprite(*this);
    }
}