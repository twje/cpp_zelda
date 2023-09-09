#include "Core/SpriteAnimation.h"
#include "Core/ResourceManager/AnimationManager.h"
#include "Core/Animation/Animation.h"

SpriteAnimation::SpriteAnimation(GroupManager& groupManager, std::string particleID, std::string sequenceID, sf::Vector2f position)
	: Sprite(groupManager),
	  mAnimation{ AnimationManager::GetInstance().LoadUnique(particleID) }
{
	mAnimation->SetAnimationSequence(sequenceID);
	Animate(sf::Time::Zero);
	SetPosition(position - 0.5f * GetSize());
}

void SpriteAnimation::Update(const sf::Time& timestamp) 
{
	Animate(timestamp);
	if (mAnimation->IsAllFramesPlayed())
	{
		Kill();
	}
}

void SpriteAnimation::Animate(const sf::Time& timestamp)
{
	mAnimation->Update(timestamp);
	SequenceFrame& frame = mAnimation->GetSequenceFrame();
	SetTexture(frame.mTexture);
	SetTextureRect(frame.mTextureRect);
}