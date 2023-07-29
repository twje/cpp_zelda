#include "Animation.h"
#include <cassert>

AnimationSequence::AnimationSequence(float framesPerSecond)
    : mFrameTime(1.0f / framesPerSecond),
      mElapsedTime(0),
      mFrameIndex(0)
{
}

void AnimationSequence::Update(const sf::Time &timestamp)
{
    mElapsedTime += timestamp.asSeconds();
    if (mElapsedTime > mFrameTime)
    {
        mElapsedTime -= mFrameTime;
        mFrameIndex = (mFrameIndex + 1) % GetFrameCount();
    }
}

TextureAnimationSequence::TextureAnimationSequence(uint8_t framesPerSecond, const TextureVector &textures)
    : AnimationSequence(framesPerSecond),
      mTextures(textures)
{
}

Animation::Animation()
    : mCurrentSequence(nullptr)
{
}

void Animation::Update(const sf::Time &timestamp)
{
    assert(mCurrentSequence != nullptr); // Animation sequence is not set
    mCurrentSequence->Update(timestamp);
}

void Animation::AddAnimationSequence(const std::string &sequenceID, Scope<AnimationSequence> sequence)
{
    assert(mSequences.find(sequenceID) == mSequences.end()); // Animation sequenceID already in use
    mSequences.emplace(sequenceID, std::move(sequence));
}

void Animation::SetAnimationSequence(const std::string &sequenceID)
{
    assert(mSequences.find(sequenceID) != mSequences.end()); // Invalid Animation sequenceID
    mSequenceID = sequenceID;
    mCurrentSequence = mSequences[mSequenceID].get();
    mCurrentSequence->Reset();
}