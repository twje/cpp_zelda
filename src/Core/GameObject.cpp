#include "GameObject.h"

#include "Core/Group.h"

void GameObject::Kill()
{
    for (auto group : mGroups)
    {
        group->RemoveSprite(*this);
    }
}