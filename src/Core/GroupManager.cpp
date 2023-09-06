#include "Core/GroupManager.h"

#include "Core/Group.h"

void GroupManager::TrackGroup(Group& group)
{
	mGroups.emplace_back(&group);
}

void GroupManager::RemoveFromGroups(const GameObject& gameObject)
{
	for (auto group : mGroups)
	{
		group->RemoveSprite(gameObject);
	}
}