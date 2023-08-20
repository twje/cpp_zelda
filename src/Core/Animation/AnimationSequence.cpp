#include "Core/Animation/AnimationSequence.h"

AnimationSequence::AnimationSequence(float framesPerSecond)
    : mFramesPerSecond(framesPerSecond),
      mFrameTime(1.0f / framesPerSecond)
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

void AnimationSequence::Reset()
{
    mElapsedTime = 0.0f;
    mFrameIndex = 0;
}

// ------------
// Serializable
// ------------
void AnimationSequence::Serialize(YAML::Emitter &emitter)
{
    emitter << YAML::Key << "framesPerSecond" << YAML::Value << mFramesPerSecond;
}

void AnimationSequence::Deserialize(const YAML::Node &node)
{
    mFramesPerSecond = node["framesPerSecond"].as<uint16_t>();
    mFrameTime = 1.0f / mFramesPerSecond;
}