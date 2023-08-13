#include "Core/Animation/Animation.h"
#include <cassert>

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