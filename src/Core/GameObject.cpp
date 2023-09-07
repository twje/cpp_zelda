#include "GameObject.h"

#include "Core/Group.h"


GameObject::GameObject(GroupManager& groupManager)
    :mGroupManager(groupManager)
{
}

bool GameObject::CollidesWith(const GameObject &other)
{
    return GetHitbox().findIntersection(other.GetHitbox()) ? true : false;
}

void GameObject::Kill()
{
    mIsMarkedForDeletion = true;
    mGroupManager.RemoveFromGroups(this);
}