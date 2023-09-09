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
	void CreateEnemyDeathParticles(std::string enemyName, sf::Vector2f position, Group& group);
	void CreateEnemyAttackParticles(std::string attackName, sf::Vector2f position, Group& group);

private:
	GroupManager& mGroupManager;
};