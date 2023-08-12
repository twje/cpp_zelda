#include "Core/AnimationSequence.h"

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

SequenceFrame TextureAnimationSequence::GetTextureAtIndex(size_t index) const
{
    TexturePtr texturePtr = mTextures.at(index);
    sf::IntRect textureRect(sf::Vector2i(), sf::Vector2i(texturePtr->getSize()));
    return {texturePtr, textureRect};
}