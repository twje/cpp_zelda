#pragma once

#include <SFML/Graphics.hpp>

// Forward declarations
class GroupManager;
class Group;

class ParticleFactory
{
public:
	ParticleFactory(GroupManager& groupManager);

	void CreateLeafParticle(sf::Vector2f position, Group& group);

private:
	GroupManager& mGroupManager;
};