#include "GameObject.h"

#include "Core/Group.h"


GameObject::GameObject(GroupManager& groupManager)
    :mGroupManager(groupManager)
{
}

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
    mGroupManager.RemoveFromGroups(*this);
}