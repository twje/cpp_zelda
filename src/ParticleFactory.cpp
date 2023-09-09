#include "ParticleFactory.h"

// Core
#include "Core/GroupManager.h"
#include "Core/Group.h"
#include "Core/SpriteAnimation.h"

// Game
#include "Support.h"


ParticleFactory::ParticleFactory(GroupManager& groupManager)
	: mGroupManager(groupManager)
{}

void ParticleFactory::CreateLeafParticle(sf::Vector2f position, Group& group)
{
	std::vector<std::string> sequenceIDs{
		"leaf_0",
		"leaf_1",
		"leaf_2",
		"leaf_3",
		"leaf_4",
		"leaf_5"
	};
	auto effect = std::make_shared<SpriteAnimation>(mGroupManager, "leaf", getRandomElement(sequenceIDs), position);	
	group.Add(effect);
}

void ParticleFactory::CreateEnemyDeathParticles(std::string enemyName, sf::Vector2f position, Group& group)
{
	auto effect = std::make_shared<SpriteAnimation>(mGroupManager, enemyName, "death", position);
	group.Add(effect);
}

void ParticleFactory::CreateEnemyAttackParticles(std::string attackName, sf::Vector2f position, Group& group)
{
	auto effect = std::make_shared<SpriteAnimation>(mGroupManager, "attack", attackName, position);
	group.Add(effect);
}