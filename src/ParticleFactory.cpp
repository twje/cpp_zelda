#include "ParticleFactory.h"

// Core
#include "Core/GroupManager.h"
#include "Core/Group.h"
#include "Core/SpriteAnimation.h"
#include "Core/RectUtils.h"

// Game
#include "Settings.h"
#include "Support.h"

static void CenterParticleEffect(SpriteAnimation& effect, const sf::FloatRect& initiatorBounds)
{
	sf::Vector2f initiatorCenter = GetRectCenter(initiatorBounds);
	effect.SetPosition(initiatorCenter - 0.5f * effect.GetSize());
}

ParticleFactory::ParticleFactory(GroupManager& groupManager)
	: mGroupManager(groupManager)
{}

void ParticleFactory::CreateLeafParticle(const sf::FloatRect& initiatorBounds, Group& group)
{
	std::vector<std::string> sequenceIDs{
		"leaf_0",
		"leaf_1",
		"leaf_2",
		"leaf_3",
		"leaf_4",
		"leaf_5"
	};
	auto effect = std::make_shared<SpriteAnimation>(mGroupManager, "leaf", getRandomElement(sequenceIDs));
	CenterParticleEffect(*effect, initiatorBounds);
	group.Add(effect);
}

void ParticleFactory::CreateEnemyDeathParticles(std::string enemyName, const sf::FloatRect& initiatorBounds, Group& group)
{
	auto effect = std::make_shared<SpriteAnimation>(mGroupManager, enemyName, "death");
	CenterParticleEffect(*effect, initiatorBounds);
	group.Add(effect);
}

void ParticleFactory::CreateEnemyAttackParticles(std::string attackName, const sf::FloatRect& initiatorBounds, Group& group)
{
	auto effect = std::make_shared<SpriteAnimation>(mGroupManager, "attack", attackName);
	CenterParticleEffect(*effect, initiatorBounds);
	group.Add(effect);
}

void ParticleFactory::CreateHealParticles(const sf::FloatRect& initiatorBounds, Group& group)
{
	auto effect1 = std::make_shared<SpriteAnimation>(mGroupManager, "magic", "aura");
	CenterParticleEffect(*effect1, initiatorBounds);
	group.Add(effect1);

	auto effect2 = std::make_shared<SpriteAnimation>(mGroupManager, "magic", "heal");
	CenterParticleEffect(*effect2, initiatorBounds);
	group.Add(effect2);
}

void ParticleFactory::CreateFlameParticles(const sf::FloatRect& initiatorBounds, const PlayerDirection initiatorDirection, Group& visibleGroup, Group& attackGroup)
{			
	auto effect = std::make_shared<SpriteAnimation>(mGroupManager, "magic", "flame");		
	
	sf::Vector2f startPosition;
	sf::Vector2f direction;
	if (initiatorDirection == PlayerDirection::RIGHT)
	{		
		startPosition = GetRectMidRight(initiatorBounds) - GetRectMidLeft(effect->GetLocalBounds());
		direction = sf::Vector2f(1, 0);
	}
	else if (initiatorDirection == PlayerDirection::LEFT)
	{
		startPosition = GetRectMidLeft(initiatorBounds) - GetRectMidRight(effect->GetLocalBounds());
		direction = sf::Vector2f(-1, 0);
	}
	else if (initiatorDirection == PlayerDirection::DOWN)
	{
		startPosition = GetRectMidBottom(initiatorBounds) - GetRectMidTop(effect->GetLocalBounds());
		direction = sf::Vector2f(0, 1);
	}
	else
	{
		startPosition = GetRectMidTop(initiatorBounds) - GetRectMidBottom(effect->GetLocalBounds());
		direction = sf::Vector2f(0, -1);
	}	
	
	effect->SetPosition(startPosition);
	visibleGroup.Add(effect);
	attackGroup.Add(effect);

	for (size_t i = 1; i < 6; i++)
	{		
		int16_t variation = TILESIZE / 3;
		float offsetX = (direction.x * i) * TILESIZE + GetRandomInt(-variation, variation);
		float offsetY = (direction.y * i) * TILESIZE + GetRandomInt(-variation, variation);

		auto effect = std::make_shared<SpriteAnimation>(
			mGroupManager,
			"magic",
			"flame",
			startPosition + sf::Vector2f(offsetX, offsetY)
		);
		visibleGroup.Add(effect);
		attackGroup.Add(effect);
	}
}