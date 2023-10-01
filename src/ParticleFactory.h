#pragma once

#include <SFML/Graphics.hpp>
#include "PlayerStatus.h"

// Forward declarations
class GroupManager;
class Group;
class Player;

class ParticleFactory
{
public:
	ParticleFactory(GroupManager& groupManager);

	void CreateLeafParticle(const sf::FloatRect& initiatorBounds, Group& group);
	void CreateEnemyDeathParticles(std::string enemyName, const sf::FloatRect& initiatorBounds, Group& group);
	void CreateEnemyAttackParticles(std::string attackName, const sf::FloatRect& initiatorBounds, Group& group);
	void CreateHealParticles(const sf::FloatRect& initiatorBounds, Group& group);
	void CreateFlameParticles(const sf::FloatRect& initiatorBounds, PlayerDirection initiatorDirection, Group& visibleGroup, Group& attackGroup);

private:
	GroupManager& mGroupManager;
};