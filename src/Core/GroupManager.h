#pragma once

#include <vector>

class Group;
class GameObject;

class GroupManager
{
public:
	void TrackGroup(Group& group);
	void RemoveFromGroups(const GameObject& gameObject);	

private:
	std::vector<Group*> mGroups;
};