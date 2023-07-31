#include "Core/Sprite.h"
#include "Core/SpriteGroup.h"

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