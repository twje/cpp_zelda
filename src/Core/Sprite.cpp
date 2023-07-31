#include "Core/Sprite.h"
#include "Core/SpriteGroup.h"

const sf::Texture Sprite::PLACEHOLDER_TEXTURE;

void Sprite::Kill()
{
    for (auto spriteGroup : mSpriteGroups)
    {
        spriteGroup->RemoveSprite(*this);
    }
}