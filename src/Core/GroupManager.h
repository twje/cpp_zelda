#pragma once

#include <vector>

class Group;
class GameObject;

class GroupManager
{
public:
	void TrackGroup(Group& group);
	void RemoveFromGroups(GameObject* gameObject);
	void CleanupDeadObjects();

private:
	std::vector<Group*> mGroups;
	std::vector<GameObject*> mDeadList;
};