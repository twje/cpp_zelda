#include "GameObject.h"

#include "Core/Group.h"

void GameObject::AddComponent(std::unique_ptr<Component> component)
{
    mCmponents.push_back(std::move(component));
}

bool GameObject::CollidesWith(const GameObject &other)
{
    return GetHitbox().findIntersection(other.GetHitbox()) ? true : false;
}

void GameObject::Kill()
{
    for (auto group : mGroups)
    {
        group->RemoveSprite(*this);
    }
}