#include "GameObject.h"

#include "Core/Group.h"

void GameObject::Kill()
{
    for (auto spriteGroup : mGroups)
    {
        spriteGroup->RemoveSprite(*this);
    }
}