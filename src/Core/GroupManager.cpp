#include "Core/GroupManager.h"

#include "Core/Group.h"

void GroupManager::TrackGroup(Group& group)
{
	mGroups.emplace_back(&group);
}

void GroupManager::RemoveFromGroups(GameObject* gameObject)
{
	auto it = std::find(mDeadList.begin(), mDeadList.end(), gameObject);
	if (it == mDeadList.end())
	{
		mDeadList.emplace_back(gameObject);
	}
}

void GroupManager::CleanupDeadObjects()
{
	for (auto gameObject : mDeadList)
	{
		for (auto group : mGroups)
		{
			group->RemoveSprite(*gameObject);
		}
	}
	mDeadList.clear();
}