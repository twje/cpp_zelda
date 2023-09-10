#pragma once

#include "Core/Sprite.h"

// Forward declarations
class Animation;

class SpriteAnimation : public Sprite
{
public:
	SpriteAnimation(GroupManager& groupManager, std::string particleID, std::string sequenceID, sf::Vector2f position);
	SpriteAnimation(GroupManager& groupManager, std::string particleID, std::string sequenceID);

	virtual void Update(const sf::Time& timestamp) override;

private:
	void Animate(const sf::Time& timestamp);

private:
	std::unique_ptr<Animation> mAnimation;
};