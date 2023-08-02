#include "GameObject.h"

#include "SpriteGroup.h"

void GameObject::Kill()
{
    for (auto spriteGroup : mSpriteGroups)
    {
        spriteGroup->RemoveSprite(*this);
    }
}